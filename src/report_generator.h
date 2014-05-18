#ifndef _REPORT_GENERATOR_H_
#define _REPORT_GENERATOR_H_


#include <string>
using std::string;

class ParametersArray;

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
    
    void outReadyReport();

    ParametersArray *m_paramsArr;
    string m_report;
};

#endif
