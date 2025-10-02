#ifndef REQUESTUNKNOWN_H
#define REQUESTUNKNOWN_H

#include "Request.h"
#include <string>

using namespace std;

class RequestUnknown : public Request {
    private:
        string m_rawCommand;
        
    public:
        RequestUnknown(const string& cmd);
        string getRawCommand() const;
        void accept(Server& server) override;
};

#endif