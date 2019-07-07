﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { namespace Generated { class SpectrumType; } } }

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
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace="http://psi.hupo.org/ms/mzml")] public partial class SpectrumListType
        class SpectrumListType
        {

        private:
            std::vector<SpectrumType*> spectrumField;

            std::string countField;

            std::string defaultDataProcessingRefField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("spectrum")] public SpectrumType[] spectrum
            std::vector<SpectrumType*> getspectrum() const;
            void setspectrum(const std::vector<SpectrumType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")] public string count
            std::string getcount() const;
            void setcount(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType="IDREF")] public string defaultDataProcessingRef
            std::string getdefaultDataProcessingRef() const;
            void setdefaultDataProcessingRef(const std::string &value);
        };
        }
    }
}
