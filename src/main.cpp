#include <iostream>
#include <exception>
#include "report_generator.h"
#include "logger.h"

int main()
{
    ReportGenerator generator;
    try {
        generator.run();
        Log.write("[INFO] The report was generated successfully");
        std::cout << "The report was generated successfully\n";
    }
    catch(const std::exception &ex) {
        Log.write(string("[ERROR] ") + ex.what());
        std::cerr << "--!Error. Cannot generate the report, the reason are:\n" << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
