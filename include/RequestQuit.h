#ifndef REQUESTQUIT_H
#define REQUESTQUIT_H

#include "Request.h"

class RequestQuit : public Request {
    public:
        RequestQuit();
        void accept(Server& server) override;
};

#endif