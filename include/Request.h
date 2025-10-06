#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Server; 

class Request {

    protected:
        string command;
        vector<string> args;
        
        void parseFromLine(const string& line);
    public:
        Request(const string& cmd);
        Request(istream& stream);
        Request(const string& line, bool parseLine);
        string getCommand() const;
        vector<string> getArgs() const;
        virtual void accept(Server& server) = 0;
};

#endif