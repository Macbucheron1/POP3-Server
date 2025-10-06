#include "../include/RequestQuit.h"
#include "../include/Server.h"

RequestQuit::RequestQuit() : Request("QUIT") {}

RequestQuit::RequestQuit(istream& stream) : Request(stream) {}

void RequestQuit::accept(Server& server){
    server.visit(*this);
};
