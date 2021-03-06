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


#include "datasample.h"

namespace MultivariateSplines
{

DataSample::DataSample(double x, double y)
{
    setData(std::vector<double>(1, x), y);
}

DataSample::DataSample(std::vector<double> x, double y)
{
    setData(x, y);
}

DataSample::DataSample(DenseVector x, double y)
{
    std::vector<double> newX;

    for (int i = 0; i < x.size(); i++)
    {
        newX.push_back(x(i));
    }

    setData(newX, y);
}

void DataSample::setData(const std::vector<double> &x, const double &y)
{
    this->x = x;
    this->y = y;
}

bool DataSample::operator<(const DataSample &rhs) const
{
    assert(this->getDimX() == rhs.getDimX());

    for(unsigned int i = 0; i < this->getDimX(); i++)
    {
        if(x.at(i) < rhs.getX().at(i))
            return true;
        else if(x.at(i) > rhs.getX().at(i))
            return false;
    }

    return false;
}

std::ostream &operator<<(std::ostream &outputStream, const DataSample &sample)
{
    outputStream << "Sample: (";

    bool firstLoop = true;
    for(auto &coordinate : sample.getX())
    {
        if(!firstLoop)
            outputStream << ", ";

        outputStream << coordinate;
        firstLoop = false;
    }

    outputStream << ") = (" << sample.getY() << ")";

    return outputStream;
}

} // namespace MultivariateSplines
