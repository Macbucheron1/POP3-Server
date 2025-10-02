#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

class Server; 

class Request {

    protected:
        string command;
    public:
        Request(const string& cmd);
        string getCommand() const;
        virtual void accept(Server& server) = 0;
};

#endif