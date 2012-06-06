#ifndef __HISTORICALEVENT_HPP_
#define __HISTORICALEVENT_HPP_

#include <string>
#include <vector>

class HistoricalEvent
{
private:
    float date;
    std::vector<std::string> messages;
public:
    HistoricalEvent(float d, std::vector<std::string> msg);
    ~HistoricalEvent();

    std::vector<std::string> getMessages();
    float getDate();
};

#endif
