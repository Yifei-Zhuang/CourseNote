#include "room.cpp"
class LobbyRoom : public Room
{
public:
    LobbyRoom()
    {
        type = LOBBY;
    }
    ~LobbyRoom() = default;
    void printInfo() final
    {
        std::cout << "here is the Lobby, you can start your adventure here\n";
        printExits();
    }
};