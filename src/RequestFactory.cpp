#include "../include/RequestFactory.h"
#include "../include/RequestQuit.h"
#include "../include/RequestUnknown.h"

unique_ptr<Request> RequestFactory::parse(const string& line) {

    string cmd = line.substr(0, line.find(' '));

    if (cmd == "QUIT") {
        return make_unique<RequestQuit>();
    }

    return std::make_unique<RequestUnknown>(line);
}