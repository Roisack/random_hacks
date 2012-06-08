#include "historicalEvent.hpp"

HistoricalEvent::HistoricalEvent(long d, std::vector<std::string> msg)
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

long HistoricalEvent::getDate()
{
    return date;
}
