#ifndef REQUESTUSER_H
#define REQUESTUSER_H

#include "Request.h"
#include <string>

class RequestUser : public Request {
private:
    std::string m_username;

public:
    RequestUser(const std::string& username);
    RequestUser(std::istream& stream);
    RequestUser(const std::string& line, bool parseLine);
    std::string getUsername() const;
    void accept(Server& server) override;
};

#endif