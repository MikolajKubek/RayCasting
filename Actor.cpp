#include "Actor.hpp"


using namespace RC;

Actor::Actor(int x, int y, int view_angle, double heading)
    : m_x(x), m_y(y),  m_view_angle(view_angle), m_heading(heading){}

void Actor::move(direction direction){
    switch (direction)
    {
    case UP:
        m_y--;
        break;

    case DOWN:
        m_y++;
        break;
    
    case LEFT:
        m_x--;
        break;

    case RIGHT:
        m_x++;
        break;
    
    default:
        break;
    }
}

void Actor::rotate(direction dir){
    switch (dir)
    {
        case LEFT:
            m_heading >= 0 ? m_heading -= m_rotation_speed : m_heading = 360 - m_rotation_speed;
            break;
        
        case RIGHT:
            m_heading <= 360 ? m_heading += m_rotation_speed : m_heading = 0 + m_rotation_speed;
            break;
    }
}

void Actor::processEvents(std::list<int>* keys){
    while(keys->size() > 0){
        switch (keys->front())
        {
        case 0:
            rotate(LEFT);
            break;
        
        case 3:
            rotate(RIGHT);
            break;

        case 71:
            move(LEFT);
            break;
        case 72:
            move(RIGHT);
            break;

        case 73:
            move(UP);
            break;

        case 74:
            move(DOWN);
            break;

        default:
            break;
        }
        keys->pop_front();
    }
}

point_t Actor::get_position(){
    point_t point;
    
    point.x = m_x;
    point.y = m_y;

    return point;
}

int Actor::get_angle(){
    return m_view_angle;
}

double Actor::get_heading(){
    return m_heading;
}