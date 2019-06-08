#ifndef RAYCASTING_H
#define RAYCASTING_H
#include <math.h>

#include "Actor.hpp"
#include "Map.hpp"
#include "View.hpp"

/*sfml wymaga odwołania się do wymiarów okna w procentach*/
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100

#define RAY_ACCURACY 0.03 /*wielkość o jaką wydłuża się pole widzenia w każdym kroku*/
namespace RC
{
class Raycaster
{
public:
    Raycaster();

    void generate_rays(Actor *actor, Map *map, View *view);/*funkcja obliczająca odległość od kamery do najbliższej przeszkody i generująca odpowiedniej długości linię na ekranie*/

private:
    int m_ray_length{50};/*maksymalna długość generowanych promieni - zasięg widzenia*/
};
} 
#endif