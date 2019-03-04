﻿#include "ChemicalFormulaTestFixture.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace MzLibUtil;
//using namespace NUnit::Framework;

#include "Assert.h"

int main ( int argc, char **argv )
{

    Test::ChemicalFormulaTestFixture::AddIsotopeWithExistingMassNumber();
    Test::ChemicalFormulaTestFixture::AddElementToFormula();
    
    return 0;
}

namespace Test {

    void ChemicalFormulaTestFixture::AddIsotopeWithExistingMassNumber() {
        Element *al = PeriodicTable::GetElement("Al");
#ifdef LATER
        Assert::Throws<MzLibException*>([&] () {
            al->AddIsotope(27, 28, 1);
        }, "Isotope with mass number " + std::to_string(28) + " already exists");
#endif
    }

    void ChemicalFormulaTestFixture::AddElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3N2O");

        Element *n = PeriodicTable::GetElement(7);

        formulaA->Add(n, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::Multiply() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        formulaA->Multiply(2);
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C4H6N2O2");

        Assert::AreEqual(formulaA, formulaB);

        Assert::IsFalse(formulaA->Equals(nullptr));
    }

    void ChemicalFormulaTestFixture::CheckToStringOfElements() {
        Element *n = PeriodicTable::GetElement("N");
        std::string a = n->ToString();
        std::string b = "N";
        Assert::AreEqual(a, b);
    }

    void ChemicalFormulaTestFixture::AddFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5NO2");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::AddFormulaToItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C4H6N2O2");

        ChemicalFormula tempVar(formulaA);
        formulaA->Add(&tempVar);

        Assert::AreEqual(formulaA, formulaB);
    }

