#ifndef _TEXT_PARAMETER_H_
#define _TEXT_PARAMETER_H_

#include "parameter.h"

class TextParameter : public Parameter
{
public:
    TextParameter(const string &str);
    ~TextParameter();
    string value();
private:
    string m_data;
};

TextParameter::TextParameter(const string &str)
    : m_data(str)
{
}

TextParameter::~TextParameter()
{
}

string TextParameter::value()
{
    return m_data;
}

#endif
