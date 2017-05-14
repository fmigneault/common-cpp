/* ChokePoint Dataset:
      P#T_S#_C#:      2 portals, 2 types (E:enter/L:leave), 4 sessions, 3 cameras = 48 video dirs (with Ground Truths, one by one individuals pass)
      P2T_S5_C#:      portal #2 only, 2 types (E:enter/L:leave), session #5, 3 cameras = 6 video dirs (no Ground Truths, simultaneous individuals)
      Crop Face dir:  up to 30 individuals (if present) with N face ROIs
*/

#ifndef COMMON_CPP_DATASET_CHOKEPOINT_H
#define COMMON_CPP_DATASET_CHOKEPOINT_H

#include <string>

// Possible sequence information
enum PORTAL_TYPE { ENTER, LEAVE };
const int PORTAL_TYPE_QUANTITY = 2;
const int PORTAL_QUANTITY = 2;
const int SESSION_QUANTITY = 4;
const int SESSION_SIMULTANEOUS_INDIVIDUALS = 5;
const int CAMERA_QUANTITY = 3;
const int INDIVIDUAL_QUANTITY = 30;
const int TOTAL_SEQUENCES = PORTAL_QUANTITY * SESSION_QUANTITY * PORTAL_TYPE_QUANTITY * CAMERA_QUANTITY;
// Combine sequence information
std::string buildChokePointSequenceString(int portal, PORTAL_TYPE type, int session, int camera, int id = 0);
std::string buildChokePointIndividualID(int id, bool withPrefixID = false);

#endif/*COMMON_CPP_CHOKEPOINT_H*/