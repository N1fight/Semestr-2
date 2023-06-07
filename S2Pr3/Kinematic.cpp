#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <math.h>
#define PI 3.14159265358979

struct Angle {
    float a, b; // углы a и b
};

struct Point {
    float x, y; // координаты точки x и y
};


class KinematicSolver {
private:
    float L1 = 60.f, L2 = 60.f, x0 = 0, y0 = 0;// .f тип float 

public:
    // Принимает угол в радианах и переводит в градусы
    float toDegrees(float radians)
    {
        return radians * (180 / PI);
    }
    KinematicSolver(float length1, float length2)
    {
        L1 = length1; L2 = length2;
    }
    // Ставит в соответствие началу координат x0, y0 координаты x, y
    void SetOrigin(float x, float y) {
        x0 = x; y0 = y;
    }
    // Происходит вычесление угла. Если расстояние между началом и концом робота > чем сумма длин звена L1 + L2,
    // Происходит ошибка и выдаётся результат {-9999.f, -9999.f}. Иначе вычисляются углы a и b.
    Angle Solve(float x, float y)
    {

        float dx = x - x0, dy = y - y0;
        if (std::sqrt(dx * dx + dy * dy) > L1 + L2)
        {
            return { -9999.f, -9999.f };
        }
        float cos_b = (dx * dx + dy * dy - (L1 * L1 + L2 * L2)) / (2 * L1 * L2);
        float sin_b = std::sqrt(1 - cos_b * cos_b);
        float b = std::acos(cos_b);
        float a = std::atan(dy / dx) - std::atan((L2 * sin_b) / (L1 + L2 * cos_b));


        return { a,b };
    }


    bool checkPoint(float& x, float& y) /* Проверяется, находится ли точка с координатами(x, y) в пределах
        область, в которой конечная точка манипулятора может находиться при заданной длине звеньев L1 и L2.*/
    {
        return (std::sqrt(x * x + y * y) <= L1 + L2) && (std::sqrt(x * x + y * y) >= std::abs(L1 - L2));
    }

    bool checkAngles(Angle& ang, Point& pnt) /*Проверяется, находится ли точка с координатами (pnt.x, pnt.y) в заданном радиусе от исходной точки с координатами (x0, y0),
        если бы две связанные между собой плечи с длинами L1 и L2 образовывали углы a и b. Используются математические функции cos и sin для вычисления
        координат конца второго плеча и сравнивает результаты с координатами данной точки*/
    {
        float sresx = L1 * std::cos(ang.a) + L2 * std::cos(ang.a + ang.b);
        float sresy = L1 * std::sin(ang.a) + L2 * std::sin(ang.a + ang.b);
        float x = pnt.x - x0;
        float y = pnt.y - y0;
        return
            ((x - 1.f <= sresx) && (sresx <= x + 1.f)) &&
            ((y - 1.f <= sresy) && (sresy <= y + 1.f));
    }


