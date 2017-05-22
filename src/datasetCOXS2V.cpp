#include "datasetCOXS2V.h"

const string COXS2V::EYES_GROUND_TRUTH_DIRECTORY_NAME = "Eye_location";
const string COXS2V::PUBLICATION_DIRECTORY_NAME = "Persons-for-Publication";
const string COXS2V::STILL_DIRECTORY_NAME = "COX-S2V-Still";
const string COXS2V::VIDEO_DIRECTORY_NAME = "COX-S2V-Video";

string COXS2V::getSequenceString(int video, int pseudoID)
{
    string seq = getSequenceString(video);
    string sid = getIndividualID(pseudoID, false, false);
    return seq + (seq == "" || sid == "" ? "" : "/" + getIndividualID(pseudoID, false, false));
}

string COXS2V::getSequenceString(int video)
{
    if (video < 1 || video > VIDEO_QUANTITY)
        return "";
    return "video" + std::to_string(video);
}

string COXS2V::getIndividualID(int pseudoID, bool withSuffix, bool asPseudoID, bool withPrefix)
{
    if (pseudoID < 1 || pseudoID > INDIVIDUAL_QUANTITY)
        return "";
    if (asPseudoID) {
        int pad = pseudoID > 9 ? (pseudoID > 99 ? (pseudoID > 999 ? 0 : 1) : 2) : 3;
        return (withPrefix ? "ID" : "") + string(pad, '0') + to_string(pseudoID);
    }
    return INDIVIDUAL_IDS[pseudoID - 1] + (withSuffix ? "_0000" : "");
}

int COXS2V::getPseudoIDIndexFromIDString(string id)
{
    auto low = std::lower_bound(INDIVIDUAL_IDS.begin(), INDIVIDUAL_IDS.end(), id);
    if (low == INDIVIDUAL_IDS.end())
        return 0;
    if (*low != id)
        return 0;
    return low - INDIVIDUAL_IDS.begin() + 1;
}

string COXS2V::getPseudoIDStringFromIDString(string id, bool withPrefix)
{
    int pseudoID = getPseudoIDIndexFromIDString(id);
    if (pseudoID > 0)
        return getIndividualID(pseudoID, false, true, withPrefix);
    return "";
}

