#include "../include/RequestUnknown.h"
#include "../include/Server.h"

RequestUnknown::RequestUnknown(const string& cmd)
    : Request("UNKNOWN"), m_rawCommand(cmd) {}

RequestUnknown::RequestUnknown(istream& stream) : Request(stream) {
    // Reconstruire la commande raw à partir de command et args
    m_rawCommand = command;
    for (const auto& arg : args) {
        m_rawCommand += " " + arg;
    }
}

RequestUnknown::RequestUnknown(const string& line, bool parseLine) : Request(line, parseLine) {
    m_rawCommand = line;
}

string RequestUnknown::getRawCommand() const {
    return m_rawCommand;
}

void RequestUnknown::accept(Server& server){
    server.visit(*this);
}
