#ifndef REQUESTLIST_H
#define REQUESTLIST_H

#include "Request.h"
#include <optional>

class RequestList : public Request {
private:
    std::optional<size_t> m_messageId;

public:
    RequestList();
    RequestList(size_t messageId);
    RequestList(std::istream& stream);
    RequestList(const std::string& line, bool parseLine);
    std::optional<size_t> getMessageId() const;
    void accept(Server& server) override;
};

#endif