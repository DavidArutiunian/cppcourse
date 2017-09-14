#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    float offset = 20;

    float circleRadius = 80;

    float width = (2 * circleRadius + 2 * offset);
    float height = (6 * circleRadius + 4 * offset);

    sf::RectangleShape backgroundRect;
    sf::CircleShape greenCircle(circleRadius);
    sf::CircleShape yellowCircle(circleRadius);
    sf::CircleShape redCircle(circleRadius);

    backgroundRect.setPosition({0, 0});
    backgroundRect.setSize({width, height});
    backgroundRect.setFillColor(sf::Color(0x67, 0x67, 0x67));

    greenCircle.setPosition({offset, offset});
    greenCircle.setFillColor(sf::Color(0, 0xE1, 0xF));

    yellowCircle.setPosition({offset, 2 * offset + 2 * circleRadius});
    yellowCircle.setFillColor(sf::Color(0xFF, 0xCC, 0x26));

    redCircle.setPosition({offset, 3 * offset + 4 * circleRadius});
    redCircle.setFillColor(sf::Color(0xF2, 0, 0));

    sf::RenderWindow window(sf::VideoMode({(unsigned int)width, (unsigned int)height}), "Traffic Light");
    window.clear();

    window.draw(backgroundRect);
    window.draw(greenCircle);
    window.draw(yellowCircle);
    window.draw(redCircle);

    window.display();

    sf::sleep(sf::seconds(5));
}