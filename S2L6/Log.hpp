#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

namespace wk
//namespace wk позволяет группировать определения функций, классов и переменных в одну логическую единицу 
// именования, чтобы избежать конфликтов имен с определениями из других библиотек или пространств имен. 
//Например, использование namespace wk перед объявлением класса Log означает, что класс Log принадлежит 
//пространству имен wk.
{

    enum class LogLevel // значения уровня логирования 
    {
        DEBUG,
        RELEASE
    };
    enum class LogType // тип сообщения лога
    {
        Info,
        Error,
        Debug
    };

    class Log 
    {
    private:
        static std::ofstream w_out; // запись в файл
        static LogLevel w_log_level; // уровень логирования 

    public:
        static void SetPath(const std::string& path) // установка пути к логу файлу 
        {
            w_out.open(path);
        }

        static void SetLevel(LogLevel logLevel) // установка уровня логирования
        {
            w_log_level = logLevel;
        }
        static void Write(LogType type, const std::string& str) // метод для записи сообщений в лог файл
        {
            SYSTEMTIME st; // структура данных для хранения информации о текущем времени
            GetLocalTime(&st); // функция для получения информации о текущем локальном времени.
            std::string in_file;
            switch (type) //  оператор выбора для определения типа сообщения лога
            {
            case LogType::Info:
                in_file += "Info: " + str;
                break;

            case LogType::Error:
                in_file += "Error: " + str;
                break;

            case LogType::Debug:
                in_file += "Debug" + str;
                break;

            default:
                break;
            }

            if (w_log_level == LogLevel::DEBUG) 
            {
                // Эта строка отвечает за вывод сообщения лога в стандартный поток ошибок, т.е в консоль
                std::cerr << in_file << "\n" << st.wHour << "h" << ":" << st.wMinute << "m" << ":" << st.wSecond << "s" << "\n";
            }
            //запись сообщения в лог файл c указанием времени
            w_out << in_file << "\n" << st.wHour << "h" << ":" << st.wMinute << "m" << ":" << st.wSecond << "s" << "\n";
            w_out.flush(); // очистка буфера вывода и запись данных в файл
        }


    };

}