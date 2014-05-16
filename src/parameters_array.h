#ifndef _PARAMETERS_ARRAY_H_
#define _PARAMETERS_ARRAY_H_

#include <map>
#include <string>
using std::map;
using std::string;

class Parameter;

typedef map<string, Parameter *> typeParams;

class ParametersArray
{
public:
    ParametersArray();
    ~ParametersArray();
    bool addParameter(const string &name, Parameter *value);
    string parameterValue(const string &parameterName) const;

private:
    typeParams m_params;
};

#endif
