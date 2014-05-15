#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <string>
using std::string;

class Parameter
{
public:
    virtual ~Parameter() {}
    virtual string value() = 0;
};

#endif
