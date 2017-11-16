#include "datafile.h"
#include "testing.h"

/*
    Reads feature vectors and corresponding target output class from the specified formatted data sample file
*/
void DataFile::readSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                  FileFormat format, std::string header)
{
    std::vector<int> dummyOutputTargets;
    readSampleDataFile(filePath, sampleFeatureVectors, dummyOutputTargets, format, header);
}

/*
    Reads feature vectors and corresponding target output class from the specified formatted data sample file
*/
void DataFile::readSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                  std::vector<int>& targetOutputs, FileFormat format, std::string header)
{
    if (format == BINARY)
        readSampleDataFile_binary(filePath, sampleFeatureVectors, targetOutputs, header);
    else if (format == LIBSVM)
        readSampleDataFile_libsvm(filePath, sampleFeatureVectors, targetOutputs, header);
    else
        THROW("Unsupported file format");
}

void DataFile::readSampleDataFile_binary(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                         std::vector<int>& targetOutputs, std::string header)
{
    // check for opened file
    std::ifstream samplesFile(filePath, std::ios::in | std::ios::binary);
    ASSERT_THROW(samplesFile.is_open(), "Failed to open the specified samples data BINARY file: '" + filePath + "'");

    try
    {
        // check for header
        ASSERT_THROW(checkBinaryHeader(samplesFile, header), "Expected BINARY file header was not found");

        // check for samples and feature counts
        int nSamples = 0;   // warning: format 'int' required, not 'size_t' for matching binary dimension
        int nFeatures = 0;  // warning: format 'int' required, not 'size_t' for matching binary dimension
        samplesFile.read(reinterpret_cast<char*>(&nSamples), sizeof(nSamples));
        samplesFile.read(reinterpret_cast<char*>(&nFeatures), sizeof(nFeatures));
        ASSERT_THROW(nSamples > 0, "Read number of samples should be greater than zero");
        ASSERT_THROW(nFeatures > 0, "Read number of features should be greater than zero");

        // retrieve sample features and target outputs
        sampleFeatureVectors = std::vector<FeatureVector>(nSamples);
        targetOutputs = std::vector<int>(nSamples);
        samplesFile.read(reinterpret_cast<char*>(&targetOutputs[0]), nSamples * sizeof(targetOutputs[0]));
        for (int s = 0; s < nSamples; ++s)
        {
            sampleFeatureVectors[s] = FeatureVector(nFeatures);
            samplesFile.read(reinterpret_cast<char*>(&sampleFeatureVectors[s][0]), nFeatures * sizeof(sampleFeatureVectors[s][0]));
            ASSERT_THROW(samplesFile.good(), "Invalid file stream status when reading samples");
        }
        samplesFile.close();
    }
    catch (std::exception& ex)
    {
        // avoid locked file from assert failure
        if (samplesFile.is_open())
            samplesFile.close();
        throw ex;   // re-throw
    }
}

void DataFile::readSampleDataFile_libsvm(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                         std::vector<int>& targetOutputs, std::string header)
{
    std::ifstream samplesFile(filePath);
    ASSERT_THROW(samplesFile, "Could not open specified ESVM samples data file: '" + filePath + "'");

    try
    {
        std::vector<FeatureVector> samples;
        std::vector<int> targets;
        size_t nFeatures = 0;
        static std::string delimiter = ":";
        static size_t offDelim = delimiter.length();

        // loop each line
        while (samplesFile)
        {
            std::string line;
            if (!std::getline(samplesFile, line)) break;

            bool firstPart = true;
            std::istringstream ssline(line);
            std::string spart;
            int prev = 0;
            int index = 0;
            double value = 0;
            FeatureVector features;

            // loop each part delimited by a space
            while (ssline)
            {
                if (!std::getline(ssline, spart, ' ')) break;
                if (firstPart)
                {
                    // Reading label
                    ASSERT_THROW(spart.find(delimiter) == std::string::npos, "Could not find class label before sample of specified file");

                    #if ESVM_READ_LIBSVM_PARSER_MODE == 0
                    int target = 0;
                    std::istringstream(spart) >> target;
                    #elif ESVM_READ_LIBSVM_PARSER_MODE == 1
                    int target = strtol(spart.c_str(), NULL, 10);
                    #elif ESVM_READ_LIBSVM_PARSER_MODE == 2
                    int target = parse(spart.c_str());
                    #else
                    THROW("Undefined parser mode");
                    #endif/*ESVM_READ_LIBSVM_PARSER_MODE*/

                    targets.push_back(target);
                    firstPart = false;
                }
                else
                {
                    // Reading features
                    size_t offset = spart.find(delimiter);
                    ASSERT_THROW(offset != std::string::npos, "Failed to find feature 'index:value' delimiter");

                    #if ESVM_READ_LIBSVM_PARSER_MODE == 0
                    std::istringstream(spart.substr(0, offset)) >> index;
                    std::istringstream(spart.erase(0, offset + offDelim)) >> value;
                    #elif ESVM_READ_LIBSVM_PARSER_MODE == 1
                    index = strtol(spart.substr(0, offset).c_str(), NULL, 10);
                    value = strtod(spart.erase(0, offset + offDelim).c_str(), NULL);
                    #elif ESVM_READ_LIBSVM_PARSER_MODE == 2
                    index = parse(spart.substr(0, offset).c_str());
                    value = parse(spart.erase(0, offset + offDelim).c_str());
                    #else
                    THROW("Undefined parser mode");
                    #endif/*ESVM_READ_LIBSVM_PARSER_MODE*/

                    // end reading index:value if termination index found (-1), otherwise check if still valid index
                    if (index == -1) break;
                    ASSERT_THROW(index > 0, "Feature indexes must be one-based (zero index found)");
                    ASSERT_THROW(index - prev > 0, "Feature indexes must be in ascending order");

                    // Add omitted sparse features (zero value features)
                    while (index - prev > 1)
                    {
                        features.push_back(0);
                        prev++;
                    }
                    features.push_back(value);
                    prev++;
                }
            }

            if (nFeatures == 0)
                nFeatures = features.size();
            else
                ASSERT_THROW(nFeatures == features.size(), "Loaded feature vectors must have a consistent dimension");
            samples.push_back(features);
        }
        ASSERT_THROW(samplesFile.eof(), "Reading ESVM samples file finished without reaching EOF");

        sampleFeatureVectors = samples;
        targetOutputs = targets;
    }
    catch (std::exception& ex)
    {
        // avoid locked file from assert failure
        if (samplesFile.is_open())
            samplesFile.close();
        throw ex;   // re-throw
    }
}

