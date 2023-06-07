// Наследование использовалось для классов тругольник, круг и прямоугольник, которым присвоили свойства
// класса фигуры
// Полиморфизм является функция Area 
// firtual используется для того, чтобы переопределять функции в разных классах
#include <iostream>
#include <math.h>
const double Pi = 3.141592653589793;

enum class Color
{
    White,
    Blue,
    Red
};

struct Point
{
    int x;
    int y;
};

class Figures
{
private:
    Color m_color;

protected:
    bool is_figure = 1;
    Point* m_point = nullptr;
    double* m_sizes = nullptr;
    int m_sides;
    int m_points;

public:

    Figures(Color color, int sides, int points) 
    {
        m_color = color;
        m_sides = sides;
        m_points = points;
        m_sizes = new double[m_sides];
        m_point = new Point[points];
        for (int i = 0; i < m_sides; i++) 
        {
            m_sizes[i] = 0;
        }
    }
    void SetPoints() 
    {
        for (int i = 0; i < m_points; i++) 
        {
            std::cin >> m_point[i].x >> m_point[i].y;
        }
    }

    void GetSides() 
    {
        for (int i = 0; i < m_sides; i++) 
        {
            for (int j = i + 1; j < m_sides; j++) 
            {
                m_sizes[i] =pow((pow((m_point[j].x - m_point[i].x), 2) + pow((m_point[j].y - m_point[i].y), 2)),0.5);
                std::cout << m_sizes[i] << " ";
            }
        }
        std::cout << "\n";
    }

    void GetPoints() {
        for (int i = 0; i < m_points; i++) 
        {
            std::cout << "x" << i << "=" << m_point[i].x << " ";
            std::cout << "y" << i << "=" << m_point[i].y << "\n";
        }
    }


    virtual void Area() = 0;

    virtual ~Figures() 
    {
        if (m_sizes != nullptr) 
        {
            delete[] m_sizes;
        }
        if (m_point != nullptr) 
        {
            delete[] m_point;
        }
    }

};

class Triangle : public Figures 
{ 

public:
    Triangle(Color color, int sides, int points) : Figures(color, sides, points) 
    {
        if (sides != 3 || points != 3) 
        {
            std::cout << "not a trianhgle" << "\n";
            is_figure = 0;
        }

    }

    void Area() override 
    {
        if (is_figure == 1) 
        {
            double p = (m_sizes[0] + m_sizes[1] + m_sizes[2]) / 2.00000;
            std::cout << "area of triangle is " << sqrt(p * (p - m_sizes[0]) * (p - m_sizes[1]) * (p - m_sizes[2])) << "\n";
        }
        else 
        {
            std::cout << 0 << "\n";
        }
    }


    virtual ~Triangle() {

    }
};

class Rectangle : public Figures 
{

public:
    Rectangle(Color color, int sides, int points) : Figures(color, sides, points) 
    {
        if (sides != 2 || points != 4) 
        {
            std::cout << "not a rectangle" << "\n";
            is_figure = 0;
        }

    }

    void Area() override 
    {
        if (is_figure == 1) 
        {
            std::cout << "area of rectangle is " << m_sizes[0] * m_sizes[1] << "\n";
        }
        else 
        {
            std::cout << 0 << "\n";
        }
    }

    virtual ~Rectangle() 
    {

    }
};

class Circle : public Figures 
{

public:
    Circle(Color color, int sides, int points) : Figures(color, sides, points) 
    {
        if (sides != 1 || points != 1) 
        { // у круга в качестве стороны выступает его радиус.
            std::cout << "not a circle" << "\n";
            is_figure = 0;
        }

    }

    void Area() override 
    {
        if (is_figure == 1) 
        {
            std::cout << "area of circle is " << Pi * pow(m_sizes[0], 2) << "\n"; 
            // pow - возведение в степень
        }
        else 
        {
            std::cout << 0 << "\n";
        }
    }


    virtual ~Circle() 
    {

    }
};



int main()
{
    Triangle triangle(Color::White, 3, 3);
    triangle.SetPoints();
    triangle.GetSides();
    triangle.GetPoints();
    triangle.Area();

    Rectangle rectangle(Color::Blue, 2, 4);
    rectangle.GetSides();
    rectangle.SetPoints();
    rectangle.GetPoints();
    rectangle.Area();

    Circle  circle(Color::Red, 1, 1);
    circle.GetSides();
    circle.SetPoints();
    circle.GetPoints();
    circle.Area();
}