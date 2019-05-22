#ifndef ACTOR_H
#define ACTOR_H

#include  <math.h>
#include <list>
#include "Map.hpp"

namespace RC{

    enum direction{
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    #ifndef POINT
    #define POINT    
    struct point_t
    {
        double x;
        double y;
    };
    #endif

    class Actor{
    public:
        int m_x {0};
        int m_y {0};

        Actor(int x, int y, int view_angle, double heading, Map map);

        void move(direction direction);

        void rotate(direction dir);
        
        void processEvents(std::list<int>* keys);

        point_t get_position();

        int get_x();

        int get_y();
        
        int get_angle();

        double get_heading();

    private:
        int m_view_angle {90};
        double m_heading {0};    
        double m_rotation_speed {1};
        Map m_map;
    };

}

#endif