// sorted list of original IDs
const vector<string> COXS2V::INDIVIDUAL_IDS = {
    "20110318_0001", "20110318_0002", "20110318_0003", "20110318_0004", "20110318_0005", "20110318_0006", "20110318_0007", "20110318_0008", "20110318_0009", "20110318_0010",
    "20110318_0012", "20110318_0014", "20110318_0015", "20110318_0016", "20110318_0017", "20110318_0018", "20110318_0019", "20110318_0020", "20110318_0021", "20110318_0022",
    "20110318_0024", "20110318_0025", "20110318_0026", "20110318_0027", "20110318_0028", "20110318_0029", "20110318_0030", "20110318_0031", "20110318_0032", "20110318_0033",
    "20110318_0034", "20110318_0035", "20110318_0037", "20110318_0038", "20110318_0039", "20110318_0040", "20110318_0041", "20110319_0001", "20110319_0002", "20110319_0003",
    "20110319_0004", "20110319_0005", "20110319_0006", "20110319_0007", "20110319_0008", "20110319_0009", "20110319_0010", "20110319_0012", "20110319_0013", "20110319_0014",
    "20110319_0017", "20110319_0018", "20110319_0019", "20110319_0020", "20110319_0021", "20110319_0022", "20110319_0023", "20110319_0024", "20110319_0025", "20110319_0026",
    "20110319_0027", "20110319_0028", "20110319_0030", "20110319_0032", "20110319_0033", "20110319_0034", "20110319_0035", "20110319_0036", "20110319_0037", "20110319_0038",
    "20110319_0039", "20110319_0040", "20110319_0041", "20110319_0042", "20110319_0043", "20110319_0044", "20110319_0045", "20110319_0046", "20110319_0047", "20110319_0048",
    "20110319_0049", "20110319_0050", "20110319_0051", "20110319_0052", "20110319_0053", "20110319_0054", "20110319_0055", "20110319_0056", "20110319_0058", "20110319_0059",
    "20110319_0060", "20110319_0062", "20110319_0063", "20110319_0064", "20110319_0065", "20110319_0066", "20110319_0067", "20110319_0068", "20110319_0069", "20110319_0071",
    "20110319_0072", "20110319_0073", "20110319_0074", "20110319_0075", "20110319_0076", "20110319_0077", "20110319_0078", "20110319_0080", "20110319_0081", "20110319_0082",
    "20110319_0083", "20110319_0085", "20110319_0087", "20110319_0088", "20110319_0089", "20110319_0090", "20110319_0091", "20110319_0092", "20110319_0093", "20110319_0094",
    "20110319_0096", "20110319_0097", "20110319_0098", "20110319_0100", "20110319_0102", "20110319_0103", "20110319_0104", "20110319_0105", "20110319_0106", "20110319_0107",
    "20110319_0108", "20110319_0109", "20110319_0110", "20110319_0111", "20110319_0112", "20110319_0116", "20110319_0117", "20110319_0119", "20110319_0120", "20110319_0121",
    "20110319_0122", "20110319_0123", "20110319_0125", "20110319_0126", "20110319_0128", "20110319_0129", "20110319_0130", "20110319_0131", "20110319_0132", "20110319_0134",
    "20110319_0135", "20110319_0136", "20110319_0137", "20110319_0138", "20110319_0139", "20110319_0140", "20110319_0141", "20110319_0142", "20110319_0143", "20110319_0144",
    "20110319_0145", "20110319_0146", "20110319_0147", "20110319_0148", "20110319_0149", "20110319_0150", "20110319_0151", "20110319_0152", "20110319_0153", "20110319_0154",
    "20110319_0155", "20110319_0156", "20110319_0157", "20110319_0158", "20110319_0159", "20110319_0161", "20110319_0163", "20110319_0165", "20110319_0166", "20110319_0168",
    "20110319_0169", "20110319_0170", "20110319_0171", "20110319_0172", "20110319_0173", "20110319_0174", "20110319_0175", "20110319_0176", "20110319_0177", "20110319_0178",
    "20110319_0179", "20110319_0181", "20110319_0184", "20110319_0185", "20110319_0186", "20110319_0187", "20110319_0188", "20110319_0189", "20110319_0190", "20110319_0193",
    "20110319_0194", "20110319_0195", "20110319_0196", "20110319_0198", "20110319_0199", "20110319_0200", "20110319_0204", "20110319_0206", "20110319_0207", "20110319_0208",
    "20110319_0213", "20110319_0214", "20110319_0215", "20110319_0216", "20110319_0217", "20110319_0218", "20110319_0220", "20110319_0221", "20110319_0222", "20110319_0223",
    "20110319_0224", "20110319_0226", "20110319_0227", "20110319_0228", "20110319_0229", "20110319_0230", "20110319_0231", "20110319_0232", "20110319_0233", "20110319_0234",
    "20110319_0235", "20110319_0236", "20110319_0237", "20110319_0238", "20110319_0239", "20110319_0241", "20110319_0243", "20110319_0244", "20110319_0245", "20110319_0246",
    "20110319_0247", "20110319_0248", "20110319_0249", "20110319_0250", "20110319_0251", "20110319_0252", "20110319_0254", "20110319_0255", "20110319_0256", "20110319_0257",
    "20110319_0258", "20110319_0259", "20110319_0260", "20110319_0261", "20110319_0262", "20110319_0263", "20110319_0264", "20110319_0265", "20110319_0266", "20110319_0267",
    "20110319_0268", "20110319_0269", "20110319_0270", "20110319_0272", "20110319_0273", "20110319_0274", "20110319_0275", "20110319_0276", "20110319_0277", "20110319_0278",
    "20110319_0279", "20110319_0280", "20110319_0281", "20110319_0282", "20110319_0284", "20110319_0285", "20110319_0286", "20110319_0288", "20110319_0289", "20110319_0290",
    "20110320_0001", "20110320_0002", "20110320_0003", "20110320_0004", "20110320_0005", "20110320_0006", "20110320_0007", "20110320_0008", "20110320_0010", "20110320_0011",
    "20110320_0012", "20110320_0013", "20110320_0014", "20110320_0015", "20110320_0016", "20110320_0017", "20110320_0018", "20110320_0019", "20110320_0020", "20110320_0021",
    "20110320_0022", "20110320_0023", "20110320_0024", "20110320_0025", "20110320_0026", "20110320_0027", "20110320_0028", "20110320_0029", "20110320_0030", "20110320_0031",
    "20110320_0032", "20110320_0033", "20110320_0034", "20110320_0035", "20110320_0036", "20110320_0037", "20110320_0038", "20110320_0039", "20110320_0040", "20110320_0041",
    "20110320_0042", "20110320_0043", "20110320_0044", "20110320_0045", "20110320_0046", "20110320_0047", "20110320_0048", "20110320_0049", "20110320_0050", "20110320_0051",
    "20110320_0052", "20110320_0053", "20110320_0054", "20110320_0056", "20110320_0058", "20110320_0060", "20110320_0061", "20110320_0062", "20110320_0063", "20110320_0064",
    "20110320_0065", "20110320_0066", "20110320_0067", "20110320_0068", "20110320_0069", "20110320_0070", "20110320_0071", "20110320_0072", "20110320_0073", "20110320_0074",
    "20110320_0075", "20110320_0076", "20110320_0077", "20110320_0078", "20110320_0079", "20110320_0080", "20110320_0081", "20110320_0082", "20110320_0084", "20110320_0086",
    "20110320_0089", "20110320_0092", "20110320_0094", "20110320_0095", "20110320_0096", "20110320_0097", "20110320_0098", "20110320_0099", "20110320_0100", "20110320_0101",
    "20110320_0102", "20110320_0103", "20110320_0104", "20110320_0105", "20110320_0106", "20110320_0107", "20110320_0108", "20110320_0109", "20110320_0110", "20110320_0111",
    "20110320_0112", "20110320_0113", "20110320_0114", "20110320_0115", "20110320_0116", "20110320_0117", "20110320_0118", "20110320_0119", "20110320_0120", "20110320_0121",
    "20110320_0124", "20110320_0125", "20110320_0126", "20110320_0127", "20110320_0128", "20110320_0129", "20110320_0130", "20110320_0131", "20110320_0132", "20110320_0134",
    "20110320_0135", "20110320_0137", "20110320_0138", "20110320_0139", "20110320_0140", "20110320_0141", "20110320_0142", "20110320_0143", "20110320_0144", "20110320_0145",
    "20110320_0146", "20110320_0147", "20110320_0150", "20110320_0152", "20110320_0153", "20110320_0154", "20110320_0156", "20110320_0157", "20110320_0158", "20110320_0160",
    "20110320_0161", "20110320_0163", "20110320_0164", "20110320_0165", "20110320_0166", "20110320_0167", "20110320_0168", "20110320_0169", "20110320_0170", "20110320_0171",
    "20110320_0172", "20110320_0173", "20110320_0174", "20110320_0175", "20110320_0176", "20110320_0177", "20110320_0178", "20110320_0179", "20110320_0181", "20110320_0182",
    "20110320_0183", "20110320_0185", "20110320_0186", "20110320_0187", "20110320_0188", "20110320_0189", "20110320_0190", "20110320_0191", "20110320_0193", "20110320_0194",
    "20110320_0195", "20110320_0196", "20110320_0197", "20110320_0198", "20110320_0199", "20110320_0200", "20110320_0201", "20110320_0202", "20110320_0203", "20110320_0204",
    "20110422_0002", "20110422_0004", "20110422_0005", "20110422_0006", "20110422_0007", "20110422_0008", "20110422_0009", "20110422_0010", "20110422_0011", "20110422_0013",
    "20110422_0015", "20110422_0017", "20110422_0018", "20110422_0021", "20110422_0022", "20110422_0023", "20110422_0024", "20110422_0025", "20110422_0026", "20110422_0027",
    "20110422_0028", "20110422_0031", "20110422_0033", "20110422_0034", "20110422_0035", "20110422_0036", "20110422_0039", "20110422_0040", "20110422_0042", "20110422_0043",
    "20110422_0044", "20110422_0045", "20110422_0046", "20110422_0047", "20110422_0049", "20110422_0051", "20110422_0052", "20110422_0054", "20110422_0055", "20110422_0056",
    "20110422_0057", "20110422_0058", "20110422_0059", "20110422_0060", "20110422_0061", "20110422_0062", "20110422_0063", "20110422_0064", "20110422_0065", "20110422_0066",
    "20110422_0067", "20110422_0068", "20110422_0070", "20110422_0071", "20110422_0072", "20110422_0073", "20110422_0074", "20110422_0075", "20110422_0076", "20110422_0077",
    "20110422_0078", "20110422_0079", "20110422_0080", "20110422_0081", "20110422_0082", "20110422_0083", "20110422_0084", "20110422_0085", "20110422_0086", "20110422_0087",
    "20110422_0088", "20110422_0089", "20110422_0090", "20110422_0093", "20110422_0095", "20110422_0097", "20110422_0098", "20110422_0100", "20110422_0101", "20110422_0102",
    "20110422_0104", "20110422_0105", "20110422_0106", "20110422_0108", "20110422_0109", "20110422_0111", "20110422_0112", "20110422_0113", "20110422_0115", "20110422_0120",
    "20110422_0122", "20110422_0123", "20110422_0124", "20110422_0125", "20110422_0126", "20110423_0001", "20110423_0002", "20110423_0004", "20110423_0005", "20110423_0006",
    "20110423_0007", "20110423_0008", "20110423_0010", "20110423_0011", "20110423_0013", "20110423_0014", "20110423_0015", "20110423_0016", "20110423_0017", "20110423_0018",
    "20110423_0020", "20110423_0021", "20110423_0022", "20110423_0023", "20110423_0025", "20110423_0026", "20110423_0027", "20110423_0031", "20110423_0032", "20110423_0033",
    "20110423_0034", "20110423_0035", "20110423_0036", "20110423_0038", "20110423_0039", "20110423_0041", "20110423_0043", "20110423_0044", "20110423_0045", "20110423_0046",
    "20110423_0047", "20110423_0048", "20110423_0049", "20110423_0050", "20110423_0051", "20110423_0053", "20110423_0054", "20110423_0055", "20110423_0056", "20110423_0057",
    "20110423_0058", "20110423_0059", "20110423_0062", "20110423_0066", "20110423_0068", "20110423_0070", "20110423_0071", "20110423_0075", "20110423_0076", "20110423_0081",
    "20110423_0082", "20110423_0084", "20110423_0085", "20110423_0086", "20110423_0088", "20110423_0091", "20110423_0092", "20110423_0093", "20110423_0094", "20110423_0095",
    "20110423_0096", "20110423_0098", "20110423_0099", "20110423_0100", "20110423_0103", "20110423_0104", "20110423_0105", "20110423_0108", "20110423_0109", "20110423_0112",
    "20110423_0114", "20110423_0115", "20110423_0116", "20110423_0117", "20110423_0118", "20110423_0119", "20110423_0121", "20110423_0122", "20110423_0123", "20110423_0124",
    "20110423_0125", "20110423_0126", "20110423_0127", "20110423_0128", "20110423_0129", "20110423_0130", "20110423_0131", "20110423_0132", "20110423_0133", "20110423_0134",
    "20110423_0136", "20110423_0137", "20110423_0138", "20110423_0139", "20110423_0140", "20110423_0141", "20110423_0142", "20110423_0143", "20110423_0144", "20110423_0145",
    "20110423_0147", "20110423_0148", "20110423_0149", "20110423_0150", "20110423_0151", "20110423_0152", "20110423_0153", "20110423_0154", "20110423_0155", "20110423_0157",
    "20110423_0158", "20110423_0160", "20110423_0161", "20110423_0162", "20110423_0163", "20110423_0164", "20110423_0165", "20110423_0168", "20110423_0169", "20110423_0170",
    "20110423_0171", "20110423_0172", "20110423_0173", "20110423_0176", "20110423_0177", "20110423_0178", "20110423_0179", "20110423_0180", "20110423_0181", "20110423_0184",
    "20110423_0185", "20110423_0186", "20110423_0188", "20110423_0189", "20110423_0190", "20110423_0191", "20110423_0192", "20110423_0193", "20110423_0195", "20110423_0196",
    "20110423_0197", "20110423_0198", "20110423_0199", "20110423_0200", "20110423_0201", "20110423_0202", "20110423_0204", "20110423_0205", "20110423_0210", "20110423_0211",
    "20110423_0213", "20110423_0215", "20110423_0216", "20110423_0217", "20110423_0218", "20110423_0219", "20110423_0220", "20110423_0221", "20110423_0222", "20110423_0223",
    "20110423_0224", "20110423_0226", "20110423_0229", "20110423_0230", "20110423_0231", "20110423_0232", "20110423_0233", "20110423_0234", "20110423_0235", "20110423_0236",
    "20110423_0237", "20110423_0238", "20110423_0240", "20110423_0241", "20110423_0242", "20110423_0243", "20110423_0244", "20110423_0245", "20110423_0251", "20110423_0252",
    "20110423_0253", "20110423_0254", "20110423_0255", "20110423_0256", "20110423_0257", "20110423_0258", "20110423_0261", "20110423_0262", "20110423_0263", "20110423_0264",
    "20110423_0265", "20110423_0266", "20110423_0268", "20110423_0269", "20110423_0270", "20110423_0271", "20110423_0272", "20110423_0273", "20110423_0276", "20110423_0277",
    "20110423_0278", "20110423_0279", "20110423_0280", "20110423_0281", "20110423_0282", "20110423_0284", "20110423_0285", "20110423_0286", "20110423_0288", "20110423_0290",
    "20110423_0291", "20110423_0292", "20110423_0293", "20110423_0294", "20110423_0295", "20110423_0296", "20110423_0297", "20110423_0298", "20110423_0299", "20110423_0301",
    "20110423_0302", "20110423_0303", "20110423_0304", "20110423_0305", "20110423_0306", "20110423_0308", "20110423_0309", "20110423_0310", "20110423_0312", "20110423_0313",
    "20110423_0314", "20110423_0315", "20110423_0316", "20110423_0317", "20110423_0318", "20110423_0319", "20110423_0320", "20110423_0321", "20110423_0322", "20110423_0323",
    "20110423_0324", "20110423_0325", "20110423_0326", "20110423_0327", "20110423_0328", "20110423_0330", "20110423_0331", "20110423_0332", "20110423_0334", "20110423_0335",
    "20110423_0336", "20110423_0337", "20110423_0338", "20110423_0339", "20110423_0342", "20110423_0343", "20110423_0344", "20110423_0345", "20110423_0347", "20110423_0348",
    "20110423_0350", "20110423_0351", "20110423_0352", "20110423_0353", "20110423_0354", "20110423_0355", "20110423_0356", "20110423_0357", "20110423_0358", "20110423_0359",
    "20110423_0360", "20110423_0361", "20110423_0362", "20110423_0364", "20110423_0365", "20110423_0366", "20110423_0367", "20110423_0368", "20110423_0369", "20110423_0370",
    "20110423_0371", "20110423_0372", "20110423_0373", "20110424_0001", "20110424_0002", "20110424_0003", "20110424_0004", "20110424_0006", "20110424_0007", "20110424_0008",
    "20110424_0009", "20110424_0010", "20110424_0011", "20110424_0012", "20110424_0013", "20110424_0014", "20110424_0015", "20110424_0017", "20110424_0018", "20110424_0019",
    "20110424_0020", "20110424_0022", "20110424_0023", "20110424_0024", "20110424_0025", "20110424_0026", "20110424_0027", "20110424_0028", "20110424_0029", "20110424_0030",
    "20110424_0031", "20110424_0032", "20110424_0034", "20110424_0037", "20110424_0039", "20110424_0041", "20110424_0042", "20110424_0043", "20110424_0045", "20110424_0046",
    "20110424_0047", "20110424_0048", "20110424_0049", "20110424_0050", "20110424_0055", "20110424_0058", "20110424_0059", "20110424_0060", "20110424_0063", "20110424_0067",
    "20110424_0068", "20110424_0069", "20110424_0071", "20110424_0072", "20110424_0073", "20110424_0075", "20110424_0076", "20110424_0078", "20110424_0080", "20110424_0081",
    "20110424_0085", "20110424_0086", "20110424_0087", "20110424_0088", "20110424_0092", "20110424_0093", "20110424_0095", "20110424_0097", "20110424_0098", "20110424_0101",
    "20110424_0103", "20110424_0105", "20110424_0106", "20110424_0110", "20110424_0114", "20110424_0121", "20110424_0122", "20110424_0123", "20110424_0125", "20110424_0131",
    "20110424_0132", "20110424_0133", "20110424_0134", "20110424_0135", "20110424_0136", "20110424_0139", "20110424_0142", "20110424_0143", "20110424_0145", "20110424_0146",
    "20110424_0148", "20110424_0149", "20110424_0151", "20110424_0155", "20110424_0156", "20110424_0159", "20110424_0163", "20110424_0166", "20110424_0167", "20110424_0169",
    "20110424_0170", "20110424_0171", "20110424_0172", "20110424_0174", "20110424_0175", "20110424_0176", "20110424_0177", "20110424_0180", "20110424_0181", "20110424_0183",
    "20110424_0186", "20110424_0188", "20110424_0189", "20110424_0192", "20110424_0193", "20110424_0195", "20110424_0197", "20110424_0198", "20110424_0199", "20110424_0200",
    "20110424_0202", "20110424_0207", "20110424_0209", "20110424_0210", "20110424_0211", "20110424_0212", "20110424_0216", "20110424_0218", "20110424_0221", "20110424_0225",
    "20110424_0230", "20110424_0232", "20110424_0233", "20110424_0237", "20110424_0238", "20110424_0239", "20110424_0241", "20110424_0242", "20110424_0243", "20110424_0247",
    "20110424_0252", "20110424_0255", "20110424_0271", "20110424_0274", "20110424_0276", "20110424_0277", "20110424_0278", "20110424_0279", "20110424_0283", "20110424_0285",
    "20110424_0286", "20110424_0287", "20110424_0288", "20110424_0289", "20110424_0292", "20110424_0294", "20110424_0295", "20110424_0296", "20110424_0298", "20110424_0300" 
};