#include "room.cpp"
class PrincessRoom : public Room
{
public:
    PrincessRoom()
    {
        type = PRINCESS;
    }
    ~PrincessRoom() = default;
    void printInfo() final
    {
        std::cout << "congratulations! princess has been found!\nnow you can leave with her via the lobby!\n";
        Room::printExits();
    }
};