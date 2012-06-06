#include "house.hpp"

House::House()
{
}

House::~House()
{
}

std::shared_ptr<Creature> House::getHead()
{
    return head;
}

std::vector<std::pair<std::shared_ptr<Creature>, std::string> > House::getMembers()
{
    return currentMembers;
}

std::vector<std::pair<std::shared_ptr<Creature>, std::string> > House::getPastMembers()
{
    return pastMembers;
}

std::vector<std::shared_ptr<HistoricalEvent> > House::getHistory()
{
    return history;
}
