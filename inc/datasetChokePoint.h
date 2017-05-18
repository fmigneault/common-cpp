/* ChokePoint Dataset:
      P#T_S#_C#:      2 portals, 2 types (E:enter/L:leave), 4 sessions, 3 cameras = 48 video dirs (with Ground Truths, one by one individuals pass)
      P2T_S5_C#:      portal #2 only, 2 types (E:enter/L:leave), session #5, 3 cameras = 6 video dirs (no Ground Truths, simultaneous individuals)
      Crop Face dir:  up to 30 individuals (if present) with N face ROIs
*/

#ifndef COMMON_CPP_DATASET_CHOKEPOINT_H
#define COMMON_CPP_DATASET_CHOKEPOINT_H

#include <string>
using namespace std;

class ChokePoint 
{
public:
    // Possible sequence information
    enum PORTAL_TYPE { ENTER, LEAVE };    
    static const int PORTAL_TYPE_QUANTITY = 2;
    static const int PORTAL_QUANTITY = 2;
    static const int SESSION_QUANTITY = 4;
    static const int SESSION_SIMULTANEOUS_INDIVIDUALS = 5;
    static const int CAMERA_QUANTITY = 3;
    static const int INDIVIDUAL_QUANTITY = 30;
    static const int TOTAL_SEQUENCES = PORTAL_QUANTITY * SESSION_QUANTITY * PORTAL_TYPE_QUANTITY * CAMERA_QUANTITY;

    // Combine sequence information
    static string getSequenceString(int portal, PORTAL_TYPE type, int session, int camera, int id = 0);
    static string getIndividualID(int id, bool withPrefixID = false);

    // Directory names
    static const string CROPPED_FACES_DIRECTORY_NAME;   // "cropped_faces"
    static const string GROUND_TRUTH_DIRECTORY_NAME;    // "Ground Truth"
    static const string STILL_DIRECTORY_NAME;           // "Enroll"
    static const string VIDEO_DIRECTORY_NAME;           // "Videos"
}

#endif/*COMMON_CPP_CHOKEPOINT_H*/