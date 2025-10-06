#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message {
    string content;
public:
    Message(const string& c);
    string getContent() const;
    size_t getSize() const; // Taille en octets (incluant CRLF)
};

#endif