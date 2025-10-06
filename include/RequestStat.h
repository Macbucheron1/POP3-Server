#ifndef REQUESTSTAT_H
#define REQUESTSTAT_H

#include "Request.h"

class RequestStat : public Request {
public:
    RequestStat();
    RequestStat(std::istream& stream);
    void accept(Server& server) override;
};

#endif