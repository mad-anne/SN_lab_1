#include <iostream>
#include <fstream>
#include <string>

#include "files/header/ParametersReader.h"

ParametersReader::ParametersReader()
= default;

ParametersReader::~ParametersReader()
= default;

void ParametersReader::read(std::string fileName)
{
    std::string name;
    double value;
    std::ifstream infile(fileName);
    while (infile >> name >> value)
        parameters[name] = value;
    infile.close();
}

void ParametersReader::printParameters() const
{
    for (const auto& parameter : parameters)
        std::cout << parameter.first << " : " << parameter.second << std::endl;
}

double ParametersReader::getParameter(std::string name) const
{
    return parameters.at(name);
}