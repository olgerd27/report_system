#ifndef _FUNCTIONAL_PARAMETER_H_
#define _FUNCTIONAL_PARAMETER_H_

#include "parameter.h"

// FuncPtrT function must return his data in string or char* format
template<typename FuncPtrT>
class FunctionalParameter : public Parameter
{
public:
    FunctionalParameter(FuncPtrT pf);
    ~FunctionalParameter();
    string value();
private:
    FuncPtrT m_pFunction;
};

template<typename FuncPtrT>
FunctionalParameter<FuncPtrT>::FunctionalParameter(FuncPtrT pf)
    : m_pFunction(pf)
{
}

template<typename FuncPtrT>
FunctionalParameter<FuncPtrT>::~FunctionalParameter()
{
}

template<typename FuncPtrT>
string FunctionalParameter<FuncPtrT>::value()
{
    return (*m_pFunction)();
}

#endif
