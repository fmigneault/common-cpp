#include "datasetChokePoint.h"

const vector<ChokePoint::PortalType> ChokePoint::PORTAL_TYPES{ ENTER, LEAVE };
const int ChokePoint::PORTAL_TYPE_QUANTITY = 2;
const int ChokePoint::PORTAL_QUANTITY = 2;
const int ChokePoint::SESSION_QUANTITY = 4;
const int ChokePoint::SESSION_SIMULTANEOUS_INDIVIDUALS = 5;
const int ChokePoint::CAMERA_QUANTITY = 3;
const int ChokePoint::INDIVIDUAL_QUANTITY = 30;
const int ChokePoint::TOTAL_SEQUENCES = ChokePoint::PORTAL_QUANTITY * ChokePoint::SESSION_QUANTITY * 
                                        ChokePoint::PORTAL_TYPE_QUANTITY * ChokePoint::CAMERA_QUANTITY;

const string ChokePoint::CROPPED_FACES_DIRECTORY_NAME = "cropped_faces";
const string ChokePoint::GROUND_TRUTH_DIRECTORY_NAME = "Ground Truth";
const string ChokePoint::STILL_DIRECTORY_NAME = "Enroll";
const string ChokePoint::VIDEO_DIRECTORY_NAME = "Videos";

string ChokePoint::getSequenceString(int portal, PortalType type, int session, int camera, int id)
{
    if (portal < 1 || portal > PORTAL_QUANTITY ||
        session < 1 || session > SESSION_QUANTITY ||
        camera < 1 || camera > CAMERA_QUANTITY)
        return "";

    string dir = "P" + to_string(portal) + (type == ENTER ? "E" : type == LEAVE ? "L" : "") +
                 "_S" + to_string(session) + "_C" + to_string(camera);
    string sID = getIndividualID(id, false);
    return sID == "" ? dir : dir + "/" + sID;
}

string ChokePoint::getIndividualID(int id, bool withPrefixID)
{
    if (id < 1 || id > INDIVIDUAL_QUANTITY)
        return "";
    return (withPrefixID ? "ID" : "") + string(id > 9 ? 2 : 3, '0').append(to_string(id));
}