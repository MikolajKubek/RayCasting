#include "View.hpp"

using namespace RC;
View::View(int width, int height)
    : m_window_width(width), m_window_height(height)
{
    window.setTitle(sf::String("ray casting"));
    window.setSize(sf::Vector2u(width, height));
}

bool View::isOpen()
{
    return window.isOpen();
}

void View::checkEvents(std::list<int> *keys, std::list<point_t> *points)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            else
            {
                keys->push_back(event.key.code);
            }
            break;

        case sf::Event::MouseButtonPressed:
            point_t clicked;
            clicked.x = event.mouseButton.x;
            clicked.y = event.mouseButton.y;
            points->push_back(clicked);
            break;

        default:
            break;
        }
    }
}

void View::clear()
{
    window.clear(sf::Color(0, 150, 0, 255));
    sf::VertexArray up(sf::Quads, 4);
    up[0].position = sf::Vector2f(0.0, 50.0);
    up[0].color = sf::Color(0, 80, 150, 255);
    up[1].position = sf::Vector2f(100.0, 50.0);
    up[1].color = sf::Color(0, 80, 150, 255);
    up[2].position = sf::Vector2f(100.0, 0.0);
    up[2].color = sf::Color(0, 80, 150, 255);
    up[3].position = sf::Vector2f(0.0, 0.0);
    up[3].color = sf::Color(0, 80, 150, 255);

    window.draw(up);

}

void View::paint_line(double x1, double y1, double x2, double y2)
{
    double color = (y2 - y1) / 100;

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(x1, y1);
    line[0].color = sf::Color(color * 250, color * 10, color * 100, 255);
    line[1].position = sf::Vector2f(x2, y2);
    line[1].color = sf::Color(color * 250, color * 10, color * 100, 255);

    window.draw(line);
}

void View::display()
{
    window.display();
}

int View::get_width()
{
    return m_window_width;
}

int View::get_height()
{
    return m_window_height;
}