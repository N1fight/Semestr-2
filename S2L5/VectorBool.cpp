
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

    // Метод добавления в конец вектора
    void push_back(bool value) 
    {
        if (m_bits.size() == m_size / BITS) 
        {
            m_bits.push_back(0);
        }
        size_t bit_idx = m_size % BITS;
        m_bits.back() |= (value ? 1 : 0) << bit_idx; // запись бита value в блок m_bits.back()
        ++m_size;
    }

    // Метод и оператор получения и изменения значения по индексу
    bool& operator[](size_t idx) 
    {
        size_t block_idx = idx / BITS;
        size_t bit_idx = idx % BITS;
        return reinterpret_cast<bool*>(&m_bits[block_idx])[bit_idx]; /* std::vector<bool> не хранит
        отдельные биты в памяти, а использует внутреннее представление битовой последовательности 
        в виде массива блоков определенного размера (обычно 32 или 64 бита), где каждый блок хранит 
        несколько битов последовательно в памяти. При обращении к отдельному биту внутри блока 
        необходимо получить указатель на данный блок в массиве и разрешить доступ к каждому биту 
        по отдельности.*/
        //В указанных методах происходит вычисление индексов блока и бита, а затем используется 
        //reinterpret_cast для приведения указателя на блок к типу указателя на bool*, 
        // чтобы получить доступ к отдельным битам через оператор[].
    }
    // reinterpret_cast - это один из операторов языка C++, который используется для преобразования 
    // одного типа указателя на другой тип указателя несовместимого типа, без изменения фактического 
    // значения указателя.
    const bool& operator[](size_t idx) const 
    {
        size_t block_idx = idx / BITS;
        size_t bit_idx = idx % BITS;
        return reinterpret_cast<const bool*>(&m_bits[block_idx])[bit_idx];
    }

    // Метод size
    size_t size() const 
    {
        return m_size;
    }
    
    // Метод insert и erase
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

    // Добавление битов
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(true);
    // Вывод значения по индексу
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << std::endl;

    // Изменение значения по индексу
    bv[2] = true;

    // Вывод измененного значения по индексу
    std::cout << bv[2] << std::endl;

    // Добавление бита по индексу
    bv.insert(2, false);

    // Вывод измененных значений
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << " " << bv[4] << std::endl;

    // Удаление бита по индексу
    bv.erase(3);

    // Вывод измененных значений
    std::cout << bv[0] << " " << bv[1] << " " << bv[2] << " " << bv[3] << " " << bv[3] << std::endl;

    // Вывод размера вектора
    std::cout << bv.size() << std::endl;

    return 0;
}