#include "room.cpp"
class MonsterRoom : public Room
{
public:
    MonsterRoom()
    {
        type = MONSTER;
    }
    void printInfo() final
    {
        std::cout << "you encouter monster, game over!" << std::endl;
    }
    ~MonsterRoom() = default;
};