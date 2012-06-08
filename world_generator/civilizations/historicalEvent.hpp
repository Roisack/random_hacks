#ifndef __HISTORICALEVENT_HPP_
#define __HISTORICALEVENT_HPP_

#include <string>
#include <vector>

class HistoricalEvent
{
private:
    long date;
    std::vector<std::string> messages;
public:
    HistoricalEvent(long d, std::vector<std::string> msg);
    ~HistoricalEvent();

    std::vector<std::string> getMessages();
    long getDate();
};

#endif
