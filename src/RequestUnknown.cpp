#include "../include/RequestUnknown.h"

RequestUnknown::RequestUnknown(const string& cmd)
    : Request("UNKNOWN"), m_rawCommand(cmd) {}

string RequestUnknown::getRawCommand() const {
    return m_rawCommand;
}

void RequestUnknown::accept(Server& server){
    // TODO: Implémenter
}
