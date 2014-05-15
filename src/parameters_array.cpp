#include <algorithm>
#include "parameters_array.h"
#include "parameter.h"
//#include "parameters_array_impl.h"

// functor for clearing memory of pointers from map container
#include <iostream>
struct ClearMemoryFromMap
{
    template<typename T>
    void operator()(const T &v)
    {
        std::cout << "clearing data from address = " << v.second << std::endl;
        delete v.second;
    }
};

ParametersArray::ParametersArray()
{
//    m_impl = ParametersArrayImpl;
}

ParametersArray::~ParametersArray()
{
    std::for_each(m_params.begin(), m_params.end(), ClearMemoryFromMap());
}

bool ParametersArray::addParameter(const string &name, Parameter *value)
{
    std::pair<typeParams::iterator, bool> ret = m_params.insert(make_pair(name, value));
    return ret.second;
}
