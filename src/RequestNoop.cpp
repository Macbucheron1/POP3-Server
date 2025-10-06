#include "../include/RequestNoop.h"
#include "../include/Server.h"

RequestNoop::RequestNoop() : Request("NOOP") {}

RequestNoop::RequestNoop(std::istream& stream) : Request(stream) {}

void RequestNoop::accept(Server& server) {
    server.visit(*this);
}