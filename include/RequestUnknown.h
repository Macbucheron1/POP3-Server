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
        RequestUnknown(istream& stream);
        RequestUnknown(const string& line, bool parseLine);
        string getRawCommand() const;
        void accept(Server& server) override;
};

#endif