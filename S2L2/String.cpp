#include <iostream>
class String
{
private:
    size_t m_size = 1; 
    char* m_str = nullptr;

public:
    String() = default; // конструктор по умолчания, инициализирующий объекты пустой строкой
    // Конструктор копирования
    String(const char* str) 
    {
        m_size = strlen(str);
        m_str = new char[m_size + 1];
        std::copy(str, str + m_size, m_str);
        m_str[m_size] = 0;
    }
    String(String& o_str)
    {
        m_size = o_str.m_size;
        m_str = new char[m_size + 1];
        std::copy(o_str.m_str, o_str.m_str + m_size, m_str);
    }
    // Оператор присваивания копированием
    String& operator = (const String& o_str) 
    {
        if (m_str != nullptr)
            delete[] m_str;
        m_size = o_str.m_size;
        m_str = new char[m_size + 1];
        std::copy(o_str.m_str, o_str.m_str + m_size + 1, this->m_str);
        return *this;
    }
    // Оператор += 
    String& operator += (const String& s1) 
    {
        m_size = this->m_size + s1.m_size;
        auto tempstr = m_str;

        m_str = new char[m_size + 1];
        std::copy(tempstr, tempstr + strlen(tempstr), m_str);
        std::copy(s1.m_str, s1.m_str + s1.m_size + 1, m_str + strlen(tempstr));
        delete[] tempstr;
        return *this;
    }
    // Операторы + 
    String operator + (const String& s2) 
    {

        String tmp;
        tmp = *this;
        tmp += s2;
        return tmp;
    }
    // Оператор [] 
    char& operator [] (size_t a) {
        return m_str[a];
    }
    // strcmp выполняет сравнение строк и возвращает значение, которое указывает их отношение
    // Операторы <, >, ==
    bool operator == (String& s) 
    {
        return std::strcmp(this->m_str, s.m_str) == 0;
    }
    bool operator < (String& s) 
    {
        return std::strcmp(this->m_str, s.m_str) < 0;
    }
    bool operator > (String& s) 
    {
        return std::strcmp(this->m_str, s.m_str) > 0;
    }

    // Метод length 
    size_t length() 
    {
        return m_size;
    }

    // Метод c_str 
    char* c_str() 
    {
        return m_str;
    }

    // Метод find 
    int find(const char& a) 
    {
        for (int i = 0; i < m_size; i++) {
            if (m_str[i] == a) {
                return i;
            }
        }
        return -1;
    }

    // Метод at 
    char at(int i) {
        if ((i >= 0) && (i < m_size)) {
            return m_str[i];
        }
        return -1;
    }

    // Метод print() нужен при отладке или выводе отчётов на экран, когда нужно убедиться 
    // в значении объекта String
    void print() 
    {
        for (int i = 0; i < m_size; i++) {
            std::cout << m_str[i];
        }
        std::cout << "\n";
    }
    friend std::ostream& operator << (std::ostream& os, const String& str);
    friend std::istream& operator >> (std::istream& in, String& str);

    // Деструктор
    ~String() {
        if (m_str != nullptr)
            delete[] m_str;
    }


};
// Операторы ввода и вывода в поток
std::ostream& operator << (std::ostream& out, const String& str) {
    out << str.m_str;
    return out;
}

std::istream& operator >> (std::istream& in, String& str) {
    char* inStr = new char[1000000];
    in >> inStr;
    str.m_str = inStr;
    return in;
}

int main()
{
    String s("Hel");
    String a("lo");
    String c(" world!");
    String f("Hi, my name is Ivan");
    String s3;
    s += a;
    s3 = s + a;
    std::cout << s << "\n";
    std::cout << s3;
    bool k = s < a;
    std::cout << k << "\n";
    std::cout << f.c_str() << "\n";
    std::cout << s.at(2) << "\n";
    std::cout << f.length() << "\n";
    String sCin;
    std::cin >> sCin;
    std::cout << sCin;
}