#ifdef LATER
    
    void ChemicalFormulaTestFixture::AddIChemicalFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        IHasChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula("H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5NO2");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    
    void ChemicalFormulaTestFixture::AddIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3H{1}NO");
        Isotope *h1 = PeriodicTable::GetElement("H")[1];

        formulaA->Add(h1, 1);

        Assert::AreEqual(formulaA, formulaB);

    }

    void ChemicalFormulaTestFixture::AddLargeElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NOFe");

        Element *fe = PeriodicTable::GetElement("Fe");

        formulaA->Add(fe, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddNegativeFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C-1H-2");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("CHNO");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::AddNegativeIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2HH{1}2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        Isotope *h1 = PeriodicTable::GetElement("H")[1];

        formulaA->Add(h1, -2);

        Assert::AreEqual(formulaA, formulaB);

    }

    void ChemicalFormulaTestFixture::AddELementByAtomicNumber() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        formulaB->Add(1, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddNonExistentSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::Throws<KeyNotFoundException*>([&] () {
            formulaA->AddPrincipalIsotopesOf("Faa", 1);
        });
    }

    void ChemicalFormulaTestFixture::InexistingElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            ChemicalFormula::ParseFormula("Q");
        });
    }

    void ChemicalFormulaTestFixture::AddZeroElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Element *n = PeriodicTable::GetElement("N");

        formulaA->Add(n, 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddZeroIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Isotope *h1 = PeriodicTable::GetElement("H")[1];

        formulaA->Add(h1, 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddZeroSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->AddPrincipalIsotopesOf("H", 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ClearFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        formulaA->Clear();
        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);
    }

    void ChemicalFormulaTestFixture::ConstructorBlankStringEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::ConstructorDefaultEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::CopyConstructorValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::CopyConstructorReferenceInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::AreNotSame(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::EmptyMonoisotopicMassIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0.0, (&tempVar)->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::EmptyAverageMassIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0.0, (&tempVar)->getAverageMass());
    }

    void ChemicalFormulaTestFixture::EmptyStringIsBlank() {
        ChemicalFormula tempVar();
        Assert::IsEmpty((&tempVar)->getFormula());
    }

    void ChemicalFormulaTestFixture::EmptyAtomCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::EmptyElementCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::EmptyIsotopeCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::FormulaValueInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("NC1OH3");

        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaValueInequalityHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaValueEqualityItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::FormulaValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("NC2OH3");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::FormulaAlmostEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C{12}2H3NO");
        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::HashCodeEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3C2NO");

        Assert::AreEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeImmutableEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        Assert::AreEqual(formulaA->GetHashCode(), formulaA->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeCheck() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("Al");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("Al{27}");
        Assert::AreNotEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HillNotation() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2O");

        Assert::AreEqual("C2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbon() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("BrH");

        Assert::AreEqual("HBr", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbonNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("Ca5O14Br6");

        Assert::AreEqual("Br6Ca5O14", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("NC2O");

        Assert::AreEqual("C2NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2C{13}2O");

        Assert::AreEqual("C2C{13}2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC-2O");

        Assert::AreEqual("C-2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotopeNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2C{13}-2O");

        Assert::AreEqual("C2C{13}-2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::BadFormula() {
        Assert::Throws<MzLibException*>([&] () {
            ChemicalFormula::ParseFormula("!@#$");
        }, "Input string for chemical formula was in an incorrect format");
    }

    void ChemicalFormulaTestFixture::InvalidChemicalElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            PeriodicTable::GetElement("Faa");
        });
    }

    void ChemicalFormulaTestFixture::InvalidElementIsotope() {
        Assert::IsNull(PeriodicTable::GetElement("C")[100]);
    }

    void ChemicalFormulaTestFixture::NumberOfAtoms() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfNegativeFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C-2H-3N-1O-1");

        Assert::AreEqual(-7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbers() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CCHHHNO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithInternalSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2 H3 N O");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtEnd() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtBeginning() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("    C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("  C2 H3 N O  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbersRandomOrder() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::EqualsFalse() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        Assert::IsFalse(formulaA->Equals("C"));
    }

    void ChemicalFormulaTestFixture::Equals() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CH3NOC");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::IsSuperSetOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CH3NO{17}C");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CHNO{16}");

        Assert::IsFalse(formulaA->IsSupersetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElementsCancelEachOther() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NOC-2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("H"));

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaBySymbol() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf("H");

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2C{13}H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3NO");

        formulaA->RemoveIsotopesOf("C");

        Assert::AreEqual(formulaA, formulaB);
        Assert::AreEqual(formulaA->getMonoisotopicMass(), formulaB->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::RemoveEmptyFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        ChemicalFormula tempVar();
        formulaA->Remove(&tempVar);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NOO{16}");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H2O{16}");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->Remove(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::ContainsSpecificIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NOO{16}");

        Assert::IsTrue(formulaA->ContainsSpecificIsotope(PeriodicTable::GetElement("O")[16]));
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("O{16}");
        Assert::IsTrue(formulaA->ContainsIsotopesOf("O"));
        Assert::IsTrue(formulaA->ContainsSpecificIsotope("O", 16));
        Assert::AreEqual(1, formulaA->CountSpecificIsotopes("O", 16));
    }

    void ChemicalFormulaTestFixture::HydrogenCarbonRatio() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C8H4");
        Assert::AreEqual(0.5, formulaA->getHydrogenCarbonRatio());
    }

    void ChemicalFormulaTestFixture::RemoveIsotopeCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("H"));

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        formulaA->Remove(PeriodicTable::GetElement("H"), 2);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveIsotopeFromFromulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3O");

        formulaA->Remove("N", 1);

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveNegativeElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H5NO");

        formulaA->Remove(PeriodicTable::GetElement("H"), -2);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveNonExistantIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("Fe");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5Fe-1NO2");

        formulaA->Remove(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::RemoveZeroIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->Remove(PeriodicTable::GetElement("H")[1], 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::TotalProtons() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{13}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::TotalProtons2() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::AverageMass() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C");

        Assert::AreEqual(PeriodicTable::GetElement("C")->getAverageMass(), formulaA->getAverageMass());
    }

    void ChemicalFormulaTestFixture::UniqueElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(0, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::AreEqual(1, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOfYe() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::IsTrue(formulaA->ContainsIsotopesOf(PeriodicTable::GetElement("C")));
    }

    void ChemicalFormulaTestFixture::TestReplaceIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}2H3NO");

        formulaA->Replace(PeriodicTable::GetElement("C")[13], PeriodicTable::GetElement("C")[12]);
        Assert::AreEqual("CC{12}2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsTrue(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H2NO");

        Assert::IsFalse(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsTrue(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsFalse(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaMyTest() {
        ChemicalFormula *formula = new ChemicalFormula();
        formula->Add(ChemicalFormula::ParseFormula("C3H5NO"));
        Assert::AreEqual(PeriodicTable::GetElement("C")->getPrincipalIsotope()->getAtomicMass() * 3 + PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() * 5 + PeriodicTable::GetElement("N")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass(), formula->getMonoisotopicMass());

        delete formula;
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        auto a = IsotopicDistribution::GetDistribution(formulaA);

        Assert::True(std::abs(formulaA->getMonoisotopicMass() - a->getMasses().ToArray()[Array::IndexOf(a->getIntensities().ToArray(), a->getIntensities().Max())]) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution2() {
        IsotopicDistribution::GetDistribution(ChemicalFormula::ParseFormula("AlO{16}"));
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution3() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");

        // Distinguish between O and C isotope masses
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001);
        Assert::AreEqual(6, a->getMasses().size()());

        // Do not distinguish between O and C isotope masses
        IsotopicDistribution::GetDistribution(formulaA, 0.001);

        // Do not distinguish between O and C isotope masses
        auto b = IsotopicDistribution::GetDistribution(formulaA);
        Assert::AreEqual(4, b->getMasses().size()());

        IsotopicDistribution::GetDistribution(formulaA, 0.1);

        PhysicalObjectWithChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula("CO");
        IsotopicDistribution::GetDistribution(formulaB->getThisChemicalFormula(), 1);

        delete formulaB;
    }

    void ChemicalFormulaTestFixture::CatchIsotopicDistributionStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C500O50H250N50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-1, 1e-15);
    }

    void ChemicalFormulaTestFixture::CatchProbStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-50, 1e-15);
    }

    void ChemicalFormulaTestFixture::I0j1() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.01, 0.1);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.5);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.75);
    }

    void ChemicalFormulaTestFixture::ThresholdProbability() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");

        // Only the principal isotopes have joint probability of 0.5! So one result when calcuating isotopic distribution
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001, 0.5);
        Assert::AreEqual(1, a->getMasses().size()());
        Assert::IsTrue(std::abs((PeriodicTable::GetElement("C")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass() - a->getMasses().front())) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestAnotherFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H{1}CC{13}2H3NO{16}");
        Assert::AreEqual("CC{13}2H3H{1}NO{16}", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::NeutronCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}O{16}");
        Assert::AreEqual(14, formulaA->NeutronCount());
    }

    void ChemicalFormulaTestFixture::NeutronCountFail() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");
        Assert::Throws<MzLibException*>([&] () {
            formulaA->NeutronCount();
        }, "Cannot know for sure what the number of neutrons is!");
    }

    void ChemicalFormulaTestFixture::CombineTest() {
        std::vector<IHasChemicalFormula*> theList = {
            new PhysicalObjectWithChemicalFormula("C2H3NO"),
            new PhysicalObjectWithChemicalFormula("CO")
        };
        auto c = ChemicalFormula::Combine(theList);

        Assert::AreEqual("C3H3NO2", c->getFormula());
    }

    void ChemicalFormulaTestFixture::ValidatePeriodicTable() {
        Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
        Assert::IsFalse(PeriodicTable::ValidateAverageMasses(1e-3));
        Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
        Assert::IsFalse(PeriodicTable::ValidateAbundances(0));
    }

    void ChemicalFormulaTestFixture::TestAddChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}");
        formulaB->Add(formulaA);
        Assert::AreEqual("CC{12}", formulaB->getFormula());
    }

    void ChemicalFormulaTestFixture::NotEqual() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C15O15H15S15N15");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("N15S15H15O15C15");
        Assert::AreEqual(formulaA, formulaB);
        Assert::IsTrue(std::abs(formulaA->getMonoisotopicMass() - formulaB->getMonoisotopicMass()) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestRemoveObjectFromChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        auto ok = new PhysicalObjectWithChemicalFormula("C");
        formulaB->Remove(ok);

        Assert::AreEqual("O", formulaB->getFormula());

//C# TO C++ CONVERTER TODO TASK: A 'delete ok' statement was not added since ok was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::TestEquality() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        Assert::AreEqual(formulaB, formulaB);
    }

    void ChemicalFormulaTestFixture::TestToChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        Assert::AreEqual(ChemicalFormula::ParseFormula("CO"), formulaB);
    }

    void ChemicalFormulaTestFixture::IsoTest() {
        ChemicalFormula *formula = ChemicalFormula::ParseFormula("C5H8NO");

        IsotopicDistribution *d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -14));

        Assert::AreEqual(324, d->getIntensities().size()());

        d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -1));

        Assert::AreEqual(17, d->getIntensities().size()());
    }

    ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::PhysicalObjectWithChemicalFormula(const std::string &v) {
        setThisChemicalFormula(ChemicalFormula::ParseFormula(v));
    }

    double ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::getMonoisotopicMass() const {
        return getThisChemicalFormula()->getMonoisotopicMass();
    }

    ChemicalFormula *ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }
#endif

}
