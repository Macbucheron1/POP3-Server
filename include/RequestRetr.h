#ifndef REQUESTRETR_H
#define REQUESTRETR_H

#include "Request.h"

class RequestRetr : public Request {
private:
    size_t m_messageId;

public:
    RequestRetr(size_t messageId);
    RequestRetr(std::istream& stream);
    RequestRetr(const std::string& line, bool parseLine);
    size_t getMessageId() const;
    void accept(Server& server) override;
};

#endif