#include "Raycaster.hpp"

using namespace RC;

Raycaster::Raycaster() {}

void Raycaster::generate_rays(Actor *actor, Map *map, View *view)
{
    double angle = actor->get_heading() - actor->get_angle() / 2;
    bool collision = false;
    for (double i = 0; i < 100; i += 100.0 / view->get_width())
    {
        bool collision = false;
        for (double j = 1.0; j < m_ray_length && !collision; j += 0.01)
        {
            double x = actor->m_x + j * cos(angle * M_PI / 180);
            double y = actor->m_y + j * sin(angle * M_PI / 180);

            if (x < 0 || x >= view->get_width() || y < 0 || x >= view->get_height() || map->get((int)x, (int)y))
            {
                double height = 100 / (j * cos((actor->get_heading() - angle) * M_PI / 180));
                if (height > 100)
                {
                    height = 100;
                }
                else if (height < 0)
                {
                    height = 0;
                }
                view->paint_line(i, (100 - height) / 2, i, (100 + height) / 2);
                collision = true;
            }
        }
        angle += actor->get_angle() / (double)view->get_width();
    }
}