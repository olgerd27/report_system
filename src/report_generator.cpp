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


/***
* ReportGenerator methods
*/
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

/***
* Main calculations
*/
void ReportGenerator::insertParameters()
{
    findAndInsertRequiredParameters("{*", "}");
    findAndInsertNotRequiredParameters("{", "}");
    /**********
    Method insertRequiredParameters() is almost identical with method insertNotRequiredParameters().
    Difference between this methods is only behaviour of application when none parameters was found.
    It is necessary to think how to simplify this code and maybe use one method findAndInsertParameters() with different arguments.
    */
}

void ReportGenerator::findAndInsertRequiredParameters(const string &markerLeft, const string &markerRight)
{
    string parName, parValue;
    string::size_type posStartPar = 0, posStartWord = 0, posEndPar = 0;
    
    // find and replace required parameters
    while( findParameter(markerLeft, markerRight, posStartPar, posStartWord, posEndPar) ) {
        parName = m_report.substr(posStartWord, posEndPar - posStartWord);
        parValue = m_paramsArr->parameterValue(parName);
        if(parValue.empty())
            throw runtime_error(string("Textual parameter \"") + parName + "\" was not found in the ini-file");
        m_report.replace(posStartPar, posEndPar - posStartPar + 1, parValue);
    }
}


void ReportGenerator::findAndInsertNotRequiredParameters(const string &markerLeft, const string &markerRight)
{
    string parName, parValue;
    string::size_type posStartPar = 0, posStartWord = 0, posEndPar = 0;
    
    // find and replace not required parameters
    posStartPar = 0, posStartWord = 0, posEndPar = 0;
    while( findParameter(markerLeft, markerRight, posStartPar, posStartWord, posEndPar) ) {
        parName = m_report.substr(posStartWord, posEndPar - posStartWord);
        parValue = m_paramsArr->parameterValue(parName);
        if(parValue.empty())
            parValue = '\n';
        m_report.replace(posStartPar, posEndPar - posStartPar + 1, parValue);
    }
}

bool ReportGenerator::findParameter(const string &markerLeft, const string &markerRight, 
                                    string::size_type &posStartPar, string::size_type &posStartWord,
                                    string::size_type &posEndPar) const
{
    posStartPar = m_report.find(markerLeft, posEndPar);
    if(posStartPar == string::npos) return false; // parameter not found
    posStartWord = posStartPar + markerLeft.size();
    posEndPar = m_report.find(markerRight, posStartWord);
    return true;
}

/***
* Out results to ready report file
*/
void ReportGenerator::outReadyReport()
{
    ofstream out("../data/out/report.txt"); // open file to out data with prevoius truncate its contents
    if( !out.is_open() )
        throw runtime_error("Cannot open result report file");
    out << m_report;
    out.close();
}
