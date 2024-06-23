#ifndef __roomHPP__
#define __roomHPP__
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
enum TYPE
{
    NOTHING,
    LOBBY,
    PRINCESS,
    MONSTER
};
std::string exitNames[] = {"up", "down", "south", "north", "east", "west"};
class Room
{
public:
    Room();
    Room(std::string name);
    virtual ~Room() = default;
    Room *MOVE(std::string input);
    virtual void printInfo();
    void printExits();
    inline int getExitNumber();
    inline TYPE getTYPE();
    inline void AddNeighbor(std::string direction, Room *room);
    static inline size_t howManyRooms();

protected:
    std::string name;
    std::vector<int> isIn;
    std::unordered_map<std::string, Room *> neighbors;
    TYPE type;

private:
    static size_t count;
};

size_t Room::count = 0;
#endif