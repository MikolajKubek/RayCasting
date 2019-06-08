#include "Raycaster.hpp"
#include <iostream>
using namespace RC;

Raycaster::Raycaster() {}

void Raycaster::generate_rays(Actor *actor, Map *map, View *view)
{
    double angle = actor->get_heading() - actor->get_angle() / 2;/*początkowy kąt promienia pola widzenia*/
    double c = cos(angle * M_PI / 180);
    double s = sin(angle * M_PI / 180);
    for (double i = 0; i < SCREEN_WIDTH; i += SCREEN_WIDTH / (double)view->get_width())/*kolejne kolumny pikseli*/
    {
        bool collision = false;
        for (double j = 1.0; j < m_ray_length && !collision; j += RAY_ACCURACY)/*dopóki promień nie napotka przeszkody/nie skończy się*/
        {
            /*kolejne pole na mapie przez które przechodzi promień*/
            int x = actor->m_x + j * c;
            int y = actor->m_y + j * s;

            /*jeżeli promień napotkał przeszkodę lub krawędź mapy - generowanie pionowego odcinka*/
            if (x < 0 || x >= map->getWidth() || y < 0 || y >= map->getHeight() || map->get(x, y) != 0)
            {
                double height = SCREEN_HEIGHT / (j * cos((actor->get_heading() - angle) * M_PI / 180));/*wysokość generowanej linii największa dla najmniejszej odległości od aktora*/
                if (height > SCREEN_HEIGHT)
                {
                    height = SCREEN_HEIGHT;
                }
                else if (height < 0)
                {
                    height = 0;
                }
                view->paint_line(i, (SCREEN_HEIGHT - height) / 2, i, (SCREEN_HEIGHT + height) / 2, map->get(x, y));/*rysowanie linii tak, aby jej środek pokrywał się ze środkiem wysokości okna*/
                collision = true;
            }
        }
        angle += actor->get_angle() / (double)view->get_width();
        c = cos(angle * M_PI / 180);
        s = sin(angle * M_PI / 180);
    }
}