#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

#include <list>

#include "Map.hpp"
#include "View.hpp"
#include "Actor.hpp"
#include "Raycaster.hpp"

using namespace RC;

int main()
{
    Map map(800, 800);
    Actor actor(10, 10, 90, 0, &map);
    View view(800, 800);
    Raycaster rc;

    for (int i = 0; i < map.getWidth(); i++)
    {
        for (int j = 0; j < map.getHeight(); j++)
        {
            map.set(i, j, (rand() % 50 == 0));
        }
    }

    std::list<int> keys;
    std::list<point_t> clicked_points;

    view.clear();
    rc.generate_rays(&actor, &map, &view);

    while (view.isOpen())
    {

        view.checkEvents(&keys, &clicked_points);
        
        if (keys.size() > 0)
        {
            actor.processEvents(&keys);
            map.processEvents(&clicked_points);

            view.clear();
            rc.generate_rays(&actor, &map, &view);
        }
        view.display();
    }

    return 0;
}