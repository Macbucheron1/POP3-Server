#include "../include/RequestUser.h"
#include "../include/Server.h"

RequestUser::RequestUser(const std::string& username) 
    : Request("USER"), m_username(username) {}

RequestUser::RequestUser(std::istream& stream) 
    : Request(stream) {
    if (!args.empty()) {
        m_username = args[0];
    }
}

RequestUser::RequestUser(const std::string& line, bool parseLine)
    : Request(line, parseLine) {
    if (!args.empty()) {
        m_username = args[0];
    }
}

std::string RequestUser::getUsername() const {
    return m_username;
}

void RequestUser::accept(Server& server) {
    server.visit(*this);
}