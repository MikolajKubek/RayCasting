#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

#include <list>

#include "Map.hpp"
#include "View.hpp"
#include "Actor.hpp"
#include "Raycaster.hpp"

#define MAP_WIDTH 2000
#define MAP_HEIGHT 2000
#define ACTOR_X 10
#define ACTOR_Y 10
#define VIEW_ANGLE 90
#define MOVEMENT_SPEED 0.2
#define HEADING 0
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

using namespace RC;

int main()
{
    /*inicjowanie obiektów*/
    Map map(MAP_WIDTH, MAP_HEIGHT);
    Actor actor(ACTOR_X, ACTOR_Y, VIEW_ANGLE, MOVEMENT_SPEED, HEADING, &map);
    View view(WINDOW_WIDTH, WINDOW_HEIGHT);
    Raycaster rc;

    /*kolory dla kolejnych wartości reprezentowanych na mapie*/
    view.add_color(255, 0, 0);
    view.add_color(0, 255, 0);
    view.add_color(0, 0, 255);
    view.add_color(255, 255, 0);
    view.add_color(255, 0, 255);

    /*wypełnienie mapy losowymi obiektami*/
    for (int i = 0; i < map.getWidth(); i++)
    {
        for (int j = 0; j < map.getHeight(); j++)
        {
            if(rand()%20 == 0){
                map.set(i, j, rand()%(view.getColors().size()+1));
            }
        }
    }

    /*listy służące do przekazywania zdarzeń do odpowiednich klas*/
    std::list<int> keys;
    std::list<point_t> clicked_points;

    bool start = false;/*generowanie pierwszej klatki nie wymaga zdarzenia*/
    while (view.isOpen())
    {
        
        view.checkEvents(&keys, &clicked_points);
        /*jeżeli wystąpiło zdarzenie związane z klawiaturą - wykonaj odpowiednią akcję i wygeneruj obraz*/
        if (keys.size() > 0 || !start)
        {
            actor.processEvents(&keys);
            map.processEvents(&clicked_points);

            view.clear();
            rc.generate_rays(&actor, &map, &view);
            start = true;
        }
        view.display();
    }
    
    return 0;
}
