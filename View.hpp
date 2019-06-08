/*
    Wyświetlanie i odczytywanie interakcji z użytkownikiem
*/
#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

namespace RC
{

#ifndef POINT
#define POINT
struct point_t
{
    double x;
    double y;
};
#endif

class View
{
public:
    sf::RenderWindow window{sf::VideoMode(100, 100), "my window"};

    View(int width, int height);

    bool isOpen();

    void checkEvents(std::list<int> *keys, std::list<point_t> *points);/*zapisywanie zdarzeń z klawiaturą i myszką i przetwarzanie związanych z oknem*/

    void clear();

    void paint_line(double x1, double y1, double x2, double y2, int color);/*rysowanie odcinka o podanym początku i końcu oraz id koloru*/

    void paint_pixel(double x, double y, int color_index);/*kolorowanie pojedynczego punktu na podany kolor*/

    void display();

    void add_color(double r, double g, double b);/*dodawanie koloru do listy*/

    std::vector<sf::Color> getColors();

    int get_width();

    int get_height();

private:
    int m_window_width{800};
    int m_window_height{600};
    std::vector<sf::Color> m_colors;
};

} 

#endif