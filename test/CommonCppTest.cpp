#include "CommonCppTest.h"
#include <string>
#include <vector>

//--------------------------------------------------------------------------------
// datafile
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_datafile)

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_fileNotFound)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_missingLabel)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_missingSeparator)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_inconsistentVectorDimensions)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_invalidZeroBasedIndex)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_invalidNonAscendingIndex)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_libsvm_validVectorData)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_fileNotFound)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_invalidSampleCount)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_invalidFeatureCount)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_missingHeader)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_missingLabel)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_inconsistentVectorDimensions)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_readSampleDataFile_binary_validVectorData)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_CASE(datafile_checkBinaryHeader)
{
    #if 0
    std::string filePath = "./datafile_checkBinaryHeader_validHeader.bin";
    std::string dummyHeader = "dummy header";
    std::vector<FeatureVector> samples(1);
    std::vector<int> labels(1);
    samples[1] = FeatureVector({ 1,2,3 });
    labels[1] = { 1 };
    DataFile::writeSampleDataFile(filePath, samples, labels, BINARY, dummyHeader);
    ifstream ifs(filePath);
    BOOST_CHECK(DataFile::checkBinaryHeader(ifs, dummyHeader));
    BOOST_CHECK(!DataFile::checkBinaryHeader(ifs, "random header"));
    #endif
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// dataChokePoint
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_datasetChokePoint)

