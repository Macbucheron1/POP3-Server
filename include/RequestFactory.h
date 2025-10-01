#ifndef FACTORY_H
#define FACTORY_H

#include "Request.h"
#include <sstream>
#include <string>

using namespace std;

class RequestFactory {
public:
    static unique_ptr<Request> parse(const string& line);
};

#endif