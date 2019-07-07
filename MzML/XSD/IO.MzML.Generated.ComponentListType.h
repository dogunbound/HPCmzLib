﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { namespace Generated { class SourceComponentType; } } }
namespace IO { namespace MzML { namespace Generated { class AnalyzerComponentType; } } }
namespace IO { namespace MzML { namespace Generated { class DetectorComponentType; } } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.6.1055.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(Namespace="http://psi.hupo.org/ms/mzml")] public partial class ComponentListType
        class ComponentListType
        {

        private:
            std::vector<SourceComponentType*> sourceField;

            std::vector<AnalyzerComponentType*> analyzerField;

            std::vector<DetectorComponentType*> detectorField;

            std::string countField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("source")] public SourceComponentType[] source
            std::vector<SourceComponentType*> getsource() const;
            void setsource(const std::vector<SourceComponentType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("analyzer")] public AnalyzerComponentType[] analyzer
            std::vector<AnalyzerComponentType*> getanalyzer() const;
            void setanalyzer(const std::vector<AnalyzerComponentType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("detector")] public DetectorComponentType[] detector
            std::vector<DetectorComponentType*> getdetector() const;
            void setdetector(const std::vector<DetectorComponentType*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType="nonNegativeInteger")] public string count
            std::string getcount() const;
            void setcount(const std::string &value);
        };
        }
    }
}
