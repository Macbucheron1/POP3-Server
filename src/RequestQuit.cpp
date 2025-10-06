#include "../include/RequestQuit.h"

RequestQuit::RequestQuit() : Request("QUIT") {}

RequestQuit::RequestQuit(istream& stream) : Request(stream) {}

void RequestQuit::accept(Server& server){
    // TODO: Implémenter
};
