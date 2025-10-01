#include "../include/Request.h"
#include "../include/Server.h"
#include <sstream>
#include <algorithm>

// Constructeur qui lit une requête complète depuis un flux d'entrée
Request::Request(std::istream& stream)
{
    // Lire la ligne complète
    std::getline(stream, fullLine);
    
    // Gérer correctement les fins de ligne \r\n
    // std::getline() supprime \n mais pas \r sous Linux/MacOS
    if (!fullLine.empty() && fullLine.back() == '\r') {
        fullLine.pop_back();
    }
    
    // Extraire le premier mot (commande) de la ligne
    std::istringstream iss(fullLine);
    iss >> command;
    
    // Si pas de commande trouvée, utiliser une chaîne vide
    if (iss.fail()) {
        command = "";
    }
}

// Retourner la commande (premier mot)
std::string Request::getCommand() const
{
    return command;
}

// Méthode pour traiter la requête
void Request::dispatch(Server& server)
{

}

// Retourner la ligne complète
std::string Request::getFullLine() const
{
    return fullLine;
}