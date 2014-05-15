#ifndef _PARAMETERS_ARRAY_IMPL_H_
#define _PARAMETERS_ARRAY_IMPL_H_

#include <map>
#include "parameter.h"

class ParametersArrayImpl
{
public
    ParametersArrayImpl();
private:
    std::map<std::string, Parameter *> m_params;
};

#endif
