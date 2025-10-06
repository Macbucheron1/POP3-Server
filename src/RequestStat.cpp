#include "../include/RequestStat.h"
#include "../include/Server.h"

RequestStat::RequestStat() : Request("STAT") {}

RequestStat::RequestStat(std::istream& stream) : Request(stream) {}

void RequestStat::accept(Server& server) {
    server.visit(*this);
}