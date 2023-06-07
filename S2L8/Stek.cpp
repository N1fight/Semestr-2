#include <iostream>
#include <vector>

template<typename T>
class Stek
{
private:
	unsigned int m_size = 0; // текущий размер стека
	unsigned int m_max_size = 0; // максимально возможный размер стека
	T* m_mas = nullptr;
public:
	Stek(int max_size) :m_max_size(max_size)
	{
		try 
		{
			m_mas = new T[max_size]; // выделение памяти
		}
		catch (const std::bad_alloc& exeption) 
		{
			std::cerr << exeption.what() << "\n"; // вывод сообщения об ошибке "невозможно выделить память"
		}
	}



	unsigned int Size()  // метод для получения текущего размера стека
	{
		return m_size;
	}

	bool Empty() // проверка пуст ли стек
	{
		if (m_size == 0) 
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}

	void Push(T element) // метод для добавления в стек элемента
	{
		if (m_size < m_max_size) 
		{
			m_mas[m_size] = element;
			m_size++;
		}
		else 
		{
			throw std::overflow_error("Stek is full"); // искключение, если текущий размер превышает максимальный
		}

	}

	T Pop() // метод для удаления элемента из стека
	{
		if (m_size == 0) 
		{
			throw std::out_of_range("out of range! Stek is empty"); // исключение в случае удаления элемента из пустого стека 
		}
		else 
		{
			T elementl = m_mas[0]; // сохранение значения 1 элемента стека 
			for (int i = 0; i < m_size - 1; i++) // сдвиг всех элментов на 1 позицию влева
			{
				m_mas[i] = m_mas[i + 1];
			}
			--m_size; // уменьшение размера стека на 1
			return elementl;
		}
	}

	void Top() // метод для получения значения верхнего элемента стека
	{
		if (m_size == 0) 
		{
			throw std::logic_error("Error! Stek is empty"); // исключение в случае пустого стека для избежания логической ошибки
		}
		else 
		{

			std::cout << m_mas[m_size - 1] << "\n"; // вывод значения верхнего элемента в поток вывода
		}


	}

	~Stek() // деструктор
	{
		if (m_mas != nullptr) 
		{
			delete[] m_mas;
		}
	}
};

int main()
{
	Stek<int> stek(3);
	stek.Push(1);
	stek.Push(1);
	stek.Push(1);
	std::cout << "Stek size is " << stek.Size() << "\n";
	try 
	{
		stek.Push(2);
	}
	catch (const std::exception& ex) 
	{
		std::cerr << ex.what() << "\n";
	}	

	Stek<std::string> str(3);
	try 
	{
		str.Top();
	}
	catch (const std::exception& ex) 
	{
		std::cerr << ex.what() << "\n";
	}
	std::cout << "stek is empty? " << str.Empty() << "\n";
	/*str.Push("Hello");
	str.Push("world");
	str.Push("!");*/
	std::cout << "stek is empty? " << str.Empty() << "\n";
	std::cout << "stek size is " << str.Size() << "\n";
	try 
	{
		str.Pop();
	}

	catch (const std::exception& ex) 
	{
		std::cerr << ex.what() << "\n";
	}
	str.Push("Hello world!");
	std::cout << "stek size is " << str.Size() << "\n";
	str.Top();
}
