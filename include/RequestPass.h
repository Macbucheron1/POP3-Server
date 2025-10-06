#ifndef REQUESTPASS_H
#define REQUESTPASS_H

#include "Request.h"
#include <string>

class RequestPass : public Request {
private:
    std::string m_password;

public:
    RequestPass(const std::string& password);
    RequestPass(std::istream& stream);
    RequestPass(const std::string& line, bool parseLine);
    std::string getPassword() const;
    void accept(Server& server) override;
};

#endif