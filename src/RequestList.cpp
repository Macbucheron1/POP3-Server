#include "../include/RequestList.h"
#include "../include/Server.h"
#include <sstream>

RequestList::RequestList() : Request("LIST") {}

RequestList::RequestList(size_t messageId) 
    : Request("LIST"), m_messageId(messageId) {}

RequestList::RequestList(std::istream& stream) : Request(stream) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        size_t id;
        if (iss >> id) {
            m_messageId = id;
        }
    }
}

RequestList::RequestList(const std::string& line, bool parseLine) : Request(line, parseLine) {
    if (!args.empty()) {
        std::istringstream iss(args[0]);
        size_t id;
        if (iss >> id) {
            m_messageId = id;
        }
    }
}

std::optional<size_t> RequestList::getMessageId() const {
    return m_messageId;
}

void RequestList::accept(Server& server) {
    server.visit(*this);
}