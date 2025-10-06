#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <string>

#include "asio.hpp"
#include "Message.h"

class Request;
class RequestQuit;
class RequestUnknown;
class RequestUser;
class RequestPass;
class RequestStat;
class RequestList;
class RequestRetr;
class RequestDele;
class RequestNoop;
class RequestRset;

namespace ip = asio::ip;
namespace chrono = std::chrono;

class Server
{
private:
	// Beaucoup de protocoles sont spécifiés sous la forme d'une
	// machine à états, il est donc naturel de les implémenter de la
	// même manière (cela facilite le travail de vérification de la
	// correction par rapport aux spécifications).
	enum class State
	{
		STOPPED,
		WAITING_FOR_CONNECTION,
		TALKING_TO_USER,
		QUITTING
	};
	State m_currentState{State::STOPPED};

	// États POP3 selon RFC 1939
	enum class Phase
	{
		AUTHORIZATION,
		TRANSACTION,
		UPDATE
	};
	Phase m_phase{Phase::AUTHORIZATION};

	// La référence au contexte ASIO, nécessaire pour orchestrer les
	// communications réseau
	asio::io_context& m_io;
	// L'objet qui permet d'écouter sur le port réseau et de créer une
	// socket pour communiquer avec un client qui se présente
	ip::tcp::acceptor m_acceptor;
	// On utilise directement un object iostream qui représente le canal de
	// communication fourni par la connexion TCP/IP.
	// On peut lire et écrire sur ce canal avec les opérateurs habituels <<
	// et >>.
	ip::tcp::iostream m_stream;

	// Le port TCP/IP sur lequel le programme communique.
	constexpr static int ECHO_PORT = 9999;

	// Stockage des messages et états POP3
	std::vector<Message> m_maildrop;
	std::vector<bool> m_deleted;
	std::string m_currentUser;
	
	// Méthodes helpers
	size_t count_not_deleted() const;
	size_t total_octets_not_deleted() const;
	bool valid_msg(size_t i) const;
	void write_multiline(const std::vector<std::string>& lines);
	void initialize_maildrop();
	
	std::string process(const std::string& req);

public:
	explicit Server(asio::io_context& io);

	void start();

	// Méthodes visitor pour le pattern Visitor
	void visit(RequestQuit& request);
	void visit(RequestUnknown& request);
	void visit(RequestUser& request);
	void visit(RequestPass& request);
	void visit(RequestStat& request);
	void visit(RequestList& request);
	void visit(RequestRetr& request);
	void visit(RequestDele& request);
	void visit(RequestNoop& request);
	void visit(RequestRset& request);
};

#endif // !defined(SERVER_H)
