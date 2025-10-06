#ifndef REQUESTDELE_H
#define REQUESTDELE_H

#include "Request.h"

class RequestDele : public Request {
private:
    size_t m_messageId;

public:
    RequestDele(size_t messageId);
    RequestDele(std::istream& stream);
    RequestDele(const std::string& line, bool parseLine);
    size_t getMessageId() const;
    void accept(Server& server) override;
};

#endif