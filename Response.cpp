#include "Response.h"

Response::Response(bool success, const string& message) 
    : success(success), message(message) {};

ostream& operator<<(ostream& os, const Response& r) {
    os << (r.success ? "+OK " : "-ERR ") << r.message << "\r\n";
    return os;
}