#ifndef COMMON_CPP_FILES_H
#define COMMON_CPP_FILES_H

#include "types.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#define DEFAULT_BINARY_SAMPLES_HEADER "binary samples"

enum FileFormat { BINARY, LIBSVM, RAW };

class DataFile
{
public:
    static void readSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors, FileFormat format,
                                   std::string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static void readSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                   std::vector<int>& targetOutputs, FileFormat format, std::string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static void writeSampleDataFile(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                    std::vector<int>& targetOutputs, FileFormat format, std::string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static bool checkBinaryHeader(std::ifstream& binaryFileStream, std::string header);

private:
    static void readSampleDataFile_raw(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors);
    static void readSampleDataFile_binary(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                          std::vector<int>& targetOutputs, std::string header);
    static void readSampleDataFile_libsvm(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                          std::vector<int>& targetOutputs, std::string header);
    static void writeSampleDataFile_raw(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors);
    static void writeSampleDataFile_binary(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                           std::vector<int>& targetOutputs, std::string header);
    static void writeSampleDataFile_libsvm(std::string filePath, std::vector<FeatureVector>& sampleFeatureVectors,
                                           std::vector<int>& targetOutputs, std::string header);
};

#endif/*COMMON_CPP_FILES_H*/
