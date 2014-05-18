#include <iostream>
#include <fstream>
#include <ctime>
#include <stdexcept>
using namespace std;

#include "report_generator.h"
#include "parameters_array.h"
#include "text_parameter.h"
#include "functional_parameter.h"

/***
* function for using as a functional parameter. Such function may be many.
* This function can be some system function or user function but in external file
*/
string currentData()
{
    time_t timeValue = time(0);
    string strRes = ctime(&timeValue);
    return strRes.erase(strRes.size() - 1); // delete the last character - '\n', returned ctime() function
}
typedef string (*pf)();

// ReportGenerator methods
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
    // input initial data
    addFunctionalParameters();
    addTextParameters();
    readReportTemplate();
    
    // calculation process
    insertParameters();
    
    // show results
    outReadyReport();
}

/***
* Registration of functional parameters
*/
void ReportGenerator::addFunctionalParameters()
{
    if( !m_paramsArr->addParameter("current_date", new FunctionalParameter<pf>(currentData)) )
        throw runtime_error("Cannot add functional parameter");
}

/***
* Registration of text parameters
*/
void ReportGenerator::addTextParameters()
{
    ifstream in("../data/in/parameters.ini");
    if( !in.is_open() )
        throw runtime_error("Cannot open the ini-file with text parameters");
    
    unsigned pos;
    string strLine, name, value;
    while(in >> strLine) {
        pos = strLine.find('='); // character '=' was not found
        if(pos == string::npos)
            throw runtime_error(string("Invalid the next text parameter: \"") + strLine + "\" in ini-file");
        name = strLine.substr(0, pos);
        value = strLine.substr(pos + 1, strLine.size());
        if( !m_paramsArr->addParameter(name, new TextParameter(value)) )
            throw runtime_error(string("Cannot add the text parameter with name: \"") + name + "\"");
    }
    
    in.close();
}

void ReportGenerator::readReportTemplate()
{
    ifstream in("../data/in/template.txt");
    if( !in.is_open() )
        throw runtime_error("Cannot open a report template file");
    getline(in, m_report, '\0');    
    in.close();
}

void ReportGenerator::insertParameters()
{
    
}
    
void ReportGenerator::outReadyReport()
{
    ofstream out("../data/out/report.txt"); // open file to out data with prevoius truncate its contents
    if( !out.is_open() )
        throw runtime_error("Cannot open result report file");
    out << m_report;
    out.close();
}
