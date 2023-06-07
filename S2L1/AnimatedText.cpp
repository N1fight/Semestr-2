#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>

class AnimatedText {
private:
    std::string text;
    double duration;
    double char_duration;
    std::queue<std::string> arr;
    void set() {
        for (unsigned int i = 1; i <= text.length(); i++) {
            arr.push(text.substr(0, i));
        }
    }


public:
    AnimatedText(std::string text, double duration) : text(text), duration(duration) {
        set();
        char_duration = (1000 * duration) / text.length();
    }

    std::string get() {
        if (arr.empty()) {
            set();
            return "";
        }
        std::string out = arr.front();
        arr.pop();
        return out;
    }

    double getCharDuration() {
        return char_duration;
    }

};


int main() {
    unsigned int WIDTH = 500, HEIGHT = 500;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

    AnimatedText atext("Hello, World!", 4);
    double char_duration = atext.getCharDuration();
    std::string disp = atext.get();


    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text text(disp, font, 40);
    text.setFillColor(sf::Color::White);
    text.setPosition(20.f, 20.f);

    float want_fps = 60;
    sf::Clock clock;
    sf::Clock clock1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        //Text
        if (clock1.getElapsedTime().asMilliseconds() >= char_duration) {
            clock1.restart();
            text.setString(atext.get());
        }


        window.draw(text);
        window.display();
        /*

        int frame_duration = clock.getElapsedTime().asMilliseconds();
        int time_to_sleep = int(1000.f / want_fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        clock.restart();
        */
    }

    return 0;
}