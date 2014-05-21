#include <algorithm>
#include "parameters_array.h"
#include "parameter.h"
//#include "parameters_array_impl.h"

// functor for clearing memory of pointers from map container
struct ClearMemoryFromMapValue
{
    template<typename T>
    void operator()(const T &v)
    {
        delete v.second;
    }
};

ParametersArray::ParametersArray()
{
}

ParametersArray::~ParametersArray()
{
    std::for_each(m_params.begin(), m_params.end(), ClearMemoryFromMapValue());
}

bool ParametersArray::addParameter(const string &name, Parameter *value)
{
    std::pair<typeParams::iterator, bool> ret = m_params.insert(make_pair(name, value));
    return ret.second;
}

/***
* Get a parameter value by its name. If name was not found, return empty string instance
*/
string ParametersArray::parameterValue(const string &parameterName) const
{
    typeParams::const_iterator it = m_params.find(parameterName);
    return (it != m_params.end()) ? it->second->value() : string();
}
