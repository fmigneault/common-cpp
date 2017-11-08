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

#include <algorithm>
#include <string>
#include <vector>

class COXS2V
{
public:
    // --- possible sequence information ---

    static const int VIDEO_QUANTITY;                        // number of videos in the dataset (1-based indexes)
    static const int CAMERA_QUANTITY;                       // number of cameras employed (1-based indexes)
    static const int INDIVIDUAL_QUANTITY;                   // number of individuals in the dataset (1-based indexes)
    static const int TOTAL_SEQUENCES;                       // total number of sequences (1-based indexes)
    static const std::vector<std::string> INDIVIDUAL_IDS;   // sorted list of original IDs (pseudo ID index -> real ID mapping)

    // --- Sequence information ---

    // returns 'video#', or optionally 'video#/yyyymmdd_####' if a valid pseudo ID is specified
    // returns '' if either the video index or the pseudo ID are invalid values
    static std::string getSequenceString(int video, int pseudoID);
    // returns 'video#' if a valid number is specified, '' otherwise
    static std::string getSequenceString(int video);
    // returns 'yyyymmdd_####', optionally with suffix such as 'yyyymmdd_####_0000' if specified, ignores prefix parameter in this case
    // returns instead the '####' pseudo ID if requested, ignores the suffix parameter in this case
    // returns optionally the 'ID####' pseudo ID if requested with prefix, ignores suffix parameter in this case
    // in any combination, returns '' if the pseudo ID is an invalid value
    static std::string getIndividualID(int pseudoID, bool withSuffix = false, bool asPseudoID = false, bool withPrefix = false);

    // --- additional utilities ---

    // returns the index of the pseudo ID mapping from a given 'yyyymmdd_####' real ID
    // returns zero in case of invalid or unmatched ID
    static int getPseudoIDIndexFromIDString(std::string id);
    // returns the '####' formatted pseudo ID from a given 'yyyymmdd_####' real ID
    // optionally returns the 'ID####' format if prefix is requested
    // returns '' in case of invalid or unmatched ID
    static std::string getPseudoIDStringFromIDString(std::string id, bool withPrefix = false);

    // --- directory names ---

    static const std::string EYES_GROUND_TRUTH_DIRECTORY_NAME;   // "Eye_location"
    static const std::string PUBLICATION_DIRECTORY_NAME;         // "Persons-for-Publication"
    static const std::string STILL_DIRECTORY_NAME;               // "COX-S2V-Still"
    static const std::string VIDEO_DIRECTORY_NAME;               // "COX-S2V-Video"
};

#endif/*COMMON_CPP_DATASET_COXS2V_H*/
