#include "../include/RequestFactory.h"
#include "../include/RequestQuit.h"
#include "../include/RequestUnknown.h"
#include "../include/RequestUser.h"
#include "../include/RequestPass.h"
#include "../include/RequestStat.h"
#include "../include/RequestList.h"
#include "../include/RequestRetr.h"
#include "../include/RequestDele.h"
#include "../include/RequestNoop.h"
#include "../include/RequestRset.h"
#include <algorithm>
#include <cctype>
#include <sstream>

unique_ptr<Request> RequestFactory::parse(istream& stream) {
    // Lire une ligne depuis le stream
    string line;
    if (!getline(stream, line)) {
        return nullptr; // Échec de lecture
    }
    
    // Parser la ligne pour extraire la commande
    string cleanLine = line;
    cleanLine.erase(std::remove(cleanLine.begin(), cleanLine.end(), '\r'), cleanLine.end());
    
    if (cleanLine.empty()) {
        return nullptr;
    }
    
    istringstream iss(cleanLine);
    string command;
    iss >> command;
    
    if (command.empty()) {
        return nullptr;
    }
    
    // Convertir la commande en majuscules pour comparaison case-insensitive
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    // Créer la requête appropriée basée sur la commande
    if (command == "QUIT") {
        return make_unique<RequestQuit>();
    }
    else if (command == "USER") {
        return make_unique<RequestUser>(line, true);
    }
    else if (command == "PASS") {
        return make_unique<RequestPass>(line, true);
    }
    else if (command == "STAT") {
        return make_unique<RequestStat>();
    }
    else if (command == "LIST") {
        return make_unique<RequestList>(line, true);
    }
    else if (command == "RETR") {
        return make_unique<RequestRetr>(line, true);
    }
    else if (command == "DELE") {
        return make_unique<RequestDele>(line, true);
    }
    else if (command == "NOOP") {
        return make_unique<RequestNoop>();
    }
    else if (command == "RSET") {
        return make_unique<RequestRset>();
    }
    
    // Commande inconnue
    return make_unique<RequestUnknown>(line, true);
}