﻿#include "IO.MzML.Generated.SoftwareListType.h"
#include "IO.MzML.Generated.SoftwareType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<SoftwareType*> SoftwareListType::getsoftware() const
            {
                return this->softwareField;
            }

            void SoftwareListType::setsoftware(const std::vector<SoftwareType*> &value)
            {
                this->softwareField = value;
            }

            std::string SoftwareListType::getcount() const
            {
                return this->countField;
            }

            void SoftwareListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
