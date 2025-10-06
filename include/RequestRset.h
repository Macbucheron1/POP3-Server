#ifndef REQUESTRSET_H
#define REQUESTRSET_H

#include "Request.h"

class RequestRset : public Request {
public:
    RequestRset();
    RequestRset(std::istream& stream);
    void accept(Server& server) override;
};

#endif