BOOST_AUTO_TEST_CASE(ChokePoint_getSequenceString_ValidParameters_ReturnValidString)
{
    std::string seq;
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 1, 1);
    BOOST_CHECK_EQUAL(seq, "P1E_S1_C1");
    seq = ChokePoint::getSequenceString(2, ChokePoint::PortalType::LEAVE, 3, 2);
    BOOST_CHECK_EQUAL(seq, "P2L_S3_C2");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::LEAVE, 4, 3, 8);
    BOOST_CHECK_EQUAL(seq, "P1L_S4_C3/0008");
    seq = ChokePoint::getSequenceString(2, ChokePoint::PortalType::ENTER, 2, 1, 25);
    BOOST_CHECK_EQUAL(seq, "P2E_S2_C1/0025");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getSequenceString_InvalidParameterBounds_ReturnEmptyString)
{
    std::string seq;
    seq = ChokePoint::getSequenceString(0, ChokePoint::PortalType::ENTER, 1, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = ChokePoint::getSequenceString(3, ChokePoint::PortalType::ENTER, 1, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 0, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 6, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 4);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getSequenceString_InvalidIndividualID_ReturnOnlySequenceString)
{
    std::string seq;
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 1, -1);
    BOOST_CHECK_EQUAL(seq, "P1E_S2_C1");
    seq = ChokePoint::getSequenceString(1, ChokePoint::PortalType::LEAVE, 4, 3, 50);
    BOOST_CHECK_EQUAL(seq, "P1L_S4_C3");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getIndividualID_ValidParameters_ReturnValidString)
{
    std::string id;
    id = ChokePoint::getIndividualID(2, false);
    BOOST_CHECK_EQUAL(id, "0002");
    id = ChokePoint::getIndividualID(11, false);
    BOOST_CHECK_EQUAL(id, "0011");
    id = ChokePoint::getIndividualID(23, false);
    BOOST_CHECK_EQUAL(id, "0023");
    id = ChokePoint::getIndividualID(7, true);
    BOOST_CHECK_EQUAL(id, "ID0007");
    id = ChokePoint::getIndividualID(14, true);
    BOOST_CHECK_EQUAL(id, "ID0014");
    id = ChokePoint::getIndividualID(29, true);
    BOOST_CHECK_EQUAL(id, "ID0029");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getIndividualID_InvalidParameters_ReturnEmptyString)
{
    std::string id;
    id = ChokePoint::getIndividualID(0, false);
    BOOST_CHECK_EQUAL(id, "");
    id = ChokePoint::getIndividualID(-2, false);
    BOOST_CHECK_EQUAL(id, "");
    id = ChokePoint::getIndividualID(40, false);
    BOOST_CHECK_EQUAL(id, "");
    id = ChokePoint::getIndividualID(0, true);
    BOOST_CHECK_EQUAL(id, "");
    id = ChokePoint::getIndividualID(-1, true);
    BOOST_CHECK_EQUAL(id, "");
    id = ChokePoint::getIndividualID(31, true);
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_DirectoryConstants_NotEmpty)
{
    BOOST_CHECK_NE(ChokePoint::CROPPED_FACES_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(ChokePoint::GROUND_TRUTH_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(ChokePoint::STILL_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(ChokePoint::VIDEO_DIRECTORY_NAME, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_SequenceConstants_NotDefaultZero)
{
    BOOST_CHECK_NE(ChokePoint::INDIVIDUAL_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::PORTAL_TYPE_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::PORTAL_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::SESSION_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::SESSION_SIMULTANEOUS_INDIVIDUALS, 0);
    BOOST_CHECK_NE(ChokePoint::CAMERA_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::CAMERA_VIEWPOINT_QUANTITY, 0);
    BOOST_CHECK_NE(ChokePoint::TOTAL_SEQUENCES, 0);
    BOOST_CHECK_NE(ChokePoint::SEQUENCES_PER_CAMERA_VIEWPOINT, 0);
    BOOST_CHECK_NE(ChokePoint::SEQUENCES_PER_SESSION, 0);
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// dataCOXS2V
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_dataCOXS2V)

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidParamtersNoPseudoID_ReturnValidString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(1);
    BOOST_CHECK_EQUAL(seq, "video1");
    seq = COXS2V::getSequenceString(2);
    BOOST_CHECK_EQUAL(seq, "video2");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidParamtersWithPseudoID_ReturnValidString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(1, 1);
    BOOST_CHECK_EQUAL(seq, "video1/20110318_0001");
    seq = COXS2V::getSequenceString(4, 2);
    BOOST_CHECK_EQUAL(seq, "video4/20110318_0002");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideoValue_NoPseudoID_ReturnEmptyString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = COXS2V::getSequenceString(5);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidVideoValue_InvalidPseudoID_ReturnOnlySequenceString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(1, 0);
    BOOST_CHECK_EQUAL(seq, "video1");
    seq = COXS2V::getSequenceString(2, -10);
    BOOST_CHECK_EQUAL(seq, "video2");
    seq = COXS2V::getSequenceString(3, 2000);
    BOOST_CHECK_EQUAL(seq, "video3");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideo_InvalidPseudoID_ReturnEmptyString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(0, -1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = COXS2V::getSequenceString(-1, 0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = COXS2V::getSequenceString(20, 9000);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideo_ValidPseudoID_ReturnEmptyString)
{
    std::string seq;
    seq = COXS2V::getSequenceString(0, 1000);
    BOOST_CHECK_EQUAL(seq, "");
    seq = COXS2V::getSequenceString(-1, 100);
    BOOST_CHECK_EQUAL(seq, "");
    seq = COXS2V::getSequenceString(10, 200);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getIndividualID_ValidPseudoID_ReturnValidString)
{
    std::string id;
    id = COXS2V::getIndividualID(1,      false, false, false);
    BOOST_CHECK_EQUAL(id,               "20110318_0001");
    id = COXS2V::getIndividualID(1000,   false, false, false);
    BOOST_CHECK_EQUAL(id,               "20110424_0300");
    id = COXS2V::getIndividualID(1,      true , false, false);
    BOOST_CHECK_EQUAL(id,               "20110318_0001_0000");
    id = COXS2V::getIndividualID(1000,   true , false, false);
    BOOST_CHECK_EQUAL(id,               "20110424_0300_0000");

    id = COXS2V::getIndividualID(1,      false, false, true );
    BOOST_CHECK_EQUAL(id,               "20110318_0001");
    id = COXS2V::getIndividualID(1000,   false, false, true );
    BOOST_CHECK_EQUAL(id,               "20110424_0300");
    id = COXS2V::getIndividualID(1,      true , false, true );
    BOOST_CHECK_EQUAL(id,               "20110318_0001_0000");
    id = COXS2V::getIndividualID(1000,   true , false, true );
    BOOST_CHECK_EQUAL(id,               "20110424_0300_0000");

    id = COXS2V::getIndividualID(1,      false, true , false);
    BOOST_CHECK_EQUAL(id,               "0001");
    id = COXS2V::getIndividualID(1000,   false, true , false);
    BOOST_CHECK_EQUAL(id,               "1000");
    id = COXS2V::getIndividualID(1,      true , true , false);
    BOOST_CHECK_EQUAL(id,               "0001");
    id = COXS2V::getIndividualID(1000,   true , true , false);
    BOOST_CHECK_EQUAL(id,               "1000");

    id = COXS2V::getIndividualID(1,      false, true , true );
    BOOST_CHECK_EQUAL(id,               "ID0001");
    id = COXS2V::getIndividualID(1000,   false, true , true );
    BOOST_CHECK_EQUAL(id,               "ID1000");
    id = COXS2V::getIndividualID(1,      true , true , true );
    BOOST_CHECK_EQUAL(id,               "ID0001");
    id = COXS2V::getIndividualID(1000,   true , true , true );
    BOOST_CHECK_EQUAL(id,               "ID1000");
}

BOOST_AUTO_TEST_CASE(COXS2V_getIndividualID_InvalidPseudoID_ReturnEmptyString)
{
    std::string id;
    id = COXS2V::getIndividualID(0,      false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,     false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,   false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(0,      false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,     false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,   false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(0,      false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,     false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,   false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(0,      false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,     false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,   false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(0,       true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,      true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,    true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(0,       true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(-1,      true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getIndividualID(9000,    true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDIndexFromIDString_ValidPseudoID_ReturnValidIndex)
{
    int id;
    std::string id0001 = "20110318_0001", id1000 = "20110424_0300";
    id = COXS2V::getPseudoIDIndexFromIDString(id0001);
    BOOST_CHECK_EQUAL(id, 1);
    id = COXS2V::getPseudoIDIndexFromIDString(id1000);
    BOOST_CHECK_EQUAL(id, 1000);
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDIndexFromIDString_InvalidPseudoID_ReturnZero)
{
    int id;
    id = COXS2V::getPseudoIDIndexFromIDString("20110318_0001_0000");
    BOOST_CHECK_EQUAL(id, 0);
    id = COXS2V::getPseudoIDIndexFromIDString("20110318_9999");
    BOOST_CHECK_EQUAL(id, 0);
    id = COXS2V::getPseudoIDIndexFromIDString("ID0001");
    BOOST_CHECK_EQUAL(id, 0);
    id = COXS2V::getPseudoIDIndexFromIDString("0001");
    BOOST_CHECK_EQUAL(id, 0);
    id = COXS2V::getPseudoIDIndexFromIDString("");
    BOOST_CHECK_EQUAL(id, 0);
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDStringFromIDString_ValidPseudoID_ReturnValidString)
{
    std::string id;
    std::string id0001 = "20110318_0001", id1000 = "20110424_0300";
    id = COXS2V::getPseudoIDStringFromIDString(id0001, false);
    BOOST_CHECK_EQUAL(id, "0001");
    id = COXS2V::getPseudoIDStringFromIDString(id1000, false);
    BOOST_CHECK_EQUAL(id, "1000");
    id = COXS2V::getPseudoIDStringFromIDString(id0001, true);
    BOOST_CHECK_EQUAL(id, "ID0001");
    id = COXS2V::getPseudoIDStringFromIDString(id1000, true);
    BOOST_CHECK_EQUAL(id, "ID1000");
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDStringFromIDString_InvalidPseudoID_ReturnEmptyString)
{
    std::string id;
    id = COXS2V::getPseudoIDStringFromIDString("20110318_0001_0000", false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("20110318_9999", false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("ID0001", false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("0001", false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("", false);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("20110318_0001_0000", true);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("20110318_9999", true);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("ID0001", true);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("0001", true);
    BOOST_CHECK_EQUAL(id, "");
    id = COXS2V::getPseudoIDStringFromIDString("", true);
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_DirectoryConstants_NotEmpty)
{
    BOOST_CHECK_NE(COXS2V::EYES_GROUND_TRUTH_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(COXS2V::PUBLICATION_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(COXS2V::STILL_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(COXS2V::VIDEO_DIRECTORY_NAME, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_SequenceConstants_NotDefaultZero)
{
    BOOST_CHECK_NE(COXS2V::VIDEO_QUANTITY, 0);
    BOOST_CHECK_NE(COXS2V::CAMERA_QUANTITY, 0);
    BOOST_CHECK_NE(COXS2V::INDIVIDUAL_QUANTITY, 0);
    BOOST_CHECK_NE(COXS2V::TOTAL_SEQUENCES, 0);
}

BOOST_AUTO_TEST_CASE(COXS2V_IndividualIDsMap_NotEmptyValidSize)
{
    BOOST_REQUIRE_EQUAL(COXS2V::INDIVIDUAL_IDS.size(), COXS2V::INDIVIDUAL_QUANTITY);
    BOOST_CHECK_NE(COXS2V::INDIVIDUAL_IDS[0], "");
    BOOST_CHECK_NE(COXS2V::INDIVIDUAL_IDS[COXS2V::INDIVIDUAL_QUANTITY - 1], "");
}

BOOST_AUTO_TEST_CASE(COXS2V_IndividualIDsMap_EqualBoundaryStrings)
{
    BOOST_REQUIRE_EQUAL(COXS2V::INDIVIDUAL_IDS.size(), 1000);
    BOOST_CHECK_EQUAL(COXS2V::INDIVIDUAL_IDS[0],   "20110318_0001");
    BOOST_CHECK_EQUAL(COXS2V::INDIVIDUAL_IDS[10],  "20110318_0012");
    BOOST_CHECK_EQUAL(COXS2V::INDIVIDUAL_IDS[999], "20110424_0300");
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// eval
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_eval)

BOOST_AUTO_TEST_CASE(eval_undef)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()


//--------------------------------------------------------------------------------
// imgUtils
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_imgUtils)

BOOST_AUTO_TEST_CASE(imgUtils_undef_test)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// logging
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_logging)

BOOST_AUTO_TEST_CASE(logging_undef_test)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// norm
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_norm)

BOOST_AUTO_TEST_CASE(norm_undef_test)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// testing
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_testing)

BOOST_AUTO_TEST_CASE(testing_undef_test)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// timing
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_types)

BOOST_AUTO_TEST_CASE(types_undef_test)
{
    BOOST_WARN_MESSAGE(false, "tests not implemeneted");
}

BOOST_AUTO_TEST_SUITE_END()
