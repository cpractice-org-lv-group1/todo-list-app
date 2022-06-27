#include "Logger.h"

inline std::string getCurrentDateTime()
{
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(p);
    char str[26];
    ctime_s(str, sizeof str, &t);
    return str;
}

void Logger(std::string logMsg)
{
    std::string file ="logFile.txt";
    std::string now(getCurrentDateTime());
    now.erase(std::remove_if(now.begin(),
        now.end(),
        [](auto ch)
        {
            return (ch == '\n' ||
                ch == '\r');
        }),
        now.end());

    std::ofstream ofs(file.c_str(), std::ios_base::out | std::ios_base::app);
    ofs <<"["+now +"]   " << logMsg << '\n';
    ofs.close();
}
