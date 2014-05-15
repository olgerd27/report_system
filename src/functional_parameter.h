#ifndef _FUNCTIONAL_PARAMETER_H_
#define _FUNCTIONAL_PARAMETER_H_

#include "parameter.h"

class FunctionalParameter : public Parameter
{
public:
    ~FunctionalParameter();
    string value();
};

FunctionalParameter::~FunctionalParameter()
{
}

string FunctionalParameter::value()
{
    return string("functional parameter");
}

#endif
