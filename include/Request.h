#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>

// Déclaration forward de la classe Server
class Server;

class Request
{
private:
    std::string command;
    std::string fullLine;

public:
    // Constructeur qui prend un flux d'entrée et lit une requête complète
    explicit Request(std::istream& stream);
    
    // Méthode pour obtenir la commande (premier mot)
    std::string getCommand() const;
    
    // Méthode pour traiter la requête (à implémenter plus tard)
    void dispatch(Server& server);
    
    // Méthode pour obtenir la ligne complète (utile pour debug/log)
    std::string getFullLine() const;
};

#endif // !defined(REQUEST_H)