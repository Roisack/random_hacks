#include "historicalEvent.hpp"

HistoricalEvent::HistoricalEvent(float d, std::vector<std::string> msg)
{
    std::vector<std::string>::iterator iter;
    for (iter = msg.begin(); iter != msg.end(); iter++)
        messages.push_back(*iter);
    date = d;
}

HistoricalEvent::~HistoricalEvent()
{
}

std::vector<std::string> HistoricalEvent::getMessages()
{
    return messages;
}

float HistoricalEvent::getDate()
{
    return date;
}
