#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <list>

namespace RC{

    #ifndef POINT
    #define POINT    
    struct point_t
    {
        double x;
        double y;
    };
    #endif

    class View{
        public:
            sf::RenderWindow window {sf::VideoMode(100, 100), "my window"};

            View(int width, int height);

            bool isOpen();

            void checkEvents(std::list<int>* keys, std::list<point_t>* points);

            void clear();

            void paint_line(double x1, double y1, double x2, double y2);

            void display();

            int get_width();
            
            int get_height();
        private:
        int m_window_width {800};
        int m_window_height {600};
    };
}

#endif