#ifndef __RoomCPP__
#define __RoomCPP__
#include "room.hpp"
Room::Room()
{
    isIn.resize(6);
    for (int i = 0; i < 6; i++)
    {
        if (rand() % 2 == 0)
        {
            isIn[i] = 1;
            AddNeighbor(exitNames[i], nullptr);
        }
    }
}
Room::Room(std::string name) : Room()
{
    this->name = name;
    ++count;
    type = NOTHING;
};

Room *Room::MOVE(std::string input)
{
    if (neighbors.find(input) == neighbors.end())
    {
        return nullptr;
    }
    return (neighbors)[input];
}
void Room::printInfo()
{
    std::cout << "Welcome to the " << name << "\n";
    printExits();
}
void Room::printExits()
{
    std::cout << "There are " << getExitNumber() << " exits :";
    std::for_each(neighbors.begin(), neighbors.end(), [&](auto it) -> void
                  { std::cout << it.first << " "; });
    puts("");
    std::cout << "Enter your command: ";
}
int Room::getExitNumber()
{
    return neighbors.size();
}
TYPE Room::getTYPE()
{
    return type;
}
void Room::AddNeighbor(std::string direction, Room *room)
{
    (neighbors)[direction] = room;
}
size_t Room::howManyRooms()
{
    return count;
}
#endif