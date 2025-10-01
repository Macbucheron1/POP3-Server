#include "../include/RequestFactory.h"
#include "../include/RequestQuit.h"

unique_ptr<Request> RequestFactory::parse(const string& line) {

    string cmd = line.substr(0, line.find(' '));

    /*if (cmd == "QUIT") {
        return make_unique<RequestQuit>();
    }*/

    return nullptr; // commande inconnue
}