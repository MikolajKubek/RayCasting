/*
    Obiekt na mapie, posiadający możliwość poruszania się
*/
#ifndef ACTOR_H
#define ACTOR_H

#include <math.h>
#include <list>
#include "Map.hpp"

namespace RC
{

enum direction
{
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

class Actor
{
public:
    double m_x{0};/*pozycja na mapie X*/
    double m_y{0};/*pozycja na mapie Y*/

    Actor(double x, double y, int view_angle, double movement_speed, double heading, Map *map);

    void move(direction direction);/*zmiana połozenia na mapie*/

    void rotate(direction dir);/*zmiana kierunku kamery*/

    void processEvents(std::list<int> *keys);/*przetwarzanie interakcji z klawiaturą na odpowiednie akcje*/

    int get_angle();/*zwraca pole widzenia*/

    double get_heading();

private:
    int m_view_angle{90};/*pole widzenia*/
    double m_heading{0};/*kierunek w który zwrócona jest kamera*/
    double m_rotation_speed{1};
    double m_movement_speed{1};
    Map *m_map;
};

}

#endif