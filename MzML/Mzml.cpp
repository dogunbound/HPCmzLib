﻿#include "Mzml.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "../MassSpectrometry/FilteringParams.h"
#include "XSD/IO.MzML.Generated.mzMLType.h"
#include "MzmlMethods.h"
#include "XSD/IO.MzML.Generated.indexedmzML.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MassSpectrometry/IFilteringParams.h"
#include "XSD/IO.MzML.Generated.InstrumentConfigurationType.h"
#include "XSD/IO.MzML.Generated.CVParamType.h"
#include "XSD/IO.MzML.Generated.BinaryDataArrayType.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO
{
    namespace MzML
    {

const std::string Mzml::_zlibCompression = "MS:1000574";
const std::string Mzml::_64bit = "MS:1000523";
const std::string Mzml::_32bit = "MS:1000521";
const std::string Mzml::_filterString = "MS:1000512";
const std::string Mzml::_centroidSpectrum = "MS:1000127";
const std::string Mzml::_profileSpectrum = "MS:1000128";
const std::string Mzml::_peakIntensity = "MS:1000042";
const std::string Mzml::_totalIonCurrent = "MS:1000285";
const std::string Mzml::_scanWindowLowerLimit = "MS:1000501";
const std::string Mzml::_scanWindowUpperLimit = "MS:1000500";
const std::string Mzml::_msnOrderAccession = "MS:1000511";
const std::string Mzml::_precursorCharge = "MS:1000041";
const std::string Mzml::_selectedIonMz = "MS:1000744";
const std::string Mzml::_isolationWindowTargetMZ = "MS:1000827";
const std::string Mzml::_isolationWindowLowerOffset = "MS:1000828";
const std::string Mzml::_isolationWindowUpperOffset = "MS:1000829";
const std::string Mzml::_oneBasedScanNumber = "MS:1000797";
const std::string Mzml::_retentionTime = "MS:1000016";
const std::string Mzml::_ionInjectionTime = "MS:1000927";
const std::string Mzml::_mzArray = "MS:1000514";
const std::string Mzml::_intensityArray = "MS:1000515";
Regex *const Mzml::MZAnalyzerTypeRegex = new Regex(R"(^[a-zA-Z]*)", RegexOptions::Compiled);
std::unordered_map<std::string, Polarity> Mzml::polarityDictionary =
{
    {"MS:1000129",Polarity::Negative},
    {"MS:1000130",Polarity::Positive}
};
std::unordered_map<std::string, MZAnalyzerType> Mzml::analyzerDictionary =
{
    {"MS:1000443", MZAnalyzerType::Unknown},
    {"MS:1000081",MZAnalyzerType::Quadrupole},
    {"MS:1000291",MZAnalyzerType::IonTrap2D},
    {"MS:1000082",MZAnalyzerType::IonTrap3D},
    {"MS:1000484",MZAnalyzerType::Orbitrap},
    {"MS:1000084",MZAnalyzerType::TOF},
    {"MS:1000079",MZAnalyzerType::FTICR},
    {"MS:1000080",MZAnalyzerType::Sector}
};
std::unordered_map<std::string, DissociationType> Mzml::dissociationDictionary =
{
    {"MS:1000133",DissociationType::CID},
    {"MS:1001880",DissociationType::ISCID},
    {"MS:1000422",DissociationType::HCD},
    {"MS:1000598",DissociationType::ETD},
    {"MS:1000435",DissociationType::IRMPD},
    {"MS:1000599",DissociationType::PQD},
    {"MS:1000044",DissociationType::Unknown}
};

        Mzml::Mzml(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(scans, sourceFile)
        {
        }

        Mzml *Mzml::LoadAllStaticData(const std::string &filePath, FilteringParams *filterParams, int maxThreads)
        {
            if (!FileSystem::fileExists(filePath))
            {
                throw FileNotFoundException();
            }

            Generated::mzMLType *_mzMLConnection;

            try
            {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read))
                {
                    FileStream fs = FileStream(filePath, FileMode::Open, FileAccess::Read, FileShare::Read);
                    auto _indexedmzMLConnection = static_cast<Generated::indexedmzML*>(MzmlMethods::indexedSerializer->Deserialize(fs));
                    _mzMLConnection = _indexedmzMLConnection->getmzML();
                }
            }
            catch (...)
            {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read))
                {
                    FileStream fs = FileStream(filePath, FileMode::Open, FileAccess::Read, FileShare::Read);
                    _mzMLConnection = static_cast<Generated::mzMLType*>(MzmlMethods::mzmlSerializer->Deserialize(fs));
                }
            }

            MassSpectrometry::SourceFile *sourceFile;
            if (_mzMLConnection->getfileDescription()->getsourceFileList() != nullptr && !_mzMLConnection->getfileDescription()->getsourceFileList()->getsourceFile().empty() && _mzMLConnection->getfileDescription()->getsourceFileList()->getsourceFile()[0] != nullptr && _mzMLConnection->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam != nullptr)
            {
                auto simpler = _mzMLConnection->getfileDescription()->getsourceFileList()->getsourceFile()[0];
                std::string nativeIdFormat = "";
                std::string fileFormat = "";
                std::string checkSum = "";
                std::string checkSumType = "";
                for (auto cv : simpler->cvParam)
                {
                    if (cv->accession->Equals(R"(MS:1000563)"))
                    {
                        fileFormat = "Thermo RAW format";
                    }
                    if (cv->accession->Equals(R"(MS:1000584)"))
                    {
                        fileFormat = "mzML format";
                    }

                    if (cv->accession->Equals(R"(MS:1000768)"))
                    {
                        nativeIdFormat = "Thermo nativeID format";
                    }
                    if (cv->accession->Equals(R"(MS:1000776)"))
                    {
                        nativeIdFormat = "scan number only nativeID format";
                    }
                    if (cv->accession->Equals(R"(MS:1000824)"))
                    {
                        nativeIdFormat = "no nativeID format";
                    }

                    if (cv->accession->Equals(R"(MS:1000568)"))
                    {
                        checkSum = cv->value;
                        checkSumType = "MD5";
                    }
                    if (cv->accession->Equals(R"(MS:1000569)"))
                    {
                        checkSum = cv->value;
                        checkSumType = "SHA-1";
                    }
                }

                Uri tempVar(simpler->location);
                sourceFile = new SourceFile(nativeIdFormat, fileFormat, checkSum, checkSumType, &tempVar, simpler->id, simpler->name);
            }
            else
            {
                std::string sendCheckSum;
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream stream = File.OpenRead(filePath))
                {
                    FileStream stream = File::OpenRead(filePath);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (SHA1Managed sha = new SHA1Managed())
                    {
                        SHA1Managed sha = SHA1Managed();
                        std::vector<unsigned char> checksum = sha.ComputeHash(stream);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                        sendCheckSum = BitConverter::ToString(checksum)->Replace("-", "");
                    }
                }
                sourceFile = new SourceFile(R"(no nativeID format)", R"(mzML format)", sendCheckSum, R"(SHA-1)", FileSystem::getFullPath(filePath), Path::GetFileNameWithoutExtension(filePath));
            }

            auto numSpecta = _mzMLConnection->getrun()->getspectrumList()->getspectrum().size();
            std::vector<MsDataScan*> scans(numSpecta);

            ParallelOptions *tempVar2 = new ParallelOptions();
            tempVar2->MaxDegreeOfParallelism = maxThreads;
            Parallel::ForEach(Partitioner::Create(0, numSpecta), tempVar2, [&] (std::any fff)
            {
                for (int i = fff::Item1; i < fff::Item2; i++)
                {
                    scans[i] = GetMsDataOneBasedScanFromConnection(_mzMLConnection, i + 1, filterParams);
                }
            });

            //Mzml sometimes have scan numbers specified, but usually not.
            //In the event that they do, the iterator above unintentionally assigned them to an incorrect index.
            //Check to make sure that the scans are in order and that there are no duplicate scans
            std::unordered_set<int> checkForDuplicateScans;
            bool ordered = true;
            int previousScanNumber = -1;
            for (auto scan : scans)
            {
                //check if no duplicates
                if (!checkForDuplicateScans.insert(scan->getOneBasedScanNumber())) //returns false if the scan already exists
                {
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar2' statement was not added since tempVar2 was passed to a method or constructor. Handle memory management manually.
                    delete sourceFile;
                    throw MzLibException("Scan number " + std::to_string(scan->getOneBasedScanNumber()) + " appeared multiple times in " + filePath);
                }
                //check if scans are in order
                if (previousScanNumber > scan->getOneBasedScanNumber())
                {
                    ordered = false;
                }
                previousScanNumber = scan->getOneBasedScanNumber();
            }

            if (!ordered) //reassign indexes if not ordered
            {
                std::vector<MsDataScan*> indexedScans(checkForDuplicateScans.Max());
                for (auto scan : scans)
                {
                    indexedScans[scan->getOneBasedScanNumber() - 1] = scan;
                }
                scans = indexedScans;
            }

            //make reference pervious ms1 scan
            // we weren't able to get the precursor scan number, so we'll have to guess;
            // loop back to find precursor scan
            // (assumed to be the first scan before this scan with an MS order of this scan's MS order - 1)
            // e.g., if this is an MS2 scan, find the first MS1 scan before this and assume that's the precursor scan
            for (int i = 0; i < scans.size(); i++)
            {
                if (scans[i]->getMsnOrder() > 1 && !scans[i]->getOneBasedPrecursorScanNumber())
                {
                    for (int j = i; j >= 0; j--)
                    {
                        if (scans[i]->getMsnOrder() - scans[j]->getMsnOrder() == 1)
                        {
                            scans[i]->setOneBasedPrecursorScanNumber(scans[j]->getOneBasedScanNumber());
                            break;
                        }
                    }
                }
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar2' statement was not added since tempVar2 was passed to a method or constructor. Handle memory management manually.
            delete sourceFile;
            return new Mzml(scans, sourceFile);
        }

        MsDataScan *Mzml::GetMsDataOneBasedScanFromConnection(Generated::mzMLType *_mzMLConnection, int oneBasedIndex, IFilteringParams *filterParams)
        {
            // Read in the instrument configuration types from connection (in mzml it's at the start)

            std::vector<Generated::InstrumentConfigurationType*> configs(_mzMLConnection->getinstrumentConfigurationList()->getinstrumentConfiguration().size());
            for (int i = 0; i < _mzMLConnection->getinstrumentConfigurationList()->getinstrumentConfiguration().size(); i++)
            {
                configs[i] = _mzMLConnection->getinstrumentConfigurationList()->getinstrumentConfiguration()[i];
            }

            auto defaultInstrumentConfig = _mzMLConnection->getrun()->getdefaultInstrumentConfigurationRef();
            // May be null!
            auto scanSpecificInsturmentConfig = _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].instrumentConfigurationRef;

            MZAnalyzerType analyzer = static_cast<MassSpectrometry::MZAnalyzerType>(0);
            // use default
            if (scanSpecificInsturmentConfig == nullptr || scanSpecificInsturmentConfig == defaultInstrumentConfig)
            {
                if (configs[0]->getcomponentList() == nullptr)
                {
                    analyzer = static_cast<MassSpectrometry::MZAnalyzerType>(0);
                }
                else
                {
                    MZAnalyzerType returnVal;
                    std::unordered_map<std::string, MZAnalyzerType>::const_iterator analyzerDictionary_iterator = analyzerDictionary.find(configs[0].componentList.analyzer[0].cvParam[0].accession);
                    if (analyzerDictionary_iterator != analyzerDictionary.end())
                    {
                    returnVal = analyzerDictionary_iterator->second;
                        analyzer = returnVal;
                    }
                else
                {
                    returnVal = analyzerDictionary_iterator->second;
                }
                }
            }
            // use scan-specific
            else
            {
                for (int i = 0; i < _mzMLConnection->getinstrumentConfigurationList()->getinstrumentConfiguration().size(); i++)
                {
                    if (configs[i]->getid() == scanSpecificInsturmentConfig)
                    {
                        MZAnalyzerType returnVal;
                        std::unordered_map<std::string, MZAnalyzerType>::const_iterator analyzerDictionary_iterator = analyzerDictionary.find(configs[i]->getcomponentList().getanalyzer()[0].cvParam[0].accession);
                        returnVal = analyzerDictionary_iterator->second;
                        analyzer = returnVal;
                    }
                }
            }

            std::string nativeId = _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->id;

            std::optional<int> msOrder;
            std::optional<bool> isCentroid;
            Polarity polarity = Polarity::Unknown;
            double tic = NAN;

            for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->cvParam)
            {
                if (cv->getaccession() == _msnOrderAccession)
                {
                    msOrder = std::make_optional(std::stoi(cv->getvalue()));
                }
                if (cv->getaccession() == _centroidSpectrum)
                {
                    isCentroid = std::make_optional(true);
                }
                if (cv->getaccession() == _profileSpectrum)
                {
                    throw MzLibException("Reading profile mode mzmls not supported");
                }
                if (cv->getaccession() == _totalIonCurrent)
                {
                    tic = std::stod(cv->getvalue());
                }
                if (polarity.Equals(Polarity::Unknown))
                {
                    std::unordered_map<std::string, Polarity>::const_iterator polarityDictionary_iterator = polarityDictionary.find(cv->getaccession());
                    polarity = polarityDictionary_iterator->second;
                }
            }

            if (!msOrder || !isCentroid)
            {
                throw MzLibException("!msOrder.HasValue || !isCentroid.HasValue");
            }

            std::vector<double> masses(0);
            std::vector<double> intensities(0);

            for (Generated::BinaryDataArrayType *binaryData : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->binaryDataArrayList.binaryDataArray)
            {
                bool compressed = false;
                bool mzArray = false;
                bool intensityArray = false;
                bool is32bit = true;
                for (auto cv : binaryData->getcvParam())
                {
                    compressed |= cv->getaccession() == _zlibCompression;
                    is32bit &= cv->getaccession() != _64bit;
                    is32bit |= cv->getaccession() == _32bit;
                    mzArray |= cv->getaccession() == _mzArray;
                    intensityArray |= cv->getaccession() == _intensityArray;
                }

                std::vector<double> data = ConvertBase64ToDoubles(binaryData->getbinary(), compressed, is32bit);
                if (mzArray)
                {
                    masses = data;
                }

                if (intensityArray)
                {
                    intensities = data;
                }
            }

            double high = NAN;
            double low = NAN;

            auto aScanWindowList = _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].scanWindowList;

            if (aScanWindowList != nullptr)
            {
                for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].scanWindowList.scanWindow[0].cvParam)
                {
                    if (cv->getaccession() == _scanWindowLowerLimit)
                    {
                        low = std::stod(cv->getvalue());
                    }
                    else if (cv->getaccession() == _scanWindowUpperLimit)
                    {
                        high = std::stod(cv->getvalue());
                    }
                }
            }

            if (filterParams != nullptr && intensities.size() > 0 && (filterParams->getMinimumAllowedIntensityRatioToBasePeakM() || filterParams->getNumberOfPeaksToKeepPerWindow()) && ((filterParams->getApplyTrimmingToMs1() && msOrder.value() == 1) || (filterParams->getApplyTrimmingToMsMs() && msOrder.value() > 1)))
            {
                if (!filterParams->getNumberOfWindows())
                {
                    int numPeaks = TopNpeakHelper(intensities, masses, filterParams);
                    Array::Resize(intensities, numPeaks);
                    Array::Resize(masses, numPeaks);
                }
                else
                {
                    WindowModeHelper(intensities, masses, filterParams, low, high);
                }
            }
            Array::Sort(masses, intensities);
            auto mzmlMzSpectrum = new MzSpectrum(masses, intensities, false);

            double rtInMinutes = NAN;
            std::string scanFilter = "";
            std::optional<double> injectionTime;
            int oneBasedScanNumber = oneBasedIndex;
            if (_mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].cvParam != nullptr)
            {
                for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].cvParam)
                {
                    if (cv->getaccession() == _retentionTime)
                    {
                        rtInMinutes = std::stod(cv->getvalue());
                        if (cv->getunitName() == "second")
                        {
                            rtInMinutes /= 60;
                        }
                    }
                    if (cv->getaccession() == _filterString)
                    {
                        scanFilter = cv->getvalue();
                    }
                    if (cv->getaccession() == _ionInjectionTime)
                    {
                        injectionTime = std::make_optional(std::stod(cv->getvalue()));
                    }
                    if (cv->getaccession() == _oneBasedScanNumber) //get the real one based spectrum number (if available), the other assumes they are in order. This is present in .mgf->.mzml conversions from MSConvert
                    {
                        oneBasedScanNumber = std::stoi(cv->getvalue());
                    }
                }
            }

            if (msOrder.value() == 1)
            {
                delete mzmlMzSpectrum;
                MzRange tempVar(low, high);
                return new MsDataScan(mzmlMzSpectrum, oneBasedScanNumber, msOrder.value(), isCentroid.value(), polarity, rtInMinutes, &tempVar, scanFilter, analyzer, tic, injectionTime, std::vector<std::vector<double>>(), nativeId);
            }

            double selectedIonMz = NAN;
            std::optional<int> selectedIonCharge;
            std::optional<double> selectedIonIntensity;
            for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0].selectedIonList.selectedIon[0].cvParam)
            {
                if (cv->getaccession() == _selectedIonMz)
                {
                    selectedIonMz = std::stod(cv->getvalue());
                }
                if (cv->getaccession() == _precursorCharge)
                {
                    selectedIonCharge = std::make_optional(std::stoi(cv->getvalue()));
                }
                if (cv->getaccession() == _peakIntensity)
                {
                    selectedIonIntensity = std::make_optional(std::stod(cv->getvalue()));
                }
            }

            std::optional<double> isolationMz;
            double lowIsolation = NAN;
            double highIsolation = NAN;
            if (_mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0].isolationWindow != nullptr)
            {
                for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0].isolationWindow.cvParam)
                {
                    if (cv->getaccession() == _isolationWindowTargetMZ)
                    {
                        isolationMz = std::make_optional(std::stod(cv->getvalue()));
                    }
                    if (cv->getaccession() == _isolationWindowLowerOffset)
                    {
                        lowIsolation = std::stod(cv->getvalue());
                    }
                    if (cv->getaccession() == _isolationWindowUpperOffset)
                    {
                        highIsolation = std::stod(cv->getvalue());
                    }
                }
            }

            DissociationType dissociationType = DissociationType::Unknown;
            if (_mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0].activation.cvParam != nullptr)
            {
                for (Generated::CVParamType *cv : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0].activation.cvParam)
                {
                    std::unordered_map<std::string, DissociationType>::const_iterator dissociationDictionary_iterator = dissociationDictionary.find(cv->getaccession());
                    dissociationType = dissociationDictionary_iterator->second;
                }
            }
            std::optional<double> monoisotopicMz;
            if (_mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].userParam != nullptr)
            {
                for (auto userParam : _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->scanList.scan[0].userParam)
                {
                    if (userParam->name->EndsWith("Monoisotopic M/Z:"))
                    {
                        monoisotopicMz = std::make_optional(std::stod(userParam->value));
                    }
                }
            }

            std::optional<int> precursorScanNumber;
            if (_mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedIndex - 1]->precursorList.precursor[0]->spectrumRef == nullptr)
            {
                precursorScanNumber = std::nullopt;
            }
            else
            {
                precursorScanNumber = std::make_optional(GetOneBasedPrecursorScanNumber(_mzMLConnection, oneBasedIndex));
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete mzmlMzSpectrum' statement was not added since mzmlMzSpectrum was passed to a method or constructor. Handle memory management manually.
            MzRange tempVar2(low, high);
            return new MsDataScan(mzmlMzSpectrum, oneBasedIndex, msOrder.value(), isCentroid.value(), polarity, rtInMinutes, &tempVar2, scanFilter, analyzer, tic, injectionTime, std::vector<std::vector<double>>(), nativeId, std::make_optional(selectedIonMz), selectedIonCharge, selectedIonIntensity, isolationMz, std::make_optional(lowIsolation + highIsolation), std::make_optional(dissociationType), precursorScanNumber, monoisotopicMz);
        }

        std::vector<double> Mzml::ConvertBase64ToDoubles(std::vector<unsigned char> &bytes, bool zlibCompressed, bool is32bit)
        {
            // Add capability of compressed data

            if (zlibCompressed)
            {
                auto output = new MemoryStream();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var compressStream = new MemoryStream(bytes))
                {
                    auto compressStream = MemoryStream(bytes);
                    compressStream.ReadByte();
                    compressStream.ReadByte();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var decompressor = new DeflateStream(compressStream, CompressionMode.Decompress))
                    {
                        auto decompressor = DeflateStream(compressStream, CompressionMode::Decompress);
                        decompressor.CopyTo(output);
                        decompressor.Close();
                        output->Position = 0;
                        bytes = output->ToArray();
                    }
                }

//C# TO C++ CONVERTER TODO TASK: A 'delete output' statement was not added since output was passed to a method or constructor. Handle memory management manually.
            }

            int size = is32bit ? sizeof(float) : sizeof(double);

            int length = bytes.size() / size;
            std::vector<double> convertedArray(length);

            for (int i = 0; i < length; i++)
            {
                if (is32bit)
                {
                    convertedArray[i] = BitConverter::ToSingle(bytes, i * size);
                }
                else
                {
                    convertedArray[i] = BitConverter::ToDouble(bytes, i * size);
                }
            }
            return convertedArray;
        }

        int Mzml::GetOneBasedPrecursorScanNumber(Generated::mzMLType *_mzMLConnection, int oneBasedSpectrumNumber)
        {
            std::string precursorID = _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedSpectrumNumber - 1]->precursorList.precursor[0].spectrumRef;
            do
            {
                oneBasedSpectrumNumber--;
            } while (precursorID != _mzMLConnection->getrun()->getspectrumList()->getspectrum()[oneBasedSpectrumNumber - 1]->id);
            return oneBasedSpectrumNumber;
        }
    }
}
