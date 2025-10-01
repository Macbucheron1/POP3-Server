#include "../include/Request.h"

Request::Request(const string& cmd) : command(cmd) {};

string Request::getCommand() const { 
    return command; 
}

