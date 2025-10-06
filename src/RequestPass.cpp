#include "../include/RequestPass.h"
#include "../include/Server.h"

RequestPass::RequestPass(const std::string& password) 
    : Request("PASS"), m_password(password) {}

RequestPass::RequestPass(std::istream& stream) 
    : Request(stream) {
    if (!args.empty()) {
        m_password = args[0];
    }
}

RequestPass::RequestPass(const std::string& line, bool parseLine)
    : Request(line, parseLine) {
    if (!args.empty()) {
        m_password = args[0];
    }
}

std::string RequestPass::getPassword() const {
    return m_password;
}

void RequestPass::accept(Server& server) {
    server.visit(*this);
}