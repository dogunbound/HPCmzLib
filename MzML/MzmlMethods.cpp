﻿#include "MzmlMethods.h"
#include "../MassSpectrometry/IMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScan.h"
#include "../MassSpectrometry/MzSpectra/IMzPeak.h"
#include "../MassSpectrometry/MzSpectra/IMzSpectrum.h"
#include "XSD/IO.MzML.Generated.mzMLType.h"
#include "XSD/IO.MzML.Generated.CVListType.h"
#include "XSD/IO.MzML.Generated.CVType.h"
#include "XSD/IO.MzML.Generated.FileDescriptionType.h"
#include "XSD/IO.MzML.Generated.ParamGroupType.h"
#include "XSD/IO.MzML.Generated.SourceFileListType.h"
#include "XSD/IO.MzML.Generated.SourceFileType.h"
#include "XSD/IO.MzML.Generated.CVParamType.h"
#include "XSD/IO.MzML.Generated.SoftwareListType.h"
#include "XSD/IO.MzML.Generated.SoftwareType.h"
#include "XSD/IO.MzML.Generated.InstrumentConfigurationListType.h"
#include "XSD/IO.MzML.Generated.InstrumentConfigurationType.h"
#include "XSD/IO.MzML.Generated.ComponentListType.h"
#include "XSD/IO.MzML.Generated.SourceComponentType.h"
#include "XSD/IO.MzML.Generated.AnalyzerComponentType.h"
#include "XSD/IO.MzML.Generated.DetectorComponentType.h"
#include "XSD/IO.MzML.Generated.DataProcessingListType.h"
#include "XSD/IO.MzML.Generated.DataProcessingType.h"
#include "XSD/IO.MzML.Generated.ProcessingMethodType.h"
#include "XSD/IO.MzML.Generated.RunType.h"
#include "XSD/IO.MzML.Generated.ChromatogramListType.h"
#include "XSD/IO.MzML.Generated.ChromatogramType.h"
#include "XSD/IO.MzML.Generated.BinaryDataArrayListType.h"
#include "XSD/IO.MzML.Generated.BinaryDataArrayType.h"
#include "../MassSpectrometry/MzSpectra/MzPeak.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "XSD/IO.MzML.Generated.SpectrumListType.h"
#include "XSD/IO.MzML.Generated.SpectrumType.h"
#include "XSD/IO.MzML.Generated.ScanListType.h"
#include "XSD/IO.MzML.Generated.ScanType.h"
#include "../MassSpectrometry/DataScan/IMsDataScanWithPrecursor.h"
#include "XSD/IO.MzML.Generated.PrecursorListType.h"
#include "XSD/IO.MzML.Generated.PrecursorType.h"
#include "XSD/IO.MzML.Generated.SelectedIonListType.h"
#include "../MzLibUtil/MzRange.h"
#include "XSD/IO.MzML.Generated.UserParamType.h"
#include "XSD/IO.MzML.Generated.ScanWindowListType.h"
#include "XSD/IO.MzML.Generated.indexedmzML.h"
#include "XSD/IO.MzML.Generated.IndexListType.h"
#include "XSD/IO.MzML.Generated.IndexType.h"
#include "XSD/mzML1_1_1_idx.h"
#include "XSD/IO.MzML.Generated.OffsetType.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO {
    namespace MzML {

XmlSerializer *const MzmlMethods::indexedSerializer = new XmlSerializer(Generated::indexedmzML::typeid);
XmlSerializer *const MzmlMethods::mzmlSerializer = new XmlSerializer(Generated::mzMLType::typeid);
const std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeAccessions = std::unordered_map<DissociationType, std::string> {
    {DissociationType::CID, "MS:1000133"}, {
    {DissociationType::HCD, "MS:1000422"}, {
    {DissociationType::MPD, "MS:1000435"}, {
    {DissociationType::Unknown, "MS:1000044"}
    };
const std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeNames = std::unordered_map<DissociationType, std::string> {
    {DissociationType::CID, "collision-induced dissociation"}, {
    {DissociationType::HCD, "beam-type collision-induced dissociation"}, {
    {DissociationType::MPD, "photodissociation"}, {
    {DissociationType::Unknown, "dissociation method"}
    };
const std::unordered_map<MZAnalyzerType, std::string> MzmlMethods::analyzerDictionary = std::unordered_map<MZAnalyzerType, std::string> {
    {MZAnalyzerType::Unknown, "MS:1000443"}, {
    {MZAnalyzerType::IonTrap2D, "MS:1000291"}, {
    {MZAnalyzerType::Orbitrap,"MS:1000484"}, {
    {MZAnalyzerType::FTICR,"MS:1000079"}, {
    };
const std::unordered_map<std::string, std::string> MzmlMethods::nativeIdFormatAccessions = std::unordered_map<std::string, std::string> {
    {"scan number only nativeID format", "MS:1000776"}, {
    {"no nativeID format", "MS:1000824"}
    };
const std::unordered_map<std::string, std::string> MzmlMethods::MassSpectrometerFileFormatAccessions = std::unordered_map<std::string, std::string> {
    {"Thermo RAW format", "MS:1000563"}, {
    };
const std::unordered_map<std::string, std::string> MzmlMethods::FileChecksumAccessions = std::unordered_map<std::string, std::string> {
    {"MD5", "MS:1000568"}, {
    };
const std::unordered_map<bool, std::string> MzmlMethods::CentroidAccessions = std::unordered_map<bool, std::string> {
    {true, "MS:1000127"}, {
    };
const std::unordered_map<bool, std::string> MzmlMethods::CentroidNames = std::unordered_map<bool, std::string> {
    {true, "centroid spectrum"}, {
    };
const std::unordered_map<Polarity, std::string> MzmlMethods::PolarityAccessions = std::unordered_map<Polarity, std::string> {
    {Polarity::Negative, "MS:1000129"}, {
    };
const std::unordered_map<Polarity, std::string> MzmlMethods::PolarityNames = std::unordered_map<Polarity, std::string> {
    {Polarity::Negative, "negative scan"}, {
    };

        void MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *myMsDataFile, const std::string &outputFile, bool writeIndexed) {
            std::string title = System::IO::Path::GetFileNameWithoutExtension(outputFile);

            auto mzML = new Generated::mzMLType();
            mzML->setversion("1.1.0");
            Generated::CVListType tempVar();
            mzML->setcvList(&tempVar);
            mzML->setid(title);

            Generated::CVListType tempVar2();
            mzML->setcvList(&tempVar2);
            mzML->getcvList()->setcount("2");
            mzML->getcvList()->setcv(std::vector<Generated::CVType*>(2));
            Generated::CVType *tempVar3 = new Generated::CVType();
            tempVar3->setURI(LR"(https://raw.githubusercontent.com/HUPO-PSI/psi-ms-CV/master/psi-ms.obo)");
            tempVar3->setfullName("Proteomics Standards Initiative Mass Spectrometry Ontology");
            tempVar3->setid("MS");
            tempVar3->setversion("4.0.1");
            mzML->getcvList()->getcv()[0] = tempVar3;

            Generated::CVType *tempVar4 = new Generated::CVType();
            tempVar4->setURI(LR"(http://obo.cvs.sourceforge.net/*checkout*/obo/obo/ontology/phenotype/unit.obo)");
            tempVar4->setfullName("Unit Ontology");
            tempVar4->setid("UO");
            tempVar4->setversion("12:10:2011");
            mzML->getcvList()->getcv()[1] = tempVar4;

            Generated::FileDescriptionType tempVar5();
            mzML->setfileDescription(&tempVar5);
            Generated::ParamGroupType tempVar6();
            mzML->getfileDescription()->setfileContent(&tempVar6);
            Generated::SourceFileListType tempVar7();
            mzML->getfileDescription()->setsourceFileList(&tempVar7);

            if (myMsDataFile->getSourceFile()->getNativeIdFormat() != "" && myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat() != "" && myMsDataFile->getSourceFile()->getFileChecksumType() != "") {
                Generated::SourceFileListType tempVar8();
                mzML->getfileDescription()->setsourceFileList(&tempVar8);
                mzML->getfileDescription()->getsourceFileList()->setcount("1");
                mzML->getfileDescription()->getsourceFileList()->setsourceFile(std::vector<Generated::SourceFileType*>(1));

                Generated::SourceFileType *tempVar9 = new Generated::SourceFileType();
                tempVar9->setid(myMsDataFile->getSourceFile()->getFileName());
                tempVar9->setname(myMsDataFile->getSourceFile()->getFileName());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar9->setlocation(myMsDataFile->getSourceFile()->getUri()->ToString());
                mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0] = tempVar9;

                mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam = std::vector<Generated::CVParamType*>(3);
                Generated::CVParamType *tempVar10 = new Generated::CVParamType();
                tempVar10->setaccession(nativeIdFormatAccessions[myMsDataFile->getSourceFile()->getNativeIdFormat()]);
                tempVar10->setname(myMsDataFile->getSourceFile()->getNativeIdFormat());
                tempVar10->setcvRef("MS");
                tempVar10->setvalue("");
                mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[0] = tempVar10;
                Generated::CVParamType *tempVar11 = new Generated::CVParamType();
                tempVar11->setaccession(MassSpectrometerFileFormatAccessions[myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat()]);
                tempVar11->setname(myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat());
                tempVar11->setcvRef("MS");
                tempVar11->setvalue("");
                mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[1] = tempVar11;
                Generated::CVParamType *tempVar12 = new Generated::CVParamType();
                tempVar12->setaccession(FileChecksumAccessions[myMsDataFile->getSourceFile()->getFileChecksumType()]);
                tempVar12->setname(myMsDataFile->getSourceFile()->getFileChecksumType());
                tempVar12->setcvRef("MS");
                std::string tempVar13 = myMsDataFile.getSourceFile().getCheckSum();
                tempVar12->setvalue((tempVar13 != nullptr) ? tempVar13 : "");
                mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[2] = tempVar12;
            }

            mzML->getfileDescription()->getfileContent()->setcvParam(std::vector<Generated::CVParamType*>(2));
            Generated::CVParamType *tempVar14 = new Generated::CVParamType();
            tempVar14->setaccession("MS:1000579");
            tempVar14->setname("MS1 spectrum");
            tempVar14->setcvRef("MS");
            tempVar14->setvalue("");
            mzML->getfileDescription()->getfileContent()->getcvParam()[0] = tempVar14;
            Generated::CVParamType *tempVar15 = new Generated::CVParamType();
            tempVar15->setaccession("MS:1000580");
            tempVar15->setname("MSn spectrum");
            tempVar15->setcvRef("MS");
            tempVar15->setvalue("");
            mzML->getfileDescription()->getfileContent()->getcvParam()[1] = tempVar15;

            Generated::SoftwareListType tempVar16();
            mzML->setsoftwareList(&tempVar16);
            mzML->getsoftwareList()->setcount("2");
            mzML->getsoftwareList()->setsoftware(std::vector<Generated::SoftwareType*>(2));

            // TODO: add the raw file fields
            Generated::SoftwareType *tempVar17 = new Generated::SoftwareType();
            tempVar17->setid("mzLib");
            tempVar17->setversion("1");
            tempVar17->setcvParam(std::vector<Generated::CVParamType*>(1));
            mzML->getsoftwareList()->getsoftware()[0] = tempVar17;

            Generated::CVParamType *tempVar18 = new Generated::CVParamType();
            tempVar18->setaccession("MS:1000799");
            tempVar18->setvalue("mzLib");
            tempVar18->setname("custom unreleased software tool");
            tempVar18->setcvRef("MS");
            mzML->getsoftwareList()->getsoftware()[0]->cvParam[0] = tempVar18;

            std::vector<MZAnalyzerType> analyzersInThisFile = (std::unordered_set<MZAnalyzerType>(myMsDataFile->Select([&] (std::any b) {
                b::MzAnalyzer;
            })))->ToList();
            std::unordered_map<MZAnalyzerType, std::string> analyzersInThisFileDict;

            // Leaving empty. Can't figure out the configurations.
            // ToDo: read instrumentConfigurationList from mzML file
            Generated::InstrumentConfigurationListType tempVar19();
            mzML->setinstrumentConfigurationList(&tempVar19);
            mzML->getinstrumentConfigurationList()->setcount(std::to_string(analyzersInThisFile.size()));
            mzML->getinstrumentConfigurationList()->setinstrumentConfiguration(std::vector<Generated::InstrumentConfigurationType*>(analyzersInThisFile.size()));

            // Write the analyzers, also the default, also in the scans if needed

            for (int i = 0; i < mzML->getinstrumentConfigurationList()->getinstrumentConfiguration().size(); i++) {
                analyzersInThisFileDict[analyzersInThisFile[i]] = "IC" + std::to_string(i + 1);
                Generated::InstrumentConfigurationType *tempVar20 = new Generated::InstrumentConfigurationType();
                tempVar20->setid("IC" + std::to_string(i + 1));
                Generated::ComponentListType tempVar21();
                tempVar20->setcomponentList(&tempVar21);
                tempVar20->setcvParam(std::vector<Generated::CVParamType*>(1));
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i] = tempVar20;

                Generated::CVParamType *tempVar22 = new Generated::CVParamType();
                tempVar22->setcvRef("MS");
                tempVar22->setaccession("MS:1000031");
                tempVar22->setname("instrument model");
                tempVar22->setvalue("");
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->cvParam[0] = tempVar22;

                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList = new Generated::ComponentListType();
                .componentList->count = std::to_string(3);
                .componentList->source = std::vector<Generated::SourceComponentType*>(1);
                .componentList->analyzer = std::vector<Generated::AnalyzerComponentType*>(1);
                .componentList->detector = std::vector<Generated::DetectorComponentType*>(1);

                Generated::SourceComponentType *tempVar23 = new Generated::SourceComponentType();
                tempVar23->setorder(1);
                tempVar23->setcvParam(std::vector<Generated::CVParamType*>(1));
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.source[0] = tempVar23;
                Generated::CVParamType *tempVar24 = new Generated::CVParamType();
                tempVar24->setcvRef("MS");
                tempVar24->setaccession("MS:1000008");
                tempVar24->setname("ionization type");
                tempVar24->setvalue("");
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.source[0].cvParam[0] = tempVar24;

                Generated::AnalyzerComponentType *tempVar25 = new Generated::AnalyzerComponentType();
                tempVar25->setorder(2);
                tempVar25->setcvParam(std::vector<Generated::CVParamType*>(1));
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.analyzer[0] = tempVar25;

                Generated::CVParamType *tempVar26 = new Generated::CVParamType();
                tempVar26->setcvRef("MS");
                tempVar26->setaccession(analyzerDictionary[analyzersInThisFile[i]]);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar26->setname(analyzersInThisFile[i].ToString()->ToLower());
                tempVar26->setvalue("");
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.analyzer[0].cvParam[0] = tempVar26;

                Generated::DetectorComponentType *tempVar27 = new Generated::DetectorComponentType();
                tempVar27->setorder(3);
                tempVar27->setcvParam(std::vector<Generated::CVParamType*>(1));
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.detector[0] = tempVar27;
                Generated::CVParamType *tempVar28 = new Generated::CVParamType();
                tempVar28->setcvRef("MS");
                tempVar28->setaccession("MS:1000026");
                tempVar28->setname("detector type");
                tempVar28->setvalue("");
                mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.detector[0].cvParam[0] = tempVar28;
            }

            Generated::DataProcessingListType tempVar29();
            mzML->setdataProcessingList(&tempVar29);
            mzML->getdataProcessingList()->setcount("1");
            mzML->getdataProcessingList()->setdataProcessing(std::vector<Generated::DataProcessingType*>(1));

            // Only writing mine! Might have had some other data processing (but not if it is a raw file)
            // ToDo: read dataProcessingList from mzML file
            Generated::DataProcessingType *tempVar30 = new Generated::DataProcessingType();
            tempVar30->setid("mzLibProcessing");
            tempVar30->setprocessingMethod(std::vector<Generated::ProcessingMethodType*>(1));
            mzML->getdataProcessingList()->getdataProcessing()[0] = tempVar30;

            Generated::ProcessingMethodType *tempVar31 = new Generated::ProcessingMethodType();
            tempVar31->setorder("0");
            tempVar31->setsoftwareRef("mzLib");
            tempVar31->setcvParam(std::vector<Generated::CVParamType*>(1));
            mzML->getdataProcessingList()->getdataProcessing()[0]->processingMethod[0] = tempVar31;

            Generated::CVParamType *tempVar32 = new Generated::CVParamType();
            tempVar32->setaccession("MS:1000452");
            tempVar32->setcvRef("MS");
            tempVar32->setname("data transformation");
            tempVar32->setvalue("");
            mzML->getdataProcessingList()->getdataProcessing()[0]->processingMethod[0].cvParam[0] = tempVar32;
            Generated::RunType tempVar33();
            mzML->setrun(&tempVar33);
            mzML->getrun()->setdefaultInstrumentConfigurationRef(analyzersInThisFileDict[analyzersInThisFile[0]]);
            mzML->getrun()->setid(title);

            Generated::ChromatogramListType tempVar34();
            mzML->getrun()->setchromatogramList(&tempVar34);
            mzML->getrun()->getchromatogramList()->setcount("1");
            mzML->getrun()->getchromatogramList()->setchromatogram(std::vector<Generated::ChromatogramType*>(1));
            mzML->getrun()->getchromatogramList()->setdefaultDataProcessingRef("mzLibProcessing");

            //Chromatagram info
            Generated::ChromatogramType *tempVar35 = new Generated::ChromatogramType();
            tempVar35->setdefaultArrayLength(myMsDataFile->getNumSpectra());
            tempVar35->setid("TIC");
            tempVar35->setindex("0");
            tempVar35->setdataProcessingRef("mzLibProcessing");
            Generated::BinaryDataArrayListType tempVar36();
            tempVar35->setbinaryDataArrayList(&tempVar36);
            tempVar35->getbinaryDataArrayList()->setcount("2");
            tempVar35->getbinaryDataArrayList()->setbinaryDataArray(std::vector<Generated::BinaryDataArrayType*>(2));
            tempVar35->setcvParam(std::vector<Generated::CVParamType*>(1));
            mzML->getrun()->getchromatogramList()->getchromatogram()[0] = tempVar35;

            Generated::CVParamType *tempVar37 = new Generated::CVParamType();
            tempVar37->setaccession("MS:1000235");
            tempVar37->setname("total ion current chromatogram");
            tempVar37->setcvRef("MS");
            tempVar37->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->cvParam[0] = tempVar37;

            std::vector<double> times(myMsDataFile->getNumSpectra());
            std::vector<double> intensities(myMsDataFile->getNumSpectra());

            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++) {
                times[i - 1] = myMsDataFile->GetOneBasedScan(i)->getRetentionTime();
                intensities[i - 1] = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->SumOfAllY;
            }

            //Chromatofram X axis (time)
            Generated::BinaryDataArrayType *tempVar38 = new Generated::BinaryDataArrayType();
            tempVar38->setbinary(MzSpectrum<MzPeak*>::Get64Bitarray(times));
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0] = tempVar38;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);

            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0]->cvParam = std::vector<Generated::CVParamType*>(3);

            Generated::CVParamType *tempVar39 = new Generated::CVParamType();
            tempVar39->setaccession("MS:1000523");
            tempVar39->setname("64-bit float");
            tempVar39->setcvRef("MS");
            tempVar39->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].cvParam[0] = tempVar39;

            Generated::CVParamType *tempVar40 = new Generated::CVParamType();
            tempVar40->setaccession("MS:1000576");
            tempVar40->setname("no compression");
            tempVar40->setcvRef("MS");
            tempVar40->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].cvParam[1] = tempVar40;

            Generated::CVParamType *tempVar41 = new Generated::CVParamType();
            tempVar41->setaccession("MS:1000595");
            tempVar41->setname("time array");
            tempVar41->setunitCvRef("UO");
            tempVar41->setunitAccession("UO:0000031");
            tempVar41->setunitName("Minutes");
            tempVar41->setcvRef("MS");
            tempVar41->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].cvParam[2] = tempVar41;

            //Chromatogram Y axis (total intensity)
            Generated::BinaryDataArrayType *tempVar42 = new Generated::BinaryDataArrayType();
            tempVar42->setbinary(MzSpectrum<MzPeak*>::Get64Bitarray(intensities));
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1] = tempVar42;

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);

            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1]->cvParam = std::vector<Generated::CVParamType*>(3);

            Generated::CVParamType *tempVar43 = new Generated::CVParamType();
            tempVar43->setaccession("MS:1000523");
            tempVar43->setname("64-bit float");
            tempVar43->setcvRef("MS");
            tempVar43->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1].cvParam[0] = tempVar43;

            Generated::CVParamType *tempVar44 = new Generated::CVParamType();
            tempVar44->setaccession("MS:1000576");
            tempVar44->setname("no compression");
            tempVar44->setcvRef("MS");
            tempVar44->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1].cvParam[1] = tempVar44;

            Generated::CVParamType *tempVar45 = new Generated::CVParamType();
            tempVar45->setaccession("MS:1000515");
            tempVar45->setname("intensity array");
            tempVar45->setunitCvRef("MS");
            tempVar45->setunitAccession("MS:1000131");
            tempVar45->setunitName("number of counts");
            tempVar45->setcvRef("MS");
            tempVar45->setvalue("");
            mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1].cvParam[2] = tempVar45;

            Generated::SpectrumListType tempVar46();
            mzML->getrun()->setspectrumList(&tempVar46);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            mzML->getrun()->getspectrumList()->setcount((myMsDataFile->getNumSpectra()).ToString(CultureInfo::InvariantCulture));
            mzML->getrun()->getspectrumList()->setdefaultDataProcessingRef("mzLibProcessing");
            mzML->getrun()->getspectrumList()->setspectrum(std::vector<Generated::SpectrumType*>(myMsDataFile->getNumSpectra()));

            // Loop over all spectra
            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++) {
                Generated::SpectrumType *tempVar47 = new Generated::SpectrumType();
                tempVar47->setdefaultArrayLength(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->YArray->Length);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar47->setindex((i - 1).ToString(CultureInfo::InvariantCulture));
                tempVar47->setid(myMsDataFile->GetOneBasedScan(i)->getNativeId());
                tempVar47->setcvParam(std::vector<Generated::CVParamType*>(9));
                Generated::ScanListType tempVar48();
                tempVar47->setscanList(&tempVar48);
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1] = tempVar47;

                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList = new Generated::ScanListType();
                .scanList->count = std::to_string(1);
                .scanList->scan = std::vector<Generated::ScanType*>(1);
                .scanList->cvParam = std::vector<Generated::CVParamType*>(1);
                Generated::CVParamType *tempVar49 = new Generated::CVParamType();
                tempVar49->setcvRef("MS");
                tempVar49->setaccession("MS:1000570");
                tempVar49->setname("spectra combination");
                tempVar49->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.cvParam[0] = tempVar49;
                auto h = myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer();
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0] = new Generated::ScanType { };

                if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() == 1) {
                    Generated::CVParamType *tempVar50 = new Generated::CVParamType();
                    tempVar50->setaccession("MS:1000579");
                    tempVar50->setcvRef("MS");
                    tempVar50->setname("MS1 spectrum");
                    tempVar50->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[0] = tempVar50;
                }
                else if (dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(myMsDataFile->GetOneBasedScan(i)) != nullptr) {
                    auto scanWithPrecursor = dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(myMsDataFile->GetOneBasedScan(i));
                    Generated::CVParamType *tempVar51 = new Generated::CVParamType();
                    tempVar51->setaccession("MS:1000580");
                    tempVar51->setcvRef("MS");
                    tempVar51->setname("MSn spectrum");
                    tempVar51->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[0] = tempVar51;

                    // So needs a precursor!
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList = new Generated::PrecursorListType();
                    .precursorList->count = std::to_string(1);
                    .precursorList->precursor = std::vector<Generated::PrecursorType*>(1);
                    Generated::PrecursorType *tempVar52 = new Generated::PrecursorType();
                    Generated::SelectedIonListType tempVar53();
                    tempVar52->setselectedIonList(&tempVar53);
                    tempVar52->getselectedIonList()->setcount(std::to_string(1));
                    tempVar52->getselectedIonList()->setselectedIon(std::vector<Generated::ParamGroupType*>(1));
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0] = tempVar52;

                    if (scanWithPrecursor->getOneBasedPrecursorScanNumber().HasValue) {
                        auto precursorID = myMsDataFile->GetOneBasedScan(scanWithPrecursor->getOneBasedPrecursorScanNumber().Value)->getNativeId();
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0]->spectrumRef = precursorID;
                    }

                    Generated::ParamGroupType *tempVar54 = new Generated::ParamGroupType();
                    tempVar54->setcvParam(std::vector<Generated::CVParamType*>(3));
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].selectedIonList.selectedIon[0] = tempVar54;

                    // Selected ion MZ
                    Generated::CVParamType *tempVar55 = new Generated::CVParamType();
                    tempVar55->setname("selected ion m/z");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    tempVar55->setvalue(scanWithPrecursor->getSelectedIonMZ().ToString(CultureInfo::InvariantCulture));
                    tempVar55->setaccession("MS:1000744");
                    tempVar55->setcvRef("MS");
                    tempVar55->setunitCvRef("MS");
                    tempVar55->setunitAccession("MS:1000040");
                    tempVar55->setunitName("m/z");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].selectedIonList.selectedIon[0].cvParam[0] = tempVar55;

                    // Charge State
                    if (scanWithPrecursor->getSelectedIonChargeStateGuess().HasValue) {
                        Generated::CVParamType *tempVar56 = new Generated::CVParamType();
                        tempVar56->setname("charge state");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar56->setvalue(scanWithPrecursor->getSelectedIonChargeStateGuess().Value.ToString(CultureInfo::InvariantCulture));
                        tempVar56->setaccession("MS:1000041");
                        tempVar56->setcvRef("MS");
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].selectedIonList.selectedIon[0].cvParam[1] = tempVar56;
                    }

                    // Selected ion intensity
                    if (scanWithPrecursor->getSelectedIonIntensity().HasValue) {
                        Generated::CVParamType *tempVar57 = new Generated::CVParamType();
                        tempVar57->setname("peak intensity");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar57->setvalue(scanWithPrecursor->getSelectedIonIntensity().Value.ToString(CultureInfo::InvariantCulture));
                        tempVar57->setaccession("MS:1000042");
                        tempVar57->setcvRef("MS");
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].selectedIonList.selectedIon[0].cvParam[2] = tempVar57;
                    }
                    if (scanWithPrecursor->getIsolationMz().HasValue) {
                        MzRange *isolationRange = scanWithPrecursor->getIsolationRange();
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0]->isolationWindow = new Generated::ParamGroupType();
                        .isolationWindow->cvParam = std::vector<Generated::CVParamType*>(3);
                        Generated::CVParamType *tempVar58 = new Generated::CVParamType();
                        tempVar58->setaccession("MS:1000827");
                        tempVar58->setname("isolation window target m/z");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar58->setvalue(isolationRange->getMean().ToString(CultureInfo::InvariantCulture));
                        tempVar58->setcvRef("MS");
                        tempVar58->setunitCvRef("MS");
                        tempVar58->setunitAccession("MS:1000040");
                        tempVar58->setunitName("m/z");
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].isolationWindow.cvParam[0] = tempVar58;
                        Generated::CVParamType *tempVar59 = new Generated::CVParamType();
                        tempVar59->setaccession("MS:1000828");
                        tempVar59->setname("isolation window lower offset");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar59->setvalue((isolationRange->getWidth() / 2).ToString(CultureInfo::InvariantCulture));
                        tempVar59->setcvRef("MS");
                        tempVar59->setunitCvRef("MS");
                        tempVar59->setunitAccession("MS:1000040");
                        tempVar59->setunitName("m/z");
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].isolationWindow.cvParam[1] = tempVar59;
                        Generated::CVParamType *tempVar60 = new Generated::CVParamType();
                        tempVar60->setaccession("MS:1000829");
                        tempVar60->setname("isolation window upper offset");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar60->setvalue((isolationRange->getWidth() / 2).ToString(CultureInfo::InvariantCulture));
                        tempVar60->setcvRef("MS");
                        tempVar60->setunitCvRef("MS");
                        tempVar60->setunitAccession("MS:1000040");
                        tempVar60->setunitName("m/z");
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].isolationWindow.cvParam[2] = tempVar60;
                    }
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0]->activation = new Generated::ParamGroupType();
                    .activation->cvParam = std::vector<Generated::CVParamType*>(1);
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].activation.cvParam[0] = new Generated::CVParamType();

                    DissociationType dissociationType = scanWithPrecursor->getDissociationType();

                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].activation.cvParam[0]->accession = DissociationTypeAccessions[dissociationType];
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].activation.cvParam[0]->name = DissociationTypeNames[dissociationType];
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].activation.cvParam[0]->cvRef = "MS";
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->precursorList.precursor[0].activation.cvParam[0]->value = "";
                }

                Generated::CVParamType *tempVar61 = new Generated::CVParamType();
                tempVar61->setname("ms level");
                tempVar61->setaccession("MS:1000511");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar61->setvalue(myMsDataFile->GetOneBasedScan(i)->getMsnOrder().ToString(CultureInfo::InvariantCulture));
                tempVar61->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[1] = tempVar61;
                Generated::CVParamType *tempVar62 = new Generated::CVParamType();
                tempVar62->setname(CentroidNames[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                tempVar62->setaccession(CentroidAccessions[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                tempVar62->setcvRef("MS");
                tempVar62->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[2] = tempVar62;
                string polarityName;
                string polarityAccession;
                std::unordered_map<Polarity, std::string>::const_iterator PolarityAccessions_iterator = PolarityAccessions.find(myMsDataFile.GetOneBasedScan(i).Polarity);
                std::unordered_map<Polarity, std::string>::const_iterator PolarityNames_iterator = PolarityNames.find(myMsDataFile.GetOneBasedScan(i).Polarity);
                if (PolarityNames_iterator != PolarityNames.end() && PolarityAccessions_iterator != PolarityAccessions.end()) {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                    Generated::CVParamType *tempVar63 = new Generated::CVParamType();
                    tempVar63->setname(polarityName);
                    tempVar63->setaccession(polarityAccession);
                    tempVar63->setcvRef("MS");
                    tempVar63->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[3] = tempVar63;
                }
                else {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                }
                // Spectrum title
                //string title = System.IO.Path.GetFileNameWithoutExtension(outputFile);

                if ((myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Size) > 0) {
                    // Lowest observed mz
                    Generated::CVParamType *tempVar64 = new Generated::CVParamType();
                    tempVar64->setname("lowest observed m/z");
                    tempVar64->setaccession("MS:1000528");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    tempVar64->setvalue(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->FirstX.ToString(CultureInfo::InvariantCulture));
                    tempVar64->setunitCvRef("MS");
                    tempVar64->setunitAccession("MS:1000040");
                    tempVar64->setunitName("m/z");
                    tempVar64->setcvRef("MS");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[4] = tempVar64;

                    // Highest observed mz
                    Generated::CVParamType *tempVar65 = new Generated::CVParamType();
                    tempVar65->setname("highest observed m/z");
                    tempVar65->setaccession("MS:1000527");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    tempVar65->setvalue(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->LastX.ToString(CultureInfo::InvariantCulture));
                    tempVar65->setunitAccession("MS:1000040");
                    tempVar65->setunitName("m/z");
                    tempVar65->setcvRef("MS");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[5] = tempVar65;
                }

                // Total ion current
                Generated::CVParamType *tempVar66 = new Generated::CVParamType();
                tempVar66->setname("total ion current");
                tempVar66->setaccession("MS:1000285");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar66->setvalue(myMsDataFile->GetOneBasedScan(i)->getTotalIonCurrent().ToString(CultureInfo::InvariantCulture));
                tempVar66->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[6] = tempVar66;

                //base peak m/z
                Generated::CVParamType *tempVar67 = new Generated::CVParamType();
                tempVar67->setname("base peak m/z");
                tempVar67->setaccession("MS:1000504");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar67->setvalue(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->XofPeakWithHighestY.ToString());
                tempVar67->setunitCvRef("MS");
                tempVar67->setunitName("m/z");
                tempVar67->setunitAccession("MS:1000040");
                tempVar67->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[7] = tempVar67;

                //base peak intensity
                Generated::CVParamType *tempVar68 = new Generated::CVParamType();
                tempVar68->setname("base peak intensity");
                tempVar68->setaccession("MS:1000505");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar68->setvalue(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->YofPeakWithHighestY.ToString());
                tempVar68->setunitCvRef("MS");
                tempVar68->setunitName("number of detector");
                tempVar68->setunitAccession("MS:1000131");
                tempVar68->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->cvParam[8] = tempVar68;

                // Retention time
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList = new Generated::ScanListType();
                .scanList->count = "1";
                .scanList->scan = std::vector<Generated::ScanType*>(1);
                .scanList->cvParam = std::vector<Generated::CVParamType*>(1);

                if (myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer().Equals(analyzersInThisFile[0])) {
                    Generated::ScanType *tempVar69 = new Generated::ScanType();
                    tempVar69->setcvParam(std::vector<Generated::CVParamType*>(3));
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0] = tempVar69;
                }
                else {
                    Generated::ScanType *tempVar70 = new Generated::ScanType();
                    tempVar70->setcvParam(std::vector<Generated::CVParamType*>(3));
                    tempVar70->setinstrumentConfigurationRef(analyzersInThisFileDict[myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer()]);
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0] = tempVar70;
                }
                Generated::CVParamType *tempVar71 = new Generated::CVParamType();
                tempVar71->setname("scan start time");
                tempVar71->setaccession("MS:1000016");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar71->setvalue(myMsDataFile->GetOneBasedScan(i)->getRetentionTime().ToString(CultureInfo::InvariantCulture));
                tempVar71->setunitCvRef("UO");
                tempVar71->setunitAccession("UO:0000031");
                tempVar71->setunitName("minute");
                tempVar71->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].cvParam[0] = tempVar71;
                Generated::CVParamType *tempVar72 = new Generated::CVParamType();
                tempVar72->setname("filter string");
                tempVar72->setaccession("MS:1000512");
                tempVar72->setvalue(myMsDataFile->GetOneBasedScan(i)->getScanFilter());
                tempVar72->setcvRef("MS");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].cvParam[1] = tempVar72;
                if (myMsDataFile->GetOneBasedScan(i)->getInjectionTime().HasValue) {
                    Generated::CVParamType *tempVar73 = new Generated::CVParamType();
                    tempVar73->setname("ion injection time");
                    tempVar73->setaccession("MS:1000927");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    tempVar73->setvalue(myMsDataFile->GetOneBasedScan(i)->getInjectionTime().Value.ToString(CultureInfo::InvariantCulture));
                    tempVar73->setcvRef("MS");
                    tempVar73->setunitName("millisecond");
                    tempVar73->setunitAccession("UO:0000028");
                    tempVar73->setunitCvRef("UO");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].cvParam[2] = tempVar73;
                }
                if (dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(myMsDataFile->GetOneBasedScan(i)) != nullptr) {
                    auto scanWithPrecursor = dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(myMsDataFile->GetOneBasedScan(i));
                    if (scanWithPrecursor->getSelectedIonMonoisotopicGuessMz().HasValue) {
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0]->userParam = std::vector<Generated::UserParamType*>(1);
                        Generated::UserParamType *tempVar74 = new Generated::UserParamType();
                        tempVar74->setname("[mzLib]Monoisotopic M/Z:");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        tempVar74->setvalue(scanWithPrecursor->getSelectedIonMonoisotopicGuessMz().Value.ToString(CultureInfo::InvariantCulture));
                        mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].userParam[0] = tempVar74;
                    }
                }

                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0]->scanWindowList = new Generated::ScanWindowListType();
                .scanWindowList->count = 1;
                .scanWindowList->scanWindow = std::vector<Generated::ParamGroupType*>(1);
                Generated::ParamGroupType *tempVar75 = new Generated::ParamGroupType();
                tempVar75->setcvParam(std::vector<Generated::CVParamType*>(2));
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].scanWindowList.scanWindow[0] = tempVar75;
                Generated::CVParamType *tempVar76 = new Generated::CVParamType();
                tempVar76->setname("scan window lower limit");
                tempVar76->setaccession("MS:1000501");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar76->setvalue(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->Minimum.ToString(CultureInfo::InvariantCulture));
                tempVar76->setcvRef("MS");
                tempVar76->setunitCvRef("MS");
                tempVar76->setunitAccession("MS:1000040");
                tempVar76->setunitName("m/z");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].scanWindowList.scanWindow[0].cvParam[0] = tempVar76;
                Generated::CVParamType *tempVar77 = new Generated::CVParamType();
                tempVar77->setname("scan window upper limit");
                tempVar77->setaccession("MS:1000500");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                tempVar77->setvalue(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->Maximum.ToString(CultureInfo::InvariantCulture));
                tempVar77->setcvRef("MS");
                tempVar77->setunitCvRef("MS");
                tempVar77->setunitAccession("MS:1000040");
                tempVar77->setunitName("m/z");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->scanList.scan[0].scanWindowList.scanWindow[0].cvParam[1] = tempVar77;
                if (myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty()) {
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList = new Generated::BinaryDataArrayListType();
                    .binaryDataArrayList->count = std::to_string(2);
                    .binaryDataArrayList->binaryDataArray = std::vector<Generated::BinaryDataArrayType*>(2);
                }

                if (myMsDataFile->GetOneBasedScan(i)->getNoiseData().size() > 0) {
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList = new Generated::BinaryDataArrayListType();
                    .binaryDataArrayList->count = std::to_string(5);
                    .binaryDataArrayList->binaryDataArray = std::vector<Generated::BinaryDataArrayType*>(5);
                }

                // M/Z Data
                Generated::BinaryDataArrayType *tempVar78 = new Generated::BinaryDataArrayType();
                tempVar78->setbinary(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitXarray());
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0] = tempVar78;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0]->cvParam = std::vector<Generated::CVParamType*>(3);
                Generated::CVParamType *tempVar79 = new Generated::CVParamType();
                tempVar79->setaccession("MS:1000514");
                tempVar79->setname("m/z array");
                tempVar79->setcvRef("MS");
                tempVar79->setunitName("m/z");
                tempVar79->setvalue("");
                tempVar79->setunitCvRef("MS");
                tempVar79->setunitAccession("MS:1000040");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0].cvParam[0] = tempVar79;
                Generated::CVParamType *tempVar80 = new Generated::CVParamType();
                tempVar80->setaccession("MS:1000523");
                tempVar80->setname("64-bit float");
                tempVar80->setcvRef("MS");
                tempVar80->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0].cvParam[1] = tempVar80;
                Generated::CVParamType *tempVar81 = new Generated::CVParamType();
                tempVar81->setaccession("MS:1000576");
                tempVar81->setname("no compression");
                tempVar81->setcvRef("MS");
                tempVar81->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0].cvParam[2] = tempVar81;

                // Intensity Data
                Generated::BinaryDataArrayType *tempVar82 = new Generated::BinaryDataArrayType();
                tempVar82->setbinary(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitYarray());
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1] = tempVar82;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1]->cvParam = std::vector<Generated::CVParamType*>(3);
                Generated::CVParamType *tempVar83 = new Generated::CVParamType();
                tempVar83->setaccession("MS:1000515");
                tempVar83->setname("intensity array");
                tempVar83->setcvRef("MS");
                tempVar83->setunitCvRef("MS");
                tempVar83->setunitAccession("MS:1000131");
                tempVar83->setunitName("number of counts");
                tempVar83->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1].cvParam[0] = tempVar83;
                Generated::CVParamType *tempVar84 = new Generated::CVParamType();
                tempVar84->setaccession("MS:1000523");
                tempVar84->setname("64-bit float");
                tempVar84->setcvRef("MS");
                tempVar84->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1].cvParam[1] = tempVar84;
                Generated::CVParamType *tempVar85 = new Generated::CVParamType();
                tempVar85->setaccession("MS:1000576");
                tempVar85->setname("no compression");
                tempVar85->setcvRef("MS");
                tempVar85->setvalue("");
                mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1].cvParam[2] = tempVar85;

                if (myMsDataFile->GetOneBasedScan(i)->getNoiseData().size() > 0) {
                    // mass
                    Generated::BinaryDataArrayType *tempVar86 = new Generated::BinaryDataArrayType();
                    tempVar86->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataMass());
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2] = tempVar86;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2]->arrayLength = std::to_string(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2]->cvParam = std::vector<Generated::CVParamType*>(3);
                    Generated::CVParamType *tempVar87 = new Generated::CVParamType();
                    tempVar87->setaccession("MS:1000786");
                    tempVar87->setname("non-standard data array");
                    tempVar87->setcvRef("MS");
                    tempVar87->setvalue("mass");
                    tempVar87->setunitCvRef("MS");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].cvParam[0] = tempVar87;
                    Generated::CVParamType *tempVar88 = new Generated::CVParamType();
                    tempVar88->setaccession("MS:1000523");
                    tempVar88->setname("64-bit float");
                    tempVar88->setcvRef("MS");
                    tempVar88->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].cvParam[1] = tempVar88;
                    Generated::CVParamType *tempVar89 = new Generated::CVParamType();
                    tempVar89->setaccession("MS:1000576");
                    tempVar89->setname("no compression");
                    tempVar89->setcvRef("MS");
                    tempVar89->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].cvParam[2] = tempVar89;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2]->userParam = std::vector<Generated::UserParamType*>(1);
                    Generated::UserParamType *tempVar90 = new Generated::UserParamType();
                    tempVar90->setname("kelleherCustomType");
                    tempVar90->setvalue("noise m/z");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].userParam[0] = tempVar90;

                    // noise
                    Generated::BinaryDataArrayType *tempVar91 = new Generated::BinaryDataArrayType();
                    tempVar91->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataNoise());
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3] = tempVar91;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->arrayLength = std::to_string(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->cvParam = std::vector<Generated::CVParamType*>(3);
                    Generated::CVParamType *tempVar92 = new Generated::CVParamType();
                    tempVar92->setaccession("MS:1000786");
                    tempVar92->setname("non-standard data array");
                    tempVar92->setcvRef("MS");
                    tempVar92->setvalue("SignalToNoise");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].cvParam[0] = tempVar92;
                    Generated::CVParamType *tempVar93 = new Generated::CVParamType();
                    tempVar93->setaccession("MS:1000523");
                    tempVar93->setname("64-bit float");
                    tempVar93->setcvRef("MS");
                    tempVar93->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].cvParam[1] = tempVar93;
                    Generated::CVParamType *tempVar94 = new Generated::CVParamType();
                    tempVar94->setaccession("MS:1000576");
                    tempVar94->setname("no compression");
                    tempVar94->setcvRef("MS");
                    tempVar94->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].cvParam[2] = tempVar94;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->userParam = std::vector<Generated::UserParamType*>(1);
                    Generated::UserParamType *tempVar95 = new Generated::UserParamType();
                    tempVar95->setname("kelleherCustomType");
                    tempVar95->setvalue("noise baseline");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].userParam[0] = tempVar95;

                    // baseline
                    Generated::BinaryDataArrayType *tempVar96 = new Generated::BinaryDataArrayType();
                    tempVar96->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataBaseline());
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4] = tempVar96;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4]->arrayLength = std::to_string(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4]->cvParam = std::vector<Generated::CVParamType*>(3);
                    Generated::CVParamType *tempVar97 = new Generated::CVParamType();
                    tempVar97->setaccession("MS:1000786");
                    tempVar97->setname("non-standard data array");
                    tempVar97->setcvRef("MS");
                    tempVar97->setvalue("baseline");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].cvParam[0] = tempVar97;
                    Generated::CVParamType *tempVar98 = new Generated::CVParamType();
                    tempVar98->setaccession("MS:1000523");
                    tempVar98->setname("64-bit float");
                    tempVar98->setcvRef("MS");
                    tempVar98->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].cvParam[1] = tempVar98;
                    Generated::CVParamType *tempVar99 = new Generated::CVParamType();
                    tempVar99->setaccession("MS:1000576");
                    tempVar99->setname("no compression");
                    tempVar99->setcvRef("MS");
                    tempVar99->setvalue("");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].cvParam[2] = tempVar99;
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4]->userParam = std::vector<Generated::UserParamType*>(1);
                    Generated::UserParamType *tempVar100 = new Generated::UserParamType();
                    tempVar100->setname("kelleherCustomType");
                    tempVar100->setvalue("noise intensity");
                    mzML->getrun()->getspectrumList()->getspectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].userParam[0] = tempVar100;
                }
            }

            if (!writeIndexed) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (TextWriter writer = new StreamWriter(outputFile))
            {
                    TextWriter writer = StreamWriter(outputFile);
                    mzmlSerializer->Serialize(writer, mzML);
            }
            }
            else if (writeIndexed) {
                Generated::indexedmzML *indexedMzml = new Generated::indexedmzML();

                auto inMemoryTextWriter = new System::IO::MemoryStream();

                //compute total offset
                indexedMzml->setmzML(mzML);

                indexedSerializer->Serialize(inMemoryTextWriter, indexedMzml);
                std::string allmzMLData = StringHelper::replace(Encoding::UTF8->GetString(inMemoryTextWriter->ToArray()), "\r\n", "\n");

                std::optional<long long> indexListOffset = std::make_optional(allmzMLData.length());

                //new stream with correct formatting

                Generated::IndexListType tempVar101();
                indexedMzml->setindexList(&tempVar101);
                indexedMzml->getindexList()->setcount("2");
                indexedMzml->getindexList()->setindex(std::vector<Generated::IndexType*>(2));

                //starts as spectrum be defualt
                auto indexname = new Generated::IndexTypeName();

                //spectra naming
                Generated::IndexType *tempVar102 = new Generated::IndexType();
                tempVar102->setname(indexname);
                indexedMzml->getindexList()->getindex()[0] = tempVar102;

                //switch to chromatogram name
                indexname = Generated::IndexTypeName::chromatogram;

                //chroma naming
                Generated::IndexType *tempVar103 = new Generated::IndexType();
                tempVar103->setname(indexname);
                indexedMzml->getindexList()->getindex()[1] = tempVar103;

                int numScans = myMsDataFile->getNumSpectra();
                int numChromas = std::stoi(mzML->getrun()->getchromatogramList()->getcount());

                //now calculate offsets of each scan and chroma

                //add spectra offsets
                indexedMzml->getindexList()->getindex()[0]->offset = std::vector<Generated::OffsetType*>(numScans);
                //add chroma offsets
                indexedMzml->getindexList()->getindex()[1]->offset = std::vector<Generated::OffsetType*>(numChromas);

                int i = 0;
                int a = 1;
                int index;
                //indexOf search returns location fom beginning of line (3 characters short)
                int offsetFromBeforeScanTag = 3;
                //spectra offset loop
                while (i < numScans) {
                    index = (int)allmzMLData.find(mzML->getrun()->getspectrumList()->getspectrum()[i]->id, (a - 1));
                    if (index != -1) {
                        a = index;
                        Generated::OffsetType *tempVar104 = new Generated::OffsetType();
                        tempVar104->setidRef(mzML->getrun()->getspectrumList()->getspectrum()[i]->id);
                        tempVar104->setValue(a + offsetFromBeforeScanTag);
                        indexedMzml->getindexList()->getindex()[0]->offset[i] = tempVar104;
                        i++;
                    }
                }
                int offsetFromBeforeChromaTag = 3;
                index = (int)allmzMLData.find("id=\"" + mzML->getrun()->getchromatogramList()->getchromatogram()[0]->id + "\"", (a - 1));
                if (index != -1) {
                    a = index;
                    Generated::OffsetType *tempVar105 = new Generated::OffsetType();
                    tempVar105->setidRef(mzML->getrun()->getchromatogramList()->getchromatogram()[0]->id);
                    tempVar105->setValue(a + offsetFromBeforeChromaTag);
                    indexedMzml->getindexList()->getindex()[1]->offset[0] = tempVar105;
                }
                //offset
                int offsetFromNullIndexList = 32;
                indexedMzml->setindexListOffset(indexListOffset - offsetFromNullIndexList);

                //compute checksum
                std::string chksum = "Dummy";

                indexedMzml->setfileChecksum(chksum);
                indexedSerializer->Serialize(inMemoryTextWriter, indexedMzml);

                std::string indexedMzmlwithBlankChecksumStream = Encoding::UTF8->GetString(inMemoryTextWriter->ToArray());

                std::string indexedMzmlwithBlankChecksumString = indexedMzmlwithBlankChecksumStream.substr(0, (int)indexedMzmlwithBlankChecksumStream.find("<fileChecksum>", (a - 1)));

                inMemoryTextWriter->Close();
                inMemoryTextWriter = new MemoryStream(Encoding::UTF8->GetBytes(indexedMzmlwithBlankChecksumString));
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                chksum = BitConverter::ToString(System::Security::Cryptography::SHA1::Create()->ComputeHash(inMemoryTextWriter));
                inMemoryTextWriter->Close();

                chksum = StringHelper::replace(chksum, "-", "");
                chksum = StringHelper::toLower(chksum);
                indexedMzml->setfileChecksum(chksum);

                //finally write the indexedmzml
                TextWriter writer = StreamWriter(outputFile);
                writer.NewLine = "\n";
                indexedSerializer->Serialize(writer, indexedMzml);
                writer.Close();

//C# TO C++ CONVERTER TODO TASK: A 'delete inMemoryTextWriter' statement was not added since inMemoryTextWriter was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete indexedMzml' statement was not added since indexedMzml was passed to a method or constructor. Handle memory management manually.
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete mzML' statement was not added since mzML was passed to a method or constructor. Handle memory management manually.
        }
    }
}
