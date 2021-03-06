/*
This file is part of the Multivariate Splines library.
Copyright (C) 2012 Bjarne Grimstad (bjarne.grimstad@gmail.com)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef BASIS1D_H
#define BASIS1D_H

#include "generaldefinitions.h"

namespace MultivariateSplines
{

enum class KnotSequenceType
{
    EXPLICIT, // Knot sequence is given (should be regular)
    REGULAR,   // p+1-regular knots (knots are added if necessary)
    FREE    // Knots for cubic spline interpolation with free end conditions
};

class Basis1D
{
public:
    Basis1D(std::vector<double> &x, int degree);
    Basis1D(std::vector<double> &x, int degree, KnotSequenceType knotSequenceType);

    // Evaluation of basis functions
    SparseVector evaluate(const double x) const;
    SparseVector evaluateDerivative(double x, int r) const;
    DenseVector evaluateFirstDerivative(double x) const; // Depricated

    // Knot sequence related
    bool refineKnots(SparseMatrix &A);
    bool insertKnots(SparseMatrix &A, double tau, unsigned int multiplicity = 1);
    // bool insertKnots(SparseMatrix &A, std::vector<tuple<double,int>> newKnots); // Add knots at several locations
    int knotMultiplicity(const double &tau) const; // Returns the number of repetitions of tau in the knot sequence

    // Support related
    bool insideSupport(const double &x) const;
    bool reduceSupport(double lb, double ub, SparseMatrix &A);

    // Getters
    std::vector<double> getKnotVector() const { return knots; }
    int getBasisDegree() const { return degree; }
    double getKnotValue(int index) const;
    int numBasisFunctions() const;
    int numBasisFunctionsTarget() const;

    // Index getters
    std::vector<int> indexSupportedBasisfunctions(double x) const;
    int indexHalfopenInterval(double x) const;
    int indexLongestInterval() const;
    int indexLongestInterval(const std::vector<double> &vec) const;

private:

    // DeBoorCox algorithm for evaluating basis functions
    double deBoorCox(double x, int i, int k) const;
    double deBoorCoxCoeff(double x, double x_min, double x_max) const;

    // Builds basis matrix for alternative evaluation of basis functions
    SparseMatrix buildBasisMatrix(double x, int u, int k, bool diff = false) const;

    // Builds knot insertion matrix
    bool buildKnotInsertionMatrix(SparseMatrix &A, const std::vector<double> &refinedKnots) const;

    // Helper functions
    bool inHalfopenInterval(double x, double x_min, double x_max) const;

    // Knot sequence related
    bool isKnotSequenceRegular() const;
    bool isKnotSequenceRegular(const std::vector<double> &vec) const;
    bool isRefinement(const std::vector<double> &refinedKnots) const;
    std::vector<double> knotSequenceRegular(std::vector<double>& X);
    std::vector<double> knotSequenceFree(std::vector<double>& X);

    // Member variables
    int degree;
    std::vector<double> knots;
    int targetNumBasisfunctions;
};

} // namespace MultivariateSplines

#endif // BASIS1D_H
