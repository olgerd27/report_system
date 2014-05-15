#ifndef _REPORT_GENERATOR_H_
#define _REPORT_GENERATOR_H_

class ParametersArray;

class ReportGenerator
{
public:
    ReportGenerator();
    ~ReportGenerator();
    void run();

private:
    ParametersArray *m_paramsArr;
};

#endif
