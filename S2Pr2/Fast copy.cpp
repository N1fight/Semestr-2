/*����������� ���� � ����� �������� ������������� ����������� ������ �� ������� ������� mas_a 
��� ����������� � ������ mas_b, ���� ������ ������� mas_a ��������� ������ ������� mas_b. 
���������� ���������, ��� ������ ������� mas_a �� ������ ������� ������� mas_b ����� ������������, 
���� ������������ ������� �����������, ������� ��������� ������� ��������.*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// ��������� ������������ ������ ���� �� ������ �����, ���� �� 8

enum mode
{
    Byte, Byte8
};

template <typename T> /*�������� ���������� ����, ������� ����� ���� ������� �� �����
���������� ��� ������ �� ����� ����������. ��� ��������� ��������� ���������� ���, 
������� ����� �������� � ������� ������ ������ ��� ������������� ���������� ��������� ���� 
��� ������� ����.*/

void copy(T* given, T* copied, uint64_t bytescount, mode Mode)
{
    /* ���� ����� ����������� 1 ����, �� ���������� ����������� ������ �� ����� ������� ������
    � ������ ��� ������ �����, ����������� �� ������� ����� � ����������� ���*/
    if (Mode == mode::Byte)
    {
        char* Fgiven = (char*)given;
        char* Scopied = (char*)copied;
        for (uint64_t i = 0; i < bytescount; i++)
        {
            Fgiven[i] = Scopied[i];
        }
    }
    /* ����� div ��������� ���������� 8 ������ ������, ������� ����� �����������
    ��������� mod ������� ������� �� ������� ���������� ���� �� 8. 
    ���� div ������� �� ���� �� ���������� ��� �� ����, ��� � ������. ����
    mod  ������� �� ���� �� ���������� ���������� ������� copy. �����, �.� ���� div 
    ����� ����, ���������� ������� copy*/ 
    else 
    {
        uint64_t div = bytescount / 8;
        uint8_t mod = bytescount % 8;
        if (div > 0) {
            double* Fgiven = (double*)given;
            double* Scopied = (double*)copied;
            for (uint64_t i = 0; i < div; i++)
            {
                Fgiven[i] = Scopied[i];
            }
            if (mod != 0) 
            {
                copy(given + div, copied + div, mod, mode::Byte);
            }
        }
        else copy(given, copied, mod, mode::Byte);
    }
}

int main()
{

    int N[10] = { 1,2,3,4,5,6,7,8,9, 10 };
    int M[10];

    copy(M, N, sizeof(N), mode::Byte8);
    for (int i = 0; i < sizeof(N)/sizeof(int); ++i)
    {
        std::cout << M[i] << " ";
    }
}
/* ���� ��� ���������� �������� ����� ������ ������ ��������(8 ���� � ������),
���������, ������� ��������� double ����� ����������� �� ���� ���, 
� ����� ��������� ����������� �����, ���� ���� �������, ������� ���������� 
����������� � ������� ����� � �������� ������. ��� ��������� �������� ��������������� 
����������� � ��������� ��������� ������� �� ����� �������. ����� ������������� ���������� 
�� char ��� ��������� ����������� ��������� ����������� ������ ����� ����������, 
�.�. char ����� ������� ������, ��� ���, ������� ����������, � ����� ���� ����� ���������� 
�������� � ������.*/