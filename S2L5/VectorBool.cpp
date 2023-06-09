
#include <iostream>
#include <vector>

template <size_t BITS>
class BoolVector 
{

private:
    std::vector<unsigned int> m_bits;
    size_t m_size;

public:
    BoolVector() : m_size(0) {}

    // ����� ���������� � ����� �������
    void push_back(bool value) 
    {
        if (m_bits.size() == m_size / BITS) 
        {
            m_bits.push_back(0);
        }
        size_t bit_idx = m_size % BITS;
        m_bits.back() |= (value ? 1 : 0) << bit_idx; // ������ ���� value � ���� m_bits.back()
        ++m_size;
    }

    // ����� � �������� ��������� � ��������� �������� �� �������
    bool& operator[](size_t idx) 
    {
        size_t block_idx = idx / BITS;
        size_t bit_idx = idx % BITS;
        return reinterpret_cast<bool*>(&m_bits[block_idx])[bit_idx]; /* std::vector<bool> �� ������
        ��������� ���� � ������, � ���������� ���������� ������������� ������� ������������������ 
        � ���� ������� ������ ������������� ������� (������ 32 ��� 64 ����), ��� ������ ���� ������ 
        ��������� ����� ��������������� � ������. ��� ��������� � ���������� ���� ������ ����� 
        ���������� �������� ��������� �� ������ ���� � ������� � ��������� ������ � ������� ���� 
        �� �����������.*/
        //� ��������� ������� ���������� ���������� �������� ����� � ����, � ����� ������������ 
        //reinterpret_cast ��� ���������� ��������� �� ���� � ���� ��������� �� bool*, 
        // ����� �������� ������ � ��������� ����� ����� ��������[].
    }
    // reinterpret_cast - ��� ���� �� ���������� ����� C++, ������� ������������ ��� �������������� 
    // ������ ���� ��������� �� ������ ��� ��������� �������������� ����, ��� ��������� ������������ 
    // �������� ���������.
    const bool& operator[](size_t idx) const 
    {
        size_t block_idx = idx / BITS;
        size_t bit_idx = idx % BITS;
        return reinterpret_cast<const bool*>(&m_bits[block_idx])[bit_idx];
    }

    // ����� size
    size_t size() const 
    {
        return m_size;
    }
    
    // ����� insert � erase
    void insert(size_t idx, bool value) 
    {
        if (idx > m_size) {
            throw std::out_of_range("Index is out of range");
        }
        push_back(false);
        for (size_t i = m_size - 1; i > idx; --i) 
        {
            (*this)[i] = (*this)[i - 1];
        }
        (*this)[idx] = value;
    }

    void erase(size_t idx) 
    {
        if (idx >= m_size) 
        {
            throw std::out_of_range("Index is out of range");
        }
        for (size_t i = idx; i < m_size; ++i) 
        {
            (*this)[i] = (*this)[i + 1];
        }
        --m_size;
    }
};

int main() 
{
    BoolVector<8> bv;

    // ���������� �����
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(true);
    // ����� �������� �� �������
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << std::endl;

    // ��������� �������� �� �������
    bv[2] = true;

    // ����� ����������� �������� �� �������
    std::cout << bv[2] << std::endl;

    // ���������� ���� �� �������
    bv.insert(2, false);

    // ����� ���������� ��������
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << " " << bv[4] << std::endl;

    // �������� ���� �� �������
    bv.erase(3);

    // ����� ���������� ��������
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << " " << bv[3] << std::endl;

    // ����� ������� �������
    std::cout << bv.size() << std::endl;

    return 0;
}