#include <stdexcept>
#include "logger.h"
#include <ctime>

Logger::Logger(const char *fileName)
    : m_fileHandler(std::fopen(fileName, "a"))
{
    if(!m_fileHandler)
        throw std::runtime_error("Cannot open log file");
}

Logger::~Logger()
{
    std::fclose(m_fileHandler);
}

void Logger::write(const std::string &str)
{
    time_t timeValue = time(0);
    std::string strRes = ctime(&timeValue);
    strRes = strRes.erase(strRes.size() - 1) + ":\t" + str + '\n';
    if( std::fputs(strRes.c_str(), m_fileHandler) == EOF )
        throw std::runtime_error("Cannot write data to a log file");
}
