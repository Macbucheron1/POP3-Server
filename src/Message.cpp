#include "../include/Message.h"
#include <algorithm>

Message::Message(const string& c) : content(c) {}

string Message::getContent() const {
    return content;
}

size_t Message::getSize() const {
    // Le contenu contient déjà les \r\n, donc la taille est directement celle du string
    // En POP3, la taille inclut tous les octets du message tel qu'il sera transmis
    return content.size();
}