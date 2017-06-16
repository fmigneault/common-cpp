/* ChokePoint Dataset:
      P#T_S#_C#:        2 portals, 2 types (E:enter/L:leave), 4 sessions, 3 cameras = 48 video dirs (with Ground Truths, one by one individuals pass)
      P2T_S5_C#:        portal #2 only, 2 types (E:enter/L:leave), session #5, 3 cameras = 6 video dirs (no Ground Truths, simultaneous individuals)
      ID####:           individual IDs within the dataset, can be returned without 'ID' (ie: '####') if requested
      Crop Face dir:    up to 30 individuals (if present) with N face ROIs
*/

#ifndef COMMON_CPP_DATASET_CHOKEPOINT_H
#define COMMON_CPP_DATASET_CHOKEPOINT_H

#include <string>
#include <vector>
using namespace std;

class ChokePoint 
{
public:
    // --- possible sequence information ---

    enum PortalType { ENTER, LEAVE };                       // Portal types indicating the direction the in which portal is crossed
    static const vector<PortalType> PORTAL_TYPES;           // Vector of all portal types for convenience iterator
    static const int PORTAL_TYPE_QUANTITY;                  // Number of portals types (1-based indexes)
    static const int PORTAL_QUANTITY;                       // Number of portals employed (1-based indexes)
    static const int SESSION_QUANTITY;                      // Number of sequenced individual trajectory video sessions (1-based indexes)
    static const int SESSION_SIMULTANEOUS_INDIVIDUALS;      // Additional video session with simultaneous individual trajectories
    static const int CAMERA_QUANTITY;                       // Number of camera viewpoints per session/portal (1-based indexes)
    static const int INDIVIDUAL_QUANTITY;                   // Number of individuals (1-based indexes, warning: #8 often omitted)
    static const int TOTAL_SEQUENCES;                       // Total sequence combinations    

    // --- combine sequence information ---

    // returns 'P#T_S#_C#', or optionally 'P#T_S#_C#/ID####' if a valid ID is specified
    // returns '' if either of the video sequence indexes are invalid values
    static string getSequenceString(int portal, PortalType type, int session, int camera, int id = 0);
    static string getIndividualID(int id, bool withPrefixID = false);    

    // --- directory names ---

    static const string CROPPED_FACES_DIRECTORY_NAME;       // "cropped_faces"
    static const string GROUND_TRUTH_DIRECTORY_NAME;        // "Ground Truth"
    static const string STILL_DIRECTORY_NAME;               // "Enroll"
    static const string VIDEO_DIRECTORY_NAME;               // "Videos"
};

#endif/*COMMON_CPP_CHOKEPOINT_H*/