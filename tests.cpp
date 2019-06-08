#include <gtest/gtest.h>

#include "Map.hpp"
#include "View.hpp"
#include "Actor.hpp"
#include "Raycaster.hpp"

using namespace RC;

struct map_test_parameters
{
    int width;
    int height;

    int x;
    int y;

    int value;
    int expected_value;
};

struct MapTest : testing::Test
{
    Map *map;

    MapTest()
    {
        map = new Map(10, 10);
    }

    ~MapTest()
    {
        delete map;
    }
};

struct MapSizeTest : MapTest, testing::WithParamInterface<map_test_parameters>
{
    MapSizeTest()
    {
        delete map;
        map = new Map(GetParam().width, GetParam().width);
    }
};

TEST_P(MapSizeTest, TEST_MAPY)
{
    auto params = GetParam();
    map->set(params.x, params.y, params.value);
    EXPECT_EQ(map->get(params.x, params.y), params.expected_value);
    EXPECT_EQ(1, 1);
}

INSTANTIATE_TEST_CASE_P(MAP_SET_GET, MapSizeTest,
                        testing::Values(
                            map_test_parameters{100, 200, 50, 12, 4, 4},/*przypadek testowy - punkt znajduje na macierzy, funkcja zwraca ustaloną wartość */
                            map_test_parameters{100, 200, 300, 100, 4, -1}/*punkt znajduje się poza macierzą, funkcja zwraca wartość -1*/));

struct actor_test_parameters
{
    int map_width;
    int map_height;

    double x;
    double y;
    int view_angle;
    double movement_speed;
    double heading;

    direction dir;

    double expected_x;
    double expected_y;

    friend std::ostream& operator<<(std::ostream& os, const actor_test_parameters& obj){
        return os
            << std::endl
            << "wysokość mapy: " << obj.map_height << std::endl
            << "szerokość mapy: " << obj.map_width << std::endl
            << "położenie X: " << obj.x << std::endl
            << "położenie Y: " << obj.y << std::endl            
            << "kąt widzenia: " << obj.view_angle << std::endl
            << "szybkość poruszania: " << obj.movement_speed << std::endl
            << "kierunek kamery: " << obj.heading << std::endl
            << "kierunek ruchu: " << obj.dir << std::endl
            << "oczekiwane położenie X: " << obj.expected_x << std::endl
            << "oczekiwane położenie Y: " << obj.expected_y;
    }
};

struct ActorTest : testing::Test
{
    Actor* actor;
    Map* map;

    ActorTest(){
        map = new Map(100, 100);
        actor = new Actor(10, 10, 10, 10, 0, &*map);
    }

    ~ActorTest(){
        delete map;
        delete actor;
    }

};

struct ActorMovementTest : ActorTest, testing::WithParamInterface<actor_test_parameters>
{
    ActorMovementTest(){
        auto params = GetParam();
        delete map;
        map = new Map(params.map_width, params.map_height);
        delete actor;
        actor = new Actor(params.x, params.y, params.view_angle, params.movement_speed, params.heading, &*map);
    }
};

struct ActorRotationTest : ActorTest, testing::WithParamInterface<actor_test_parameters>
{
};

TEST_P(ActorMovementTest, TEST_PORUSZANIA){
    point_t position{actor->m_x, actor->m_y};
    actor->move(GetParam().dir);

    EXPECT_TRUE(actor->m_x == GetParam().expected_x || actor->m_y ==  GetParam().expected_x);
}


TEST_P(ActorRotationTest, TEST_OBRACANIA){
    double heading = actor->get_heading();
    if(GetParam().dir == LEFT || GetParam().dir == RIGHT)
        actor->rotate(GetParam().dir);

    EXPECT_TRUE(heading != actor->get_heading() && actor->get_heading() >= 0 && actor->get_heading() <= 360);
}

INSTANTIATE_TEST_CASE_P(ACTOR_MOVE, ActorMovementTest,
                        testing::Values(
                            actor_test_parameters{100, 100, 10, 10, 90, 1, 0, UP, 10, 9},/*przypadki testowe ruch w różnych kierunkach*/
                            actor_test_parameters{100, 100, 10, 10, 90, 1, 0, DOWN, 10, 11},
                            actor_test_parameters{100, 100, 10, 10, 90, 1, 0, LEFT, 9, 10},
                            actor_test_parameters{100, 100, 10, 10, 90, 1, 0, RIGHT, 10, 11},
                            actor_test_parameters{100, 100, 100, 100, 90, 1, 0, RIGHT, 100, 100}/*przypadek testowy - aktor poza mapą, brak zmiany położenia*/));

INSTANTIATE_TEST_CASE_P(ACTOR_ROTATE, ActorMovementTest,
                        testing::Values(
                           actor_test_parameters{100, 100, 10, 10, 90, 1, 0, LEFT, 10, 10},
                           actor_test_parameters{100, 100, 10, 10, 90, 1, 0, RIGHT, 10, 10}));

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}