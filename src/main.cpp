#include <iostream>
#include <exception>
#include "report_generator.h"

int main()
{
    ReportGenerator generator;
    try {
        generator.run();
    }
    catch(const std::exception &ex) {
        std::cerr << "--!Error. Cannot generate the report, the reason are:\n" << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
