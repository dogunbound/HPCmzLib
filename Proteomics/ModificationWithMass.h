﻿#pragma once

#include "ModificationWithLocation.h"
#include "TerminusLocalization.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class ModificationMotif; }


namespace Proteomics {
    class ModificationWithMass : public ModificationWithLocation {

    public:
        const double monoisotopicMass;
        const std::vector<double> diagnosticIons;
        const std::vector<double> neutralLosses;

    protected:
        static constexpr double tolForEquality = 1e-9;

    public:
        ModificationWithMass(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, double monoisotopicMass, std::unordered_map<std::string, std::vector<std::string>> &externalDatabaseReferences = nullptr, std::vector<std::string> &keywords = nullptr, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons = nullptr);

        std::string ToString() override;

        bool Equals(std::any o) override;

        int GetHashCode() override;

    private:
        bool ApproxSequenceEqual(std::vector<double> &a, std::vector<double> &b, double tolForEquality);

    };
}
