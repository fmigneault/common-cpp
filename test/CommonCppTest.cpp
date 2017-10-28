#include "CommonCppTest.h"

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
    string filePath = "./datafile_checkBinaryHeader_validHeader.bin";
    string dummyHeader = "dummy header";
    vector<FeatureVector> samples(1);
    vector<int> labels(1);
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
    string seq;    
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 1, 1);    
    BOOST_CHECK_EQUAL(seq, "P1E_S1_C1");
    seq = chokepoint.getSequenceString(2, ChokePoint::PortalType::LEAVE, 3, 2);
    BOOST_CHECK_EQUAL(seq, "P2L_S3_C2");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::LEAVE, 4, 3, 8);
    BOOST_CHECK_EQUAL(seq, "P1L_S4_C3/0008");
    seq = chokepoint.getSequenceString(2, ChokePoint::PortalType::ENTER, 2, 1, 25);
    BOOST_CHECK_EQUAL(seq, "P2E_S2_C1/0025");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getSequenceString_InvalidParameterBounds_ReturnEmptyString)
{
    string seq;
    seq = chokepoint.getSequenceString(0, ChokePoint::PortalType::ENTER, 1, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = chokepoint.getSequenceString(3, ChokePoint::PortalType::ENTER, 1, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 0, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 6, 1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 4);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getSequenceString_InvalidIndividualID_ReturnOnlySequenceString)
{
    string seq;
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::ENTER, 2, 1, -1);
    BOOST_CHECK_EQUAL(seq, "P1E_S2_C1");
    seq = chokepoint.getSequenceString(1, ChokePoint::PortalType::LEAVE, 4, 3, 50);
    BOOST_CHECK_EQUAL(seq, "P1L_S4_C3");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getIndividualID_ValidParameters_ReturnValidString)
{
    string id;
    id = chokepoint.getIndividualID(2, false);
    BOOST_CHECK_EQUAL(id, "0002");
    id = chokepoint.getIndividualID(11, false);
    BOOST_CHECK_EQUAL(id, "0011");
    id = chokepoint.getIndividualID(23, false);
    BOOST_CHECK_EQUAL(id, "0023");
    id = chokepoint.getIndividualID(7, true);
    BOOST_CHECK_EQUAL(id, "ID0007");
    id = chokepoint.getIndividualID(14, true);
    BOOST_CHECK_EQUAL(id, "ID0014");
    id = chokepoint.getIndividualID(29, true);
    BOOST_CHECK_EQUAL(id, "ID0029");
}

