#include "View.hpp"
#include <iostream>
using namespace RC;
View::View(int width, int height)
    : m_window_width(width), m_window_height(height)
{
    window.setTitle(sf::String("ray casting"));
    window.setSize(sf::Vector2u(width, height));
    m_colors = {};
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        keys->push_back(sf::Keyboard::Up);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        keys->push_back(sf::Keyboard::Down);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        keys->push_back(sf::Keyboard::Left);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        keys->push_back(sf::Keyboard::Right);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        keys->push_back(sf::Keyboard::A);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        keys->push_back(sf::Keyboard::D);
    }

}

void View::clear()
{   
     window.clear(sf::Color::Black);
}
void View::paint_line(double x1, double y1, double x2, double y2, int color_index)
{
    double dist = y2 - y1;
    double mul = 1;

    if(dist < 10){
        mul = 0.5;
    }
    else{
        mul = dist/100 + 0.5;
    }

    mul > 1 ? mul = 1 : true;

    sf::Color color;
    if(color_index > m_colors.size()){
        color = sf::Color(0, 0, 0, 0);
    }
    else if(color_index == -1){
        color = sf::Color(255, 255, 255, 0);
    }
    else{
        color = m_colors[color_index - 1];
    }

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(x1, y1);
    line[0].color = sf::Color(color.r*mul, color.g*mul, color.b*mul, 255);
    line[1].position = sf::Vector2f(x2, y2);
    line[1].color = sf::Color(color.r*mul, color.g*mul, color.b*mul, 255);

    window.draw(line);
}

void View::paint_pixel(double x, double y, int color_index){
    sf::Color color;
    if(color_index > m_colors.size()){
        color = sf::Color(0, 0, 0, 0);
    }
    else{
        color = m_colors[color_index - 1];
    }

    sf::VertexArray point(sf::Points, 1);
    point[0].position = sf::Vector2f(x, y);
    point[0].color = color;

    window.draw(point);
}


void View::display()
{
    window.display();
}

void View::add_color(double r, double g, double b){
    m_colors.push_back(sf::Color(r, g, b, 255));
}

std::vector<sf::Color> View::getColors(){
    return m_colors;
}


int View::get_width()
{
    return m_window_width;
}

int View::get_height()
{
    return m_window_height;
}