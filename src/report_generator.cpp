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
        throw runtime_error("Cannot add a functional parameter. There are unknown reason.");
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
            throw runtime_error(string("Cannot add the text parameter \"") + name + "\" from a ini-file. Maybe this parameter was already added.");
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

/***
* ParameterNotFoundBhvr class and its inheritances, needed for modeling behaviour when any type of parameters not found
*/
struct ParameterNotFoundBhvr
{
    virtual ~ParameterNotFoundBhvr() { }
    virtual void processError(const string &paramName, string &paramValue) const = 0;
};

struct RequiredParameterNotFoundBhvr : public ParameterNotFoundBhvr
{
    ~RequiredParameterNotFoundBhvr() { }
    void processError(const string &paramName, string &paramValue) const
    {
        throw runtime_error(string("Required parameter \"") + paramName + "\" was not found in the ini-file");
    }
};

struct NotRequiredParameterNotFoundBhvr : public ParameterNotFoundBhvr
{
    ~NotRequiredParameterNotFoundBhvr() { }
    void processError(const string &paramName, string &paramValue) const
    {
        paramValue = '\n';
    }
};


void ReportGenerator::insertParameters()
{
    RequiredParameterNotFoundBhvr reqBhvr;
    findAndInsertParameters("{*", "}", reqBhvr);
    
    NotRequiredParameterNotFoundBhvr notReqBhvr;
    findAndInsertParameters("{", "}", notReqBhvr);
}

void ReportGenerator::findAndInsertParameters(const string &markerLeft, const string &markerRight, ParameterNotFoundBhvr &bhvr)
{
    string parName, parValue;
    typePos posLeftPar = 0, posLeftWord = 0, posRightPar = 0;
    
    // find and replace required parameters
    while( findParameter(markerLeft, markerRight, posLeftPar, posRightPar) ) {
        checkMarkerLeftInParameter(posLeftPar, posRightPar, markerLeft);
        posLeftWord = posLeftPar + markerLeft.size();
        parName = m_report.substr(posLeftWord, posRightPar - posLeftWord);
        parValue = m_paramsArr->parameterValue(parName);
        if(parValue.empty())
            bhvr.processError(parName, parValue);
        m_report.replace(posLeftPar, posRightPar - posLeftPar + 1, parValue);
    }
}

bool ReportGenerator::findParameter(const string &markerLeft, const string &markerRight, 
                                    typePos &posLeft, typePos &posRight) const
{
    posLeft = m_report.find(markerLeft, posRight);
    if(posLeft == string::npos) return false; // parameter not found
    posRight = m_report.find(markerRight, posLeft);
    if(posRight == string::npos) return false; // parameter closed brace not found
    return true;
}

void ReportGenerator::checkMarkerLeftInParameter(typePos &posLeft, typePos posRight, const string &markerLeft) const
{
    // check, maybe markerLeft located between posLeftPar and posRightPar
    typePos posLeftTemp = m_report.find(markerLeft, posLeft + 1);
    if(posLeftTemp < posRight)
        posLeft = posLeftTemp;
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
