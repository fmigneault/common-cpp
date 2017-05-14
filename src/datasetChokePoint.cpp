#include "datasetChokePoint.h"

// Builds the string as "P#T_S#_C#", if the individual is non-zero, it adds the sub folder as "P#T_S#_C#/ID#"
std::string buildChokePointSequenceString(int portal, PORTAL_TYPE type, int session, int camera, int id)
{
    std::string dir = "P" + std::to_string(portal) + (type == ENTER ? "E" : type == LEAVE ? "L" : "") +
                      "_S" + std::to_string(session) + "_C" + std::to_string(camera);
    return id > 0 ? dir + "/" + buildChokePointIndividualID(id) : dir;
}

std::string buildChokePointIndividualID(int id, bool withPrefixID)
{
    return (withPrefixID ? "ID" : "") + std::string(id > 9 ? 2 : 3, '0').append(std::to_string(id));
}
