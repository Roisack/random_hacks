#ifndef __CIVILIZATION_HPP_
#define __CIVILIZATION_HPP_

class Creature;
class House;
class HistoricalEvent;

#include <memory>
#include <vector>

class Civilization
{
private:
    std::shared_ptr<House> leader;
    std::vector<std::shared_ptr<Creature> > races;
    std::vector<std::shared_ptr<HistoricalEvent> > history;
public:
    Civilization();
    ~Civilization();
};

#endif
