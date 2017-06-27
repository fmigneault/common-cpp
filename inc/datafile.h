#ifndef COMMON_CPP_FILES_H
#define COMMON_CPP_FILES_H

#include "types.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define DEFAULT_BINARY_SAMPLES_HEADER "binary samples"

enum FileFormat { BINARY, LIBSVM, CSV };

class DataFile
{
public:
    static void readSampleDataFile(string filePath, vector<FeatureVector>& sampleFeatureVectors, FileFormat format, 
                                   string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static void readSampleDataFile(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, FileFormat format,
                                   string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static void writeSampleDataFile(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, FileFormat format,
                                    string header = DEFAULT_BINARY_SAMPLES_HEADER);
    static bool checkBinaryHeader(ifstream& binaryFileStream, string header);

private:
    static void readSampleDataFile_binary(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, string header);
    static void readSampleDataFile_libsvm(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, string header);
    static void writeSampleDataFile_binary(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, string header);
    static void writeSampleDataFile_libsvm(string filePath, vector<FeatureVector>& sampleFeatureVectors, vector<int>& targetOutputs, string header);    
};

#endif/*COMMON_CPP_FILES_H*/
