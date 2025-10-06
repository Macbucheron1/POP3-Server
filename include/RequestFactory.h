#ifndef FACTORY_H
#define FACTORY_H

#include "Request.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

class RequestFactory {
public:
    static unique_ptr<Request> parse(istream& stream);
};

#endif