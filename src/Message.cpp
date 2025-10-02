#include "../include/Message.h"

Message::Message(const string& c) : content(c) {}

string Message::getContent() const {
    return content;
}