BOOST_AUTO_TEST_CASE(ChokePoint_getIndividualID_InvalidParameters_ReturnEmptyString)
{
    string id;
    id = chokepoint.getIndividualID(0, false);
    BOOST_CHECK_EQUAL(id, "");
    id = chokepoint.getIndividualID(-2, false);
    BOOST_CHECK_EQUAL(id, "");
    id = chokepoint.getIndividualID(40, false);
    BOOST_CHECK_EQUAL(id, "");
    id = chokepoint.getIndividualID(0, true);
    BOOST_CHECK_EQUAL(id, "");
    id = chokepoint.getIndividualID(-1, true);
    BOOST_CHECK_EQUAL(id, "");
    id = chokepoint.getIndividualID(31, true);
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_DirectoryConstants_NotEmpty)
{
    BOOST_CHECK_NE(chokepoint.CROPPED_FACES_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(chokepoint.GROUND_TRUTH_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(chokepoint.STILL_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(chokepoint.VIDEO_DIRECTORY_NAME, "");
}

BOOST_AUTO_TEST_CASE(ChokePoint_SequenceConstants_NotDefaultZero)
{
    BOOST_CHECK_NE(chokepoint.PORTAL_TYPE_QUANTITY, 0);
    BOOST_CHECK_NE(chokepoint.PORTAL_QUANTITY, 0);
    BOOST_CHECK_NE(chokepoint.SESSION_QUANTITY, 0);
    BOOST_CHECK_NE(chokepoint.SESSION_SIMULTANEOUS_INDIVIDUALS, 0);
    BOOST_CHECK_NE(chokepoint.CAMERA_QUANTITY, 0);
    BOOST_CHECK_NE(chokepoint.INDIVIDUAL_QUANTITY, 0);
    BOOST_CHECK_NE(chokepoint.TOTAL_SEQUENCES, 0);
}

BOOST_AUTO_TEST_SUITE_END()

//--------------------------------------------------------------------------------
// dataCOXS2V
//--------------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE(TestSuite_dataCOXS2V)

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidParamtersNoPseudoID_ReturnValidString)
{
    string seq;
    seq = coxs2v.getSequenceString(1);
    BOOST_CHECK_EQUAL(seq, "video1");
    seq = coxs2v.getSequenceString(2);
    BOOST_CHECK_EQUAL(seq, "video2");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidParamtersWithPseudoID_ReturnValidString)
{
    string seq;
    seq = coxs2v.getSequenceString(1, 1);
    BOOST_CHECK_EQUAL(seq, "video1/20110318_0001");
    seq = coxs2v.getSequenceString(4, 2);
    BOOST_CHECK_EQUAL(seq, "video4/20110318_0002");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideoValue_NoPseudoID_ReturnEmptyString)
{
    string seq;
    seq = coxs2v.getSequenceString(0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = coxs2v.getSequenceString(5);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_ValidVideoValue_InvalidPseudoID_ReturnOnlySequenceString)
{
    string seq;
    seq = coxs2v.getSequenceString(1, 0);
    BOOST_CHECK_EQUAL(seq, "video1");
    seq = coxs2v.getSequenceString(2, -10);
    BOOST_CHECK_EQUAL(seq, "video2");
    seq = coxs2v.getSequenceString(3, 2000);
    BOOST_CHECK_EQUAL(seq, "video3");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideo_InvalidPseudoID_ReturnEmptyString)
{
    string seq;
    seq = coxs2v.getSequenceString(0, -1);
    BOOST_CHECK_EQUAL(seq, "");
    seq = coxs2v.getSequenceString(-1, 0);
    BOOST_CHECK_EQUAL(seq, "");
    seq = coxs2v.getSequenceString(20, 9000);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getSequenceString_InvalidVideo_ValidPseudoID_ReturnEmptyString)
{
    string seq;
    seq = coxs2v.getSequenceString(0, 1000);
    BOOST_CHECK_EQUAL(seq, "");
    seq = coxs2v.getSequenceString(-1, 100);
    BOOST_CHECK_EQUAL(seq, "");
    seq = coxs2v.getSequenceString(10, 200);
    BOOST_CHECK_EQUAL(seq, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getIndividualID_ValidPseudoID_ReturnValidString)
{
    string id;
    id = coxs2v.getIndividualID(1,      false, false, false);
    BOOST_CHECK_EQUAL(id,               "20110318_0001");
    id = coxs2v.getIndividualID(1000,   false, false, false);
    BOOST_CHECK_EQUAL(id,               "20110424_0300");
    id = coxs2v.getIndividualID(1,      true , false, false);
    BOOST_CHECK_EQUAL(id,               "20110318_0001_0000");
    id = coxs2v.getIndividualID(1000,   true , false, false);
    BOOST_CHECK_EQUAL(id,               "20110424_0300_0000");

    id = coxs2v.getIndividualID(1,      false, false, true );
    BOOST_CHECK_EQUAL(id,               "20110318_0001");
    id = coxs2v.getIndividualID(1000,   false, false, true );
    BOOST_CHECK_EQUAL(id,               "20110424_0300");
    id = coxs2v.getIndividualID(1,      true , false, true );
    BOOST_CHECK_EQUAL(id,               "20110318_0001_0000");
    id = coxs2v.getIndividualID(1000,   true , false, true );
    BOOST_CHECK_EQUAL(id,               "20110424_0300_0000");
    
    id = coxs2v.getIndividualID(1,      false, true , false);
    BOOST_CHECK_EQUAL(id,               "0001");
    id = coxs2v.getIndividualID(1000,   false, true , false);
    BOOST_CHECK_EQUAL(id,               "1000");
    id = coxs2v.getIndividualID(1,      true , true , false);
    BOOST_CHECK_EQUAL(id,               "0001");
    id = coxs2v.getIndividualID(1000,   true , true , false);
    BOOST_CHECK_EQUAL(id,               "1000");

    id = coxs2v.getIndividualID(1,      false, true , true );
    BOOST_CHECK_EQUAL(id,               "ID0001");
    id = coxs2v.getIndividualID(1000,   false, true , true );
    BOOST_CHECK_EQUAL(id,               "ID1000");
    id = coxs2v.getIndividualID(1,      true , true , true );
    BOOST_CHECK_EQUAL(id,               "ID0001");
    id = coxs2v.getIndividualID(1000,   true , true , true );
    BOOST_CHECK_EQUAL(id,               "ID1000");
}

BOOST_AUTO_TEST_CASE(COXS2V_getIndividualID_InvalidPseudoID_ReturnEmptyString)
{
    string id;
    id = coxs2v.getIndividualID(0,      false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,     false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,   false, false, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(0,      false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,     false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,   false, false, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(0,      false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,     false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,   false,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(0,      false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,     false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,   false,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(0,       true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,      true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,    true,  true, false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(0,       true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(-1,      true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getIndividualID(9000,    true,  true, true );
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDIndexFromIDString_ValidPseudoID_ReturnValidIndex)
{
    int id;
    string id0001 = "20110318_0001", id1000 = "20110424_0300";    
    id = coxs2v.getPseudoIDIndexFromIDString(id0001);
    BOOST_CHECK_EQUAL(id, 1);
    id = coxs2v.getPseudoIDIndexFromIDString(id1000);
    BOOST_CHECK_EQUAL(id, 1000);
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDIndexFromIDString_InvalidPseudoID_ReturnZero)
{
    int id;
    id = coxs2v.getPseudoIDIndexFromIDString("20110318_0001_0000");
    BOOST_CHECK_EQUAL(id, 0);
    id = coxs2v.getPseudoIDIndexFromIDString("20110318_9999");
    BOOST_CHECK_EQUAL(id, 0);
    id = coxs2v.getPseudoIDIndexFromIDString("ID0001");
    BOOST_CHECK_EQUAL(id, 0);
    id = coxs2v.getPseudoIDIndexFromIDString("0001");
    BOOST_CHECK_EQUAL(id, 0);
    id = coxs2v.getPseudoIDIndexFromIDString("");
    BOOST_CHECK_EQUAL(id, 0);
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDStringFromIDString_ValidPseudoID_ReturnValidString)
{
    string id;
    string id0001 = "20110318_0001", id1000 = "20110424_0300";
    id = coxs2v.getPseudoIDStringFromIDString(id0001, false);
    BOOST_CHECK_EQUAL(id, "0001");
    id = coxs2v.getPseudoIDStringFromIDString(id1000, false);
    BOOST_CHECK_EQUAL(id, "1000");
    id = coxs2v.getPseudoIDStringFromIDString(id0001, true);
    BOOST_CHECK_EQUAL(id, "ID0001");
    id = coxs2v.getPseudoIDStringFromIDString(id1000, true);
    BOOST_CHECK_EQUAL(id, "ID1000");
}

BOOST_AUTO_TEST_CASE(COXS2V_getPseudoIDStringFromIDString_InvalidPseudoID_ReturnEmptyString)
{
    string id;
    id = coxs2v.getPseudoIDStringFromIDString("20110318_0001_0000", false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("20110318_9999", false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("ID0001", false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("0001", false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("", false);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("20110318_0001_0000", true);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("20110318_9999", true);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("ID0001", true);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("0001", true);
    BOOST_CHECK_EQUAL(id, "");
    id = coxs2v.getPseudoIDStringFromIDString("", true);
    BOOST_CHECK_EQUAL(id, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_DirectoryConstants_NotEmpty)
{
    BOOST_CHECK_NE(coxs2v.EYES_GROUND_TRUTH_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(coxs2v.PUBLICATION_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(coxs2v.STILL_DIRECTORY_NAME, "");
    BOOST_CHECK_NE(coxs2v.VIDEO_DIRECTORY_NAME, "");
}

BOOST_AUTO_TEST_CASE(COXS2V_SequenceConstants_NotDefaultZero)
{
    BOOST_CHECK_NE(coxs2v.VIDEO_QUANTITY, 0);
    BOOST_CHECK_NE(coxs2v.CAMERA_QUANTITY, 0);
    BOOST_CHECK_NE(coxs2v.INDIVIDUAL_QUANTITY, 0);
    BOOST_CHECK_NE(coxs2v.TOTAL_SEQUENCES, 0);
}

BOOST_AUTO_TEST_CASE(COXS2V_IndividualIDsMap_NotEmptyValidSize)
{
    BOOST_REQUIRE_EQUAL(coxs2v.INDIVIDUAL_IDS.size(), coxs2v.INDIVIDUAL_QUANTITY);
    BOOST_CHECK_NE(coxs2v.INDIVIDUAL_IDS[0], "");
    BOOST_CHECK_NE(coxs2v.INDIVIDUAL_IDS[coxs2v.INDIVIDUAL_QUANTITY - 1], "");
}

BOOST_AUTO_TEST_CASE(COXS2V_IndividualIDsMap_EqualBoundaryStrings)
{
    BOOST_REQUIRE_EQUAL(coxs2v.INDIVIDUAL_IDS.size(), 1000);
    BOOST_CHECK_EQUAL(coxs2v.INDIVIDUAL_IDS[0],   "20110318_0001");
    BOOST_CHECK_EQUAL(coxs2v.INDIVIDUAL_IDS[10],  "20110318_0012");
    BOOST_CHECK_EQUAL(coxs2v.INDIVIDUAL_IDS[999], "20110424_0300");
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
