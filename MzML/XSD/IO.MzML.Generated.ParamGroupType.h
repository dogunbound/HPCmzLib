﻿#pragma once

#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { namespace Generated { class ReferenceableParamGroupRefType; } } }
namespace IO { namespace MzML { namespace Generated { class CVParamType; } } }
namespace IO { namespace MzML { namespace Generated { class UserParamType; } } }

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace IO
{
    namespace MzML
    {
        namespace Generated
        {
        /// <remarks/>
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlIncludeAttribute(typeof(ChromatogramType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(BinaryDataArrayType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(ScanType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(ScanListType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SpectrumType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(RunType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(ScanSettingsType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(ProcessingMethodType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SoftwareType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(InstrumentConfigurationType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(ComponentType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(AnalyzerComponentType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(DetectorComponentType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SourceComponentType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SampleType))][System.Xml.Serialization.XmlIncludeAttribute(typeof(SourceFileType))][System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace="http://psi.hupo.org/ms/mzml")] public partial class ParamGroupType
        class ParamGroupType
        {

        private:
            std::vector<ReferenceableParamGroupRefType*> referenceableParamGroupRefField;

            std::vector<CVParamType*> cvParamField;

            std::vector<UserParamType*> userParamField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("referenceableParamGroupRef")] public ReferenceableParamGroupRefType[] referenceableParamGroupRef
            std::vector<ReferenceableParamGroupRefType*> getreferenceableParamGroupRef() const;
            void setreferenceableParamGroupRef(const std::vector<ReferenceableParamGroupRefType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("cvParam")] public CVParamType[] cvParam
            std::vector<CVParamType*> getcvParam() const;
            void setcvParam(const std::vector<CVParamType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("userParam")] public UserParamType[] userParam
            std::vector<UserParamType*> getuserParam() const;
            void setuserParam(const std::vector<UserParamType*> &value);
        };
        }
    }
}
