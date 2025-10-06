#include "../include/RequestFactory.h"
#include "../include/RequestQuit.h"
#include "../include/RequestUnknown.h"
#include <algorithm>

unique_ptr<Request> RequestFactory::parse(istream& stream) {
    string line;
    if (getline(stream, line)) {
        // Retirer les caractères \r en fin de ligne
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        
        string cmd = line.substr(0, line.find(' '));
        
        if (cmd == "QUIT") {
            auto request = make_unique<RequestQuit>();
            return request;
        }
        
        return make_unique<RequestUnknown>(line, true);
    }
    
    // Si on ne peut pas lire, retourner nullptr
    return nullptr;
}