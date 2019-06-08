#include "Map.hpp"
#include <iostream>
using namespace RC;

Map::Map(int width, int height)
    : m_width(width), m_height(height)
{
    m_map = new int *[width]; 

    for (int i = 0; i < width; i++)
    {
        m_map[i] = new int[height];
    }
}

Map::~Map()
{
    for (int i = 0; i < m_width; i++)
    {
        delete[] m_map[i];
    }
    delete[] m_map;
}

int Map::get(int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return m_map[x][y];
    }

    return -1;
}

void Map::set(int x, int y, int value)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        m_map[x][y] = value;
    }
}

void Map::processEvents(std::list<point_t> *points)
{
    point_t point;
    while (points->size() > 0)
    {
        point = points->front();
        points->pop_front();
    }
}

int Map::getWidth()
{
    return m_width;
}

int Map::getHeight()
{
    return m_height;
}