    void Generate(std::vector<Point>& vector) /*?\генерирует набор точек на двумерной плоскости и сохраняет их в переданный вектор vector.
        Код генерирует точки для нескольких различных геометрических фигур: параболу, окружность, эллипс и прямоугольник.*/
    {


        for (float x = -50.f; x <= 50.f; x += 0.5f) // Первый цикл генерирует точки на параболе, заданной уравнением y = 0.1 * x^2, для значений x от -50 до 50 с шагом 0.5.
        {
            float y = 0.1f * x * x;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        float r = 50.f;
        float posx = 80.f;
        float posy = -80.f;

        for (float x = posx - r; x <= posx + r; x += 0.3f) /*Второй цикл генерирует точки на верхней половине окружности с центром в (80,-80) и радиусом 50.
            Он перебирает значения x от posx-r до posx+r и использует уравнение окружности, чтобы определить соответствующие значения y.*/
        {
            float y = std::sqrt(r * r - std::pow((x - posx), 2)) + posy;

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float x = posx - r; x <= posx + r; x += 0.3f) /*Третий цикл генерирует точки на нижней половине той же окружности, используя то же уравнение окружности,
            что и второй цикл, но с отрицательным знаком перед корнем из-за выбора нижней половины окружности.*/
        {
            float y = -std::sqrt(r * r - std::pow((x - posx), 2)) + posy;

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }


        float a = 300.f, b = 200.f;
        for (float x = -a; x <= a; x += 0.5f) /*Четвертый цикл генерирует точки на верхней половине эллипса, заданном уравнением(x ^ 2 / a ^ 2 + y ^ 2 / b ^ 2) = 1, где a = 300 и b = 200.
            Он перебирает значения x от -a до a с шагом 0.5 и использует уравнение эллипса, чтобы найти соответствующие значения y.*/
        {
            float y = std::sqrt(b * b * (1 - ((x * x) / (a * a))));

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float x = -a; x <= a; x += 0.5f)/* Пятый цикл генерирует точки на нижней половине эллипса, заданном уравнением (x^2/a^2 + y^2/b^2) = 1, где a = 300 и b = 200.
            Он перебирает значения x от -a до a с шагом 0.5 и использует уравнение эллипса, чтобы найти соответствующие значения y.*/
        {
            float y = -std::sqrt(b * b * (1 - ((x * x) / (a * a))));

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        /*Последние четыре цикла генерируют точки на прямоугольнике, заданном четырьмя линиями: x=-200, x=-50, y=-200 и y=-50.
        Каждый цикл перебирает значения x или y по одной стороне прямоугольника и фиксирует остальную координату на соответствующем краю.*/
        for (float x = -200.f; x <= -50.f; x += 1.f)
        {
            float y = -50.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float y = -50.f; y >= -200.f; y -= 1.f)
        {
            float x = -50.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float x = -50.f; x >= -200.f; x -= 1.f)
        {
            float y = -200.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float y = -200.f; y <= -50.f; y += 1.f)
        {
            float x = -200.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }
    }
    };





    int main() 
    { // создаётся окно, устанавливается длины рычагов, находится координаты центра окна и Создаётся окно с заданными размерами и названием
        unsigned int WIDTH = 800, HEIGHT = 800;
        float l1 = 150.f, l2 = 150.f;
        float x0 = WIDTH / 2, y0 = HEIGHT / 2;
        sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

        //Создаётся объект класса и устанавливается начало координат
        KinematicSolver solver(l1, l2);
        solver.SetOrigin(x0, y0);

        // Создаётся звенья манипулятора
        sf::RectangleShape joint1{ sf::Vector2f(l1, 4.f) };
        sf::RectangleShape joint2{ sf::Vector2f(l2, 4.f) };

        // Задаётся позиция для первого звена и цвет звеньев
        joint1.setPosition(x0, y0);
        joint1.setFillColor(sf::Color::Color(60, 60, 60));
        joint2.setFillColor(sf::Color::Color(60, 60, 60));

        // Создаётся ось Ox и задаются ее параметры
        sf::RectangleShape Ox{ sf::Vector2f(WIDTH, 1.f) };
        Ox.setPosition(0, y0);
        Ox.setFillColor(sf::Color::Black);

        // Создаётся ось Oy и задаются ее параметры
        sf::RectangleShape Oy{ sf::Vector2f(HEIGHT, 0.5f) };
        Oy.setPosition(x0, 0);
        Oy.rotate(90);
        Oy.setFillColor(sf::Color::Black);

        // Задаётся главная точка манипулятора, рисующая точка
        sf::CircleShape pmain{ 4.0f };
        pmain.setOrigin(2.0f, 2.0f);
        pmain.setFillColor(sf::Color::Green);

        // вектор для хранения массива точек манипулятора
        std::vector<Point> array;


        // генерируются точки для построения траектории 
        solver.Generate(array);

        unsigned int k = 0;
        bool ok = false; //  используется для определения корректности значений углов механизма в текущей точке
        bool pause = false; // использоуется для паузы в процессе воспроизведения траектории

        std::vector<sf::CircleShape> buffer; // отвечает за хранение отображаемых точек на экране 
        sf::CircleShape point(4.f); // задаётся объект класса, который будет использоваться для отображения каждой точки
        point.setOrigin(2.f, 2.f); // задаёт точке координаты центра.
        point.setFillColor(sf::Color::Blue); // задаётся цвет, которым будут рисоваться фигуры


        sf::Font font; //  создает объект класса, который будет использоваться для отображения текста на экране
        font.loadFromFile("font.ttf");


        sf::Text text; // создает объект класса, который будет использоваться для отображения текста на экране
        text.setFont(font); // устанавливает используемый шрифт для текста
        text.setCharacterSize(20); // устанавливает размер символов в пикселях
        text.setPosition(5.f, 5.f); // задает позицию текста на экране
        text.setFillColor(sf::Color::Black); //  задает цвет текста
        std::string str("Joints: "); // объявляет и инициализирует переменную str со значением "Joints: ".
        std::string final;
        str += std::to_string(l1) + " " + std::to_string(l2) + "\n"; /* добавляет к строке str значения l1 и l2 в виде строковых представлений,
        а также перенос строки*/



        float want_fps = 480; // используется для установки желаемой частоты кадров
        sf::Clock clock;

        /*Этот блок кода обрабатывает все события, произошедшие в окне приложения, такие как закрытие окна. 
        Если событие "закрытие окна" было получено, то программа закрывается.*/
        while (window.isOpen()) 
        {
            sf::Event event; 
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            /*В этом блоке кода получается координата точки pnt по её индексу k в массиве array. 
            Затем используется объект класса solver, чтобы вычислить углы ang для этой точки. 
            Если вычисление углов прошло успешно, то переменная ok устанавливается в true. Если же углы не были вычислены 
            (например, из-за того что робот не может достичь данной точки), то ok устанавливается в false*/
            auto pnt = array[k];
            Angle ang = solver.Solve(pnt.x, pnt.y);
            ok = true;


            if ((ang.a == -9999.f) && (ang.b == -9999.f)) ok = false;

            /*Этот блок кода отвечает за очистку окна и отрисовку всех элементов на экране. Сначала вызывается метод window.clear(), 
            чтобы очистить окно от предыдущих изображений. Затем на экран рисуются оси X и Y (Ox и Oy) и все элементы в списке buffer. 
            Если значение переменной ok равно true и программа не находится в режиме паузы, создаётся объект point, 
            который устанавливается на позицию pnt, после чего добавляется в список buffer*/
            window.clear(sf::Color::White);

            window.draw(Ox);
            window.draw(Oy);

            k++;

            for (const auto& elem : buffer) window.draw(elem);

            if (ok && !pause) 
            {
                point.setPosition(pnt.x, pnt.y);
                buffer.push_back(point);

                // Задаётся строка на экране с значением углов
                final = str +
                    "Alpha: " + std::to_string(std::abs(solver.toDegrees(ang.a))) + "\n" +
                    "Beta: " + std::to_string(std::abs(solver.toDegrees(ang.b)));
                text.setString(final);


                /*Происходит проверка, удовлетворяют ли значения переменных ang и pnt условиям. В зависимости от того, какое из условий выполнено,
                позиции и повороты элементов joint1 и joint2 обновляются соответствующим образом, используя тригонометрические функции */
                if (solver.checkAngles(ang, pnt))
                {
                    joint1.setRotation(solver.toDegrees(ang.a));

                    joint2.setPosition(x0 + l1 * std::cos(ang.a), y0 + l1 * std::sin(ang.a));
                    joint2.setRotation(solver.toDegrees(ang.a + ang.b));
                }
                else {
                    joint1.setRotation(solver.toDegrees(ang.a) + 180);

                    joint2.setPosition(x0 - l1 * std::cos(ang.a), y0 - l1 * std::sin(ang.a));
                    joint2.setRotation(solver.toDegrees(ang.a + ang.b) + 180);
                }

                pmain.setPosition(pnt.x, pnt.y);
            }
            /*Этот блок кода отвечает за рисование элементов робота на экране. Если значение углов было вычислено и приложение не находится 
            в режиме паузы, то программа отрисовывает все элементы робота на экране*/
            window.draw(joint1);
            window.draw(joint2);
            window.draw(pmain);
            window.draw(text);
            window.display();


            /*Вычисляется время, которое необходимо подождать перед отрисовкой следующего кадра (time_to_sleep). Если это значение положительное, 
            то программа засыпает на указанное количество миллисекунд, используя функцию sf::sleep.Предназначен для стабилизации частоты кадров 
            в приложении и предотвращения нагрузки на процессор.*/
            if (k >= array.size()) 
            {
                k = 0;
                pause = true;
            }


            sf::Int32 frame_duration = clock.getElapsedTime().asMilliseconds();
            sf::Int32 time_to_sleep = int(1000.f / want_fps) - frame_duration;
            if (time_to_sleep > 0) {
                sf::sleep(sf::milliseconds(time_to_sleep));
            }
            clock.restart();
        }

        return 0;
    }