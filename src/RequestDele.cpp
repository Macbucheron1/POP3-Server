#include "../include/RequestDele.h"
#include "../include/Server.h"
#include <sstream>

RequestDele::RequestDele(size_t messageId) 
    : Request("DELE"), m_messageId(messageId) {}

RequestDele::RequestDele(std::istream& stream) : Request(stream) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        if (!(iss >> m_messageId)) {
            m_messageId = 0; // Invalid
        }
    } else {
        m_messageId = 0; // Invalid
    }
}

RequestDele::RequestDele(const std::string& line, bool parseLine) : Request(line, parseLine) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        if (!(iss >> m_messageId)) {
            m_messageId = 0; // Invalid
        }
    } else {
        m_messageId = 0; // Invalid
    }
}

size_t RequestDele::getMessageId() const {
    return m_messageId;
}

void RequestDele::accept(Server& server) {
    server.visit(*this);
}