/*
    Writes feature vectors and corresponding target output class to a data sample file
*/
void DataFile::writeSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                   std::vector<int>& targetOutputs, FileFormat format, std::string header)
{
    size_t nSamples = sampleFeatureVectors.size();
    ASSERT_THROW(nSamples > 0, "Number of samples must be greater than zero");
    ASSERT_THROW(nSamples == targetOutputs.size(), "Number of samples must match number of corresponding target outputs");
    size_t nFeatures = sampleFeatureVectors[0].size();
    ASSERT_THROW(nFeatures > 0, "Number of features in samples must be greater than zero");

    for (size_t s = 0; s < nSamples; ++s)
        ASSERT_THROW(sampleFeatureVectors[s].size() == nFeatures, "Inconsistent number of features in samples");

    if (format == BINARY)
        writeSampleDataFile_binary(filePath, sampleFeatureVectors, targetOutputs, header);
    else if (format == LIBSVM)
        writeSampleDataFile_libsvm(filePath, sampleFeatureVectors, targetOutputs, header);
    else
        THROW("Unsupported file format");
}

/*
    Writes feature vectors and corresponding target output class to a BINARY data sample file
*/
void DataFile::writeSampleDataFile_binary(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                          std::vector<int>& targetOutputs, std::string header)
{
    /*
    Expected data format and order:    <all reinterpreted as char*>

        TYPE          QUANTITY                VALUE
        =======================================================
        (char)      | len(header)           | 'ESVM_BINARY_HEADER_SAMPLES'
        (int)       | 1                     | nSamples
        (int)       | 1                     | nFeatures
        (int)       | nSamples              | Targets
        (double)    | nSamples * nFeatures  | Samples Features
    */

    // check opened file
    std::ofstream samplesFile(filePath, std::ios::out | std::ios::binary);
    ASSERT_THROW(samplesFile.is_open(), "Failed to open the specified samples data BINARY file: '" + filePath + "'");

    // get sample and feature counts (already checked valid dimensions from calling function)
    int nSamples = (int)sampleFeatureVectors.size();     // warning: format 'int' required, not 'size_t' for matching binary dimension
    int nFeatures = (int)sampleFeatureVectors[0].size(); // warning: format 'int' required, not 'size_t' for matching binary dimension

                                                         // write header and counts for later reading
    const char *headerChar = header.c_str();
    samplesFile.write(headerChar, header.size());
    samplesFile.write(reinterpret_cast<const char*>(&nSamples), sizeof(nSamples));
    samplesFile.write(reinterpret_cast<const char*>(&nFeatures), sizeof(nFeatures));

    // write target outputs and sample features
    samplesFile.write(reinterpret_cast<const char*>(&targetOutputs[0]), nSamples * sizeof(targetOutputs[0]));
    for (int s = 0; s < nSamples; ++s)
        samplesFile.write(reinterpret_cast<const char*>(&sampleFeatureVectors[s][0]), nFeatures * sizeof(sampleFeatureVectors[s][0]));

    samplesFile.close();
}

/*
    Writes feature vectors and corresponding target output class to a LIBSVM formatted data sample file
*/
void DataFile::writeSampleDataFile_libsvm(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                          std::vector<int>& targetOutputs, std::string header)
{
    std::ofstream samplesFile(filePath);
    ASSERT_THROW(samplesFile, "Could not open specified ESVM sample data file: '" + filePath + "'");

    // get sample and feature counts (already checked valid dimensions from calling function)
    size_t nSamples = sampleFeatureVectors.size();
    size_t nFeatures = sampleFeatureVectors[0].size();

    for (size_t s = 0; s < nSamples; ++s)
    {
        samplesFile << targetOutputs[s];
        for (size_t f = 0; f < nFeatures; ++f)
            samplesFile << " " << (f + 1) << ":" << sampleFeatureVectors[s][f];
        samplesFile << std::endl;
    }
}

/*
    Verifies if the specified header can be found at the start of a binary file
*/
bool DataFile::checkBinaryHeader(std::ifstream& binaryFileStream, std::string header)
{
    if (!binaryFileStream.is_open()) return false;
    size_t headerLength = header.size();
    char *headerCheck = new char[headerLength + 1];     // +1 for the terminating '\0'
    binaryFileStream.read(headerCheck, headerLength);
    headerCheck[headerLength] = '\0';                   // avoids comparing different strings because '\0' is not found
    bool isFound = (header == std::string(headerCheck));
    delete[] headerCheck;
    return isFound;
}
