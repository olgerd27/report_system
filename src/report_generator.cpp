#include <iostream>
#include <fstream>
using namespace std;

#include "report_generator.h"
#include "parameters_array.h"
#include "text_parameter.h"

ReportGenerator::ReportGenerator()
{
    m_paramsArr = new ParametersArray;
}

ReportGenerator::~ReportGenerator()
{
    delete m_paramsArr;
}

void ReportGenerator::run()
{
    
}
