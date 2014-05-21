#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstdio>
#include <string>

class Logger
{
public:
    static Logger & Instance()
    {
        static Logger instance("../data/out/logfile.txt");
        return instance;
    }
    
    ~Logger();
    void write(const std::string &str);

private:
    Logger(const char *fileName);
    Logger(const Logger &item);
    Logger & operator=(const Logger &item);

    FILE *m_fileHandler;
};

#define Log Logger::Instance()

#endif
