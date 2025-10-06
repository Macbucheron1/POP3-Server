#include "../include/RequestFactory.h"
#include "../include/RequestQuit.h"
#include "../include/RequestUnknown.h"

unique_ptr<Request> RequestFactory::parse(istream& stream) {
    // Créer une RequestUnknown temporaire pour lire et parser la ligne
    auto tempRequest = make_unique<RequestUnknown>(stream);
    
    // Si la lecture a échoué, retourner nullptr
    if (tempRequest->getCommand().empty()) {
        return nullptr;
    }
    
    // Déterminer le type de requête basé sur la commande parsée
    if (tempRequest->getCommand() == "QUIT") {
        return make_unique<RequestQuit>();
    }
    
    // Retourner la RequestUnknown qui a déjà tout parsé
    return tempRequest;
}