#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message {
    string content;
public:
    Message(const string& c);
    string getContent() const;
};

#endif