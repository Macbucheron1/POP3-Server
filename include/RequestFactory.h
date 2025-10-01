#ifndef FACTORY_H
#define FACTORY_H

#include "Request.h"
#include <string>
#include <memory>

using namespace std;

class RequestFactory {
public:
    static unique_ptr<Request> parse(const string& line);
};

#endif