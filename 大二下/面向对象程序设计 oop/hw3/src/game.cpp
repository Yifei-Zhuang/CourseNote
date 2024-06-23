#ifndef __GAME__
#define __GAME__
#include <random>

#include <map>
#include "room.hpp"
#include "MonsterRoom.cpp"
#include "PrincessRoom.cpp"
#include "LobbyRoom.cpp"

class Game
{

public:
    Game()
    {
        srand(time(NULL));
        lobby = new LobbyRoom();
    }
    ~Game()
    {
        delete lobby;
        std::for_each(
            rooms.begin(), rooms.end(), [](auto it) -> void
            { delete it; });
    }
    inline static int GetSplitRoomName(int index)
    {
        if (index >= 8 || index < 0)
        {
            return -1;
        }
        return 1 ^ index;
    }
    void play()
    {
        Room *curRoom = lobby;
        curRoom->printInfo();
        while (true)
        {
            std::string prefix, direction;
            if (std::cin.peek() == '\n')
                getchar();
            std::cin >> prefix;
            if (prefix != "go")
            {
                std::cout << "usage: go directionName\n";
                continue;
            }
            std::cin >> direction;
            if (directionNamesMap.find(direction) == directionNamesMap.end())
            {
                std::cout << "invalid direction\n";
                curRoom->printInfo();
                continue;
            }
            auto newPos = curRoom->MOVE(direction);

            if (newPos == nullptr)
            {
                int temp = rand() % 15;
                // std::cout << "random" << temp << std::endl;
                if (temp == 9)
                {
                    newPos = new MonsterRoom();
                }
                else if ((temp == 6 || temp == 7 || temp == 8) && !hasFound)
                {
                    newPos = new PrincessRoom();
                }
                else
                {
                    newPos = new Room("room " + std::to_string(Room::howManyRooms()) + ":");
                }
                //创建新room
                rooms.push_back(newPos);
                curRoom->AddNeighbor(direction, newPos);
                newPos->AddNeighbor(directionNames[GetSplitRoomName(directionNamesMap[direction])], curRoom);
            }
            curRoom = newPos;
            curRoom->printInfo();
            if (curRoom->getTYPE() == MONSTER)
            {
                exit(0);
            }
            if (curRoom->getTYPE() == PRINCESS)
            {
                hasFound = true;
            }
            if (hasFound && curRoom == lobby)
            {
                std::cout << "\ncongratulations! you have win this game!\n";
                return;
            }
        }
    }

private:
    inline static std::map<std::string, int> directionNamesMap = {
        std::make_pair<std::string, int>("up", 0),
        std::make_pair<std::string, int>("down", 1),
        std::make_pair<std::string, int>("south", 2),
        std::make_pair<std::string, int>("north", 3),
        std::make_pair<std::string, int>("east", 4),
        std::make_pair<std::string, int>("west", 5)};
    inline static std::string directionNames[] = {"up", "down", "south", "north", "east", "west"};
    Room *lobby;
    std::vector<Room *> rooms;
    bool hasFound = false;
};
#endif