#ifndef _TEXT_PARAMETER_H_
#define _TEXT_PARAMETER_H_

#include "parameter.h"

class TextParameter : public Parameter
{
public:
    ~TextParameter();
    string value();
};

TextParameter::~TextParameter()
{
}

string TextParameter::value()
{
    return string("text parameter");
}

#endif
