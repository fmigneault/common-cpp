#include "datasetChokePoint.h"

const std::vector<ChokePoint::PortalType> ChokePoint::PORTAL_TYPES{ ENTER, LEAVE };
const int ChokePoint::PORTAL_TYPE_QUANTITY = 2;
const int ChokePoint::PORTAL_QUANTITY = 2;
const int ChokePoint::SESSION_QUANTITY = 4;
const int ChokePoint::SESSION_SIMULTANEOUS_INDIVIDUALS = 5;
const int ChokePoint::CAMERA_QUANTITY = 3;
const int ChokePoint::INDIVIDUAL_QUANTITY = 30;
const int ChokePoint::TOTAL_SEQUENCES = ChokePoint::PORTAL_QUANTITY * ChokePoint::SESSION_QUANTITY *
                                        ChokePoint::PORTAL_TYPE_QUANTITY * ChokePoint::CAMERA_QUANTITY;

const std::string ChokePoint::CROPPED_FACES_DIRECTORY_NAME = "cropped_faces";
const std::string ChokePoint::GROUND_TRUTH_DIRECTORY_NAME = "Ground Truth";
const std::string ChokePoint::STILL_DIRECTORY_NAME = "Enroll";
const std::string ChokePoint::VIDEO_DIRECTORY_NAME = "Videos";

std::string ChokePoint::getSequenceString(int portal, PortalType type, int session, int camera, int id)
{
    if (portal < 1 || portal > PORTAL_QUANTITY ||
        session < 1 || session > SESSION_QUANTITY ||
        camera < 1 || camera > CAMERA_QUANTITY)
        return "";

    std::string dir = "P" + std::to_string(portal) + (type == ENTER ? "E" : type == LEAVE ? "L" : "") +
                      "_S" + std::to_string(session) + "_C" + std::to_string(camera);
    std::string sID = getIndividualID(id, false);
    return sID == "" ? dir : dir + "/" + sID;
}

std::string ChokePoint::getIndividualID(int id, bool withPrefixID)
{
    if (id < 1 || id > INDIVIDUAL_QUANTITY)
        return "";
    return (withPrefixID ? "ID" : "") + std::string(id > 9 ? 2 : 3, '0').append(std::to_string(id));
}
