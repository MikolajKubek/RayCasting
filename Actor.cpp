#include "Actor.hpp"

using namespace RC;

Actor::Actor(double x, double y, int view_angle, double heading, Map *map)
    : m_x(x), m_y(y), m_view_angle(view_angle), m_heading(heading), m_map(map) {}

void Actor::move(direction direction)
{
    double step_lengh = 0.5;
    double x = m_x;
    double y = m_y;
    switch (direction)
    {
    case UP:
            x = m_x + step_lengh * cos(m_heading * M_PI / 180);
            y = m_y + step_lengh * sin(m_heading * M_PI / 180);
        break;

    case DOWN:
            x = m_x + step_lengh * cos((m_heading + 180) * M_PI / 180);
            y = m_y + step_lengh * sin((m_heading + 180) * M_PI / 180);   
        break;

    case LEFT:
            x = m_x + step_lengh * cos((m_heading - 90) * M_PI / 180);
            y = m_y + step_lengh * sin((m_heading - 90) * M_PI / 180);
        break;

    case RIGHT:
            x = m_x + step_lengh * cos((m_heading + 90) * M_PI / 180);
            y = m_y + step_lengh * sin((m_heading + 90) * M_PI / 180);
        break;

    default:
        break;
    }

    if (x < m_map->getWidth() && y < m_map->getHeight() && m_map->get((int)x, (int)y) == 0)
    {
        m_x = x;
        m_y = y;
    }
}

void Actor::rotate(direction dir)
{
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

void Actor::processEvents(std::list<int> *keys)
{
    while (keys->size() > 0)
    {
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

int Actor::get_angle()
{
    return m_view_angle;
}

double Actor::get_heading()
{
    return m_heading;
}