#include "../include/RequestRetr.h"
#include "../include/Server.h"
#include <sstream>

RequestRetr::RequestRetr(size_t messageId) 
    : Request("RETR"), m_messageId(messageId) {}

RequestRetr::RequestRetr(std::istream& stream) : Request(stream) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        if (!(iss >> m_messageId)) {
            m_messageId = 0; // Invalid
        }
    } else {
        m_messageId = 0; // Invalid
    }
}

RequestRetr::RequestRetr(const std::string& line, bool parseLine) : Request(line, parseLine) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        if (!(iss >> m_messageId)) {
            m_messageId = 0; // Invalid
        }
    } else {
        m_messageId = 0; // Invalid
    }
}

size_t RequestRetr::getMessageId() const {
    return m_messageId;
}

void RequestRetr::accept(Server& server) {
    server.visit(*this);
}