#ifndef ACTOR_H
#define ACTOR_H

#include <list>

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
        Actor(int x, int y, int view_angle, double heading);

        void move(direction direction);

        void rotate(direction dir);
        
        void processEvents(std::list<int>* keys);

        point_t get_position();
        
        int get_angle();

        double get_heading();

    private:
        int m_x {0};
        int m_y {0};
        int m_view_angle {90};
        double m_heading {0};    
        double m_rotation_speed {10};
    };

}

#endif