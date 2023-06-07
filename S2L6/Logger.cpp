#include "log.hpp"

int main()
{
    wk::Log::SetPath("Loger.txt");
    wk::Log::SetLevel(wk::LogLevel::RELEASE);
    wk::Log::Write(wk::LogType::Info, "logger is work ");
}