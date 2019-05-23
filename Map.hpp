/*
    Rzut z góry, zawierający informacje o obiektach 
*/
#ifndef MAP_H
#define MAP_H

#include <list>

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

class Map
{
public:
    Map(int width, int height);

    int get(int x, int y);

    void set(int x, int y, int value);

    void processEvents(std::list<point_t> *points);

    void clear();

    int getWidth();

    int getHeight();

private:
    int m_width;
    int m_height;
    int **m_map;
};
} // namespace RC

#endif