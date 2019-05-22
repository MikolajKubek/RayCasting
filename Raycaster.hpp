#include <math.h>

#include "Actor.hpp"
#include "Map.hpp"
#include "View.hpp"

namespace RC{
    class Raycaster{
        public:
            Raycaster();

            void generate_rays(Actor* actor, Map* map, View* view);
            
        private:
            int m_ray_length {50};
    };
}