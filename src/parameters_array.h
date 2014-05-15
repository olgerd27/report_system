#ifndef _PARAMETERS_ARRAY_H_
#define _PARAMETERS_ARRAY_H_

#include <map>
#include <string>
using std::map;
using std::string;

class Parameter;

// if use ParametersArrayImpl
//class map;
//class ParametersArrayImpl;

typedef map<string, Parameter *> typeParams;

class ParametersArray
{
public:
    ParametersArray();
    ~ParametersArray();
    bool addParameter(const string &name, Parameter *value);

private:
    //ParametersArrayImpl *m_impl;
    typeParams m_params;
};

#endif
