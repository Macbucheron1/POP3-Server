#ifndef REQUESTNOOP_H
#define REQUESTNOOP_H

#include "Request.h"

class RequestNoop : public Request {
public:
    RequestNoop();
    RequestNoop(std::istream& stream);
    void accept(Server& server) override;
};

#endif