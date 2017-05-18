#include "datasetChokePoint.h"

const string ChokePoint::CROPPED_FACES_DIRECTORY_NAME = "cropped_faces";
const string ChokePoint::GROUND_TRUTH_DIRECTORY_NAME = "Ground Truth";
const string ChokePoint::STILL_DIRECTORY_NAME = "Enroll";
const string ChokePoint::VIDEO_DIRECTORY_NAME = "Videos";

// Gets the string as "P#T_S#_C#", if the individual is non-zero, it adds the sub folder as "P#T_S#_C#/ID#" otherwise
string ChokePoint::getSequenceString(int portal, PORTAL_TYPE type, int session, int camera, int id)
{
    string dir = "P" + to_string(portal) + (type == ENTER ? "E" : type == LEAVE ? "L" : "") +
                      "_S" + to_string(session) + "_C" + to_string(camera);
    return id > 0 ? dir + "/" + getIndividualID(id) : dir;
}

string ChokePoint::getIndividualID(int id, bool withPrefixID)
{
    return (withPrefixID ? "ID" : "") + string(id > 9 ? 2 : 3, '0').append(to_string(id));
}