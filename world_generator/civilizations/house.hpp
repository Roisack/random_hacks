#ifndef __HOUSE_HPP_
#define __HOUSE_HPP_

// This class defines a house, such as House Atreides or Lannister
// It does NOT define Empire State Building or White House

#include <utility>
#include <string>
#include <memory>
#include <vector>

class Creature;
class HistoricalEvent;

class House
{
private:
    std::string name;   // Harkonnen, Lannister, Layland Lashers...
    std::string type;   // A family, clan, group of bandits...
    std::shared_ptr<Creature> head; // The leader of this house
    std::vector<std::pair<std::shared_ptr<Creature>, std::string> > currentMembers; // member, position
    std::vector<std::pair<std::shared_ptr<Creature>, std::string> > pastMembers;    // member, position at the time of death
    std::vector<std::shared_ptr<HistoricalEvent> > history;
public:
    House();
    ~House();

    std::shared_ptr<Creature> getHead();
    std::vector<std::pair<std::shared_ptr<Creature>, std::string> > getMembers();
    std::vector<std::pair<std::shared_ptr<Creature>, std::string> > getPastMembers();
    std::vector<std::shared_ptr<HistoricalEvent> > getHistory();
};

#endif
