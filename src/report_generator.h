#ifndef _REPORT_GENERATOR_H_
#define _REPORT_GENERATOR_H_

#include <string>
using std::string;

class ParametersArray;
class ParameterNotFoundBhvr;

class ReportGenerator
{
public:
    ReportGenerator();
    ~ReportGenerator();
    void run();

private:
    void addFunctionalParameters();

    void addTextParameters();

    void readReportTemplate();
    void insertParameters();
    void findAndInsertParameters(const string &markerLeft, const string &markerRight, ParameterNotFoundBhvr &bhvr);
    bool findParameter(const string &markerLeft, const string &markerRight, 
                       string::size_type &posStartPar, string::size_type &posStartWord,
                       string::size_type &posEndPar) const;
    
    void outReadyReport();

    ParametersArray *m_paramsArr;
    string m_report;
};

#endif
