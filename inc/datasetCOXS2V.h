/* COX-S2V Dataset:
      video#:           4 videos sequences with frames regrouped by corresponding individual
                        always only one individual present on frames at a time
      ground truths:    specified directly in the file names
      eye locations:    available for all still and video image/frames
                        specified as "filename x y w h", one image per row 
      id:               take the form "yyyymmdd_####_0000" form image stills
                        suffix "_0000" is not added if requested (ex: for video directories)
      pseudo id:        pseudo id [1-1000] is attributed for corresponding ordered image lists
                        if requested, the returned string takes the form "####" padded with zeros
*/

#ifndef COMMON_CPP_DATASET_COXS2V_H
#define COMMON_CPP_DATASET_COXS2V_H

#include <string>
#include <vector>
using namespace std;

class COXS2V 
{
public:
    // Possible sequence information
    static const int VIDEO_QUANTITY = 4;
    static const int CAMERA_QUANTITY = 2;
    static const int INDIVIDUAL_QUANTITY = 1000;
    static const int TOTAL_SEQUENCES = VIDEO_QUANTITY;
    static const vector<string> INDIVIDUAL_IDS;
    
    // Sequence information
    static string getSequenceString(int video, int pseudoID = 0);
    static string getSequenceString(int video);
    static string getIndividualID(int pseudoID, bool withSuffix = false, bool asPseudoID = false);    

    // Directory names
    static const string EYES_GROUND_TRUTH_DIRECTORY_NAME;   // "Eye_location"
    static const string PUBLICATION_DIRECTORY_NAME;         // "Persons-for-Publication"
    static const string STILL_DIRECTORY_NAME;               // "COX-S2V-Still"
    static const string VIDEO_DIRECTORY_NAME;               // "COX-S2V-Video"
}

#endif/*COMMON_CPP_DATASET_COXS2V_H*/
