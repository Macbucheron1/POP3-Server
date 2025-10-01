#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <iostream>

using namespace std;

class Response {

    private:
        bool success;
        string message;

    public:
        Response(bool success, const string& message);
        friend ostream& operator<<(ostream& os, const Response& r);
};

#endif