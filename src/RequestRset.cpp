#include "../include/RequestRset.h"
#include "../include/Server.h"

RequestRset::RequestRset() : Request("RSET") {}

RequestRset::RequestRset(std::istream& stream) : Request(stream) {}

void RequestRset::accept(Server& server) {
    server.visit(*this);
}