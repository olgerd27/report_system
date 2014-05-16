#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#include "report_generator.h"
#include "parameters_array.h"
#include "text_parameter.h"

/***
* function for using as a functional parameter. Such function may be many.
* This function can be some system function or user function but in external file
*/
string currentData()
{
    time_t timeValue = time(0);
    return string( ctime(&timeValue) );
}


// ReportGenerator
ReportGenerator::ReportGenerator()
{
    cout << "create generator\n";
    m_paramsArr = new ParametersArray;
}

ReportGenerator::~ReportGenerator()
{
    cout << "destroy generator\n";
    delete m_paramsArr;
}

void ReportGenerator::run()
{
    cout << "run generator\n";
}
