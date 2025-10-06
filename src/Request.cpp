#include "../include/Request.h"
#include <sstream>

Request::Request(const string& cmd) : command(cmd) {};

Request::Request(istream& stream) {
    string line;
    if (getline(stream, line)) {
        parseFromLine(line);
    }
}

Request::Request(const string& line, bool parseLine) {
    if (parseLine) {
        parseFromLine(line);
    } else {
        command = line;
    }
}

void Request::parseFromLine(const string& line) {
    istringstream iss(line);
    iss >> command;
    
    string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
}

string Request::getCommand() const { 
    return command; 
}

vector<string> Request::getArgs() const {
    return args;
}

