#include "datasetChokePoint.h"

const int ChokePoint::INDIVIDUAL_QUANTITY = 30;
const std::vector<ChokePoint::PortalType> ChokePoint::PORTAL_TYPES{ ENTER, LEAVE };
const int ChokePoint::PORTAL_TYPE_QUANTITY = 2;
const int ChokePoint::PORTAL_QUANTITY = 2;
const int ChokePoint::SESSION_QUANTITY = 4;
const int ChokePoint::SESSION_SIMULTANEOUS_INDIVIDUALS = 5;
const int ChokePoint::CAMERA_QUANTITY = 3;
const int ChokePoint::CAMERA_VIEWPOINT_QUANTITY = ChokePoint::CAMERA_QUANTITY *
                                                  ChokePoint::SESSION_QUANTITY;
const int ChokePoint::TOTAL_SEQUENCES = ChokePoint::PORTAL_QUANTITY *
                                        ChokePoint::SESSION_QUANTITY *
                                        ChokePoint::PORTAL_TYPE_QUANTITY *
                                        ChokePoint::CAMERA_QUANTITY;
const int ChokePoint::SEQUENCES_PER_SESSION = ChokePoint::PORTAL_QUANTITY *
                                              ChokePoint::PORTAL_TYPE_QUANTITY *
                                              ChokePoint::CAMERA_QUANTITY;
const int ChokePoint::SEQUENCES_PER_CAMERA_VIEWPOINT = ChokePoint::PORTAL_QUANTITY *
                                                       ChokePoint::PORTAL_TYPE_QUANTITY;

const std::string ChokePoint::CROPPED_FACES_DIRECTORY_NAME = "cropped_faces";
const std::string ChokePoint::GROUND_TRUTH_DIRECTORY_NAME = "Ground Truth";
const std::string ChokePoint::STILL_DIRECTORY_NAME = "Enroll";
const std::string ChokePoint::VIDEO_DIRECTORY_NAME = "Videos";

std::string ChokePoint::getSequenceString(int portal, PortalType type, int session, int camera, int id)
{
    if (portal < 1  || portal  > PORTAL_QUANTITY  ||
        session < 1 || session > SESSION_QUANTITY ||
        camera < 1  || camera  > CAMERA_QUANTITY)
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

std::vector<std::vector<std::string>> ChokePoint::getCameraViewpointSequences(bool videoVariations)
{
    // camera number and session are ascending after corresponding grouping is applied
    return (videoVariations) ?
        std::vector<std::vector<std::string>>{
            {"P1E_S1_C1","P1E_S2_C1","P1E_S3_C1","P1E_S4_C1"},
            {"P1E_S1_C2","P1E_S2_C2","P1E_S3_C2","P1E_S4_C2"},
            {"P1E_S1_C3","P1E_S2_C3","P1E_S3_C3","P1E_S4_C3"},
            {"P1L_S1_C1","P1L_S2_C1","P1L_S3_C1","P1L_S4_C1"},
            {"P1L_S1_C2","P1L_S2_C2","P1L_S3_C2","P1L_S4_C2"},
            {"P1L_S1_C3","P1L_S2_C3","P1L_S3_C3","P1L_S4_C2"},
            {"P2E_S1_C1","P2E_S2_C1","P2E_S3_C1","P2E_S4_C1"},
            {"P2E_S1_C2","P2E_S2_C2","P2E_S3_C2","P2E_S4_C2"},
            {"P2E_S1_C3","P2E_S2_C3","P2E_S3_C3","P2E_S4_C3"},
            {"P2L_S1_C1","P2L_S2_C1","P2L_S3_C1","P2L_S4_C1"},
            {"P2L_S1_C2","P2L_S2_C2","P2L_S3_C2","P2L_S4_C2"},
            {"P2L_S1_C3","P2L_S2_C3","P2L_S3_C3","P2L_S4_C3"}}
        :
        std::vector<std::vector<std::string>>{
            {"P1E_S1_C1",  "P1E_S2_C1",  "P1E_S3_C1",  "P1E_S4_C1"},
            {"P1E_S1_C2",  "P1E_S2_C2",  "P1E_S3_C2",  "P1E_S4_C2"},
            {"P1E_S1_C3",  "P1E_S2_C3",  "P1E_S3_C3",  "P1E_S4_C3"},
            {"P1L_S1_C1",  "P1L_S2_C1",  "P1L_S3_C1",  "P1L_S4_C1"},
            {"P1L_S1_C2",  "P1L_S2_C2",  "P1L_S3_C2",  "P1L_S4_C2"},
            {"P1L_S1_C3",  "P1L_S2_C3",  "P1L_S3_C3",  "P1L_S4_C2"},
            {"P2E_S1_C1.1","P2E_S1_C1.2","P2E_S2_C1.1","P2E_S2_C1.2","P2E_S3_C1.1","P2E_S3_C1.2","P2E_S4_C1.1","P2E_S4_C1.2"},
            {"P2E_S1_C2.1","P2E_S1_C2.2","P2E_S2_C2.1","P2E_S2_C2.2","P2E_S3_C2.1","P2E_S3_C2.2","P2E_S4_C2.1","P2E_S4_C2.2"},
            {"P2E_S1_C3.1","P2E_S1_C3.2","P2E_S2_C3.1","P2E_S2_C3.2","P2E_S3_C3.1","P2E_S3_C3.2","P2E_S4_C3.1","P2E_S4_C3.2"},
            {"P2L_S1_C1.1","P2L_S1_C1.2","P2L_S2_C1.1","P2L_S2_C1.2","P2L_S3_C1.1","P2L_S3_C1.2","P2L_S4_C1.1","P2L_S4_C1.2"},
            {"P2L_S1_C2.1","P2L_S1_C2.2","P2L_S2_C2.1","P2L_S2_C2.2","P2L_S3_C2.1","P2L_S3_C2.2","P2L_S4_C2.1","P2L_S4_C2.2"},
            {"P2L_S1_C3.1","P2L_S1_C3.2","P2L_S2_C3.1","P2L_S2_C3.2","P2L_S3_C3.1","P2L_S3_C3.2","P2L_S4_C3.1","P2L_S4_C3.2"}}
        ;
}
