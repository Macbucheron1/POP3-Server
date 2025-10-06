#include <iostream>

#include "asio.hpp"

#include "../include/Server.h"
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
#include "../include/Response.h"

namespace ip = asio::ip;


// On crée l'instance du Serveur avec un objet ASIO context qui sert à
// orchestrer tous les objets et événements gérés par ASIO (connexions réseau,
// timers, etc.)
Server::Server(asio::io_context& ioContext) :
	m_io{ioContext},
	// On crée la socket sur laquelle on écoutera
	m_acceptor{ioContext, ip::tcp::endpoint{ip::tcp::v4(), ECHO_PORT}}
{
	// Initialiser le maildrop avec des messages de test
	initialize_maildrop();
}

void Server::start()
{
	// On utilise une boucle infinie, chaque tour de boucle est l'
	// interaction
	// complète avec un client jusqu'à sa déconnexion.
	// Le serveur quitte lorsqu'il crashe suite à une exception...
	for (;;)
	{
		m_currentState = State::WAITING_FOR_CONNECTION;

		// On initialise le flux de communication, qui contient une
		// socket non connectée pour le moment. On écoute sur le port
		// TCP/IP et lorsqu'un client se présente, la socket est alors
		// "branchée", et le flux m_stream permet de lire et écrire sur
		// la socket.
		// Pour d'autres manières de faire, par exemple, pour gérer
		// plusieurs clients simultanément, il y a quelques exemples
		// dans la documentation d'ASIO :
		// https://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/examples/cpp11_examples.html.
		m_stream = ip::tcp::iostream{};
		m_acceptor.accept(m_stream.socket());

		std::cerr << "New client connected!" << std::endl;

		// Initialiser l'état POP3 à AUTHORIZATION
		m_phase = Phase::AUTHORIZATION;
		m_currentUser.clear();
		// Réinitialiser les suppressions 
		std::fill(m_deleted.begin(), m_deleted.end(), false);

		m_stream << "+OK POP3 server ready\r\n";

		// On passe à l'état suivant de la communication.
		m_currentState = State::TALKING_TO_USER;

		// On traite les requêtes tant qu'on peut lire depuis le flux.
		while (m_stream && m_currentState != State::QUITTING) {
			auto request = RequestFactory::parse(m_stream);
			
			// Vérifier si on a pu parser une requête
			if (!request) {
				break;
			}

			// Pattern Visitor : double dispatch via accept()
			request->accept(*this);

		}

		// Si l'état est QUITTING, cela signifie que l'on a quitté la
		// boucle volontairement, suite à une requête du client, et non
		// parce que le flux est devenu invalide (ce qui arrive si le
		// client s'est déconnecté par exemple).
		// La réponse QUIT a déjà été envoyée dans visit(RequestQuit&)

		// On ferme la connexion avec le client de façon polie (si on
		// détruit ou on réassigne l'objet m_stream, le client recevra
		// un TCP RESET à la place) et on signifie au système
		// d'exploitation qu'il peut libérer les ressources associées
		// dans les structures de données réseau.
		//
		// Il faut toujours vérifier si le flux est dans un état valide,
		// il se peut que la connexion soit déjà fermée si on a soi-même
		// reçu un TCP RESET.
		if (m_stream) {
			m_stream.close();
		}
	}
}

// Méthodes helpers
size_t Server::count_not_deleted() const
{
	size_t count = 0;
	for (size_t i = 0; i < m_maildrop.size(); ++i) {
		if (!m_deleted[i]) {
			count++;
		}
	}
	return count;
}

size_t Server::total_octets_not_deleted() const
{
	size_t total = 0;
	for (size_t i = 0; i < m_maildrop.size(); ++i) {
		if (!m_deleted[i]) {
			total += m_maildrop[i].getSize();
		}
	}
	return total;
}

bool Server::valid_msg(size_t i) const
{
	return (i > 0 && i <= m_maildrop.size() && !m_deleted[i - 1]);
}

void Server::write_multiline(const std::vector<std::string>& lines)
{
	for (const auto& line : lines) {
		// Dot-stuffing : préfixer d'un '.' toute ligne commençant par '.'
		if (!line.empty() && line[0] == '.') {
			m_stream << "." << line << "\r\n";
		} else {
			m_stream << line << "\r\n";
		}
	}
	m_stream << ".\r\n"; // Terminaison multilignes RFC 1939
}

void Server::initialize_maildrop()
{
	// Messages avec en-têtes RFC complets (Date, From, To, Subject + ligne blanche + corps)
	m_maildrop.emplace_back(
		"From: alice@example.com\r\n"
		"To: nathan@example.com\r\n"
		"Subject: Hello Nathan\r\n"
		"Date: Mon, 06 Oct 2025 10:00:00 +0000\r\n"
		"\r\n"
		"Hello Nathan!\r\n"
		"How are you doing today?\r\n"
	);
	
	m_maildrop.emplace_back(
		"From: charlie@example.com\r\n"
		"To: nathan@example.com\r\n"
		"Subject: Important Meeting\r\n"
		"Date: Mon, 06 Oct 2025 14:30:00 +0000\r\n"
		"\r\n"
		"Don't forget our meeting tomorrow at 9 AM.\r\n"
		"Location: Conference Room A\r\n"
	);
	
	m_maildrop.emplace_back(
		"From: dave@example.com\r\n"
		"To: nathan@example.com\r\n"
		"Subject: Multi-line Test\r\n"
		"Date: Mon, 06 Oct 2025 16:45:00 +0000\r\n"
		"\r\n"
		"This is a test message.\r\n"
		"With multiple lines in the body.\r\n"
		"Line three here.\r\n"
	);
	
	m_maildrop.emplace_back(
		"From: system@example.com\r\n"
		"To: nathan@example.com\r\n"
		"Subject: Dot-stuffing Test\r\n"
		"Date: Mon, 06 Oct 2025 18:00:00 +0000\r\n"
		"\r\n"
		"This message tests dot-stuffing:\r\n"
		".This line starts with a dot\r\n"
		"..This line starts with two dots\r\n"
		".End of dot test\r\n"
		"Normal line after dots.\r\n"
	);
	
	// Initialiser le vecteur de suppressions
	m_deleted.resize(m_maildrop.size(), false);
}

// Implémentation des méthodes visitor
void Server::visit(RequestQuit& request)
{
	if (m_phase == Phase::TRANSACTION) {
		// Passer en UPDATE et supprimer réellement les messages marqués
		m_phase = Phase::UPDATE;
		
		// Compter les messages à supprimer
		size_t deletedCount = 0;
		for (size_t i = 0; i < m_deleted.size(); ++i) {
			if (m_deleted[i]) {
				deletedCount++;
			}
		}
		
		// Supprimer réellement les messages marqués du maildrop
		// Parcourir en sens inverse pour éviter les décalages d'indices
		for (int i = static_cast<int>(m_deleted.size()) - 1; i >= 0; --i) {
			if (m_deleted[i]) {
				m_maildrop.erase(m_maildrop.begin() + i);
				m_deleted.erase(m_deleted.begin() + i);
			}
		}
		
		m_stream << "+OK POP3 server signing off (" << deletedCount << " messages deleted)\r\n";
	} else {
		// En AUTHORIZATION, ne pas supprimer
		m_stream << "+OK POP3 server signing off\r\n";
	}
	m_currentState = State::QUITTING;
}

void Server::visit(RequestUnknown& request)
{
	m_stream << "-ERR unknown command\r\n";
}

void Server::visit(RequestUser& request)
{
	if (m_phase != Phase::AUTHORIZATION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	std::string username = request.getUsername();
	if (username.empty()) {
		m_stream << "-ERR invalid syntax\r\n";
		return;
	}
	
	// RFC permet USER multiple - le dernier remplace les précédents
	m_currentUser = username;
	m_stream << "+OK " << m_currentUser << " is a valid mailbox\r\n";
}

void Server::visit(RequestPass& request)
{
	if (m_phase != Phase::AUTHORIZATION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	if (m_currentUser.empty()) {
		m_stream << "-ERR USER command required first\r\n";
		return;
	}
	
	std::string password = request.getPassword();
	if (password.empty()) {
		m_stream << "-ERR invalid syntax\r\n";
		return;
	}
	
	// Pour le TP, accepter n'importe quel password non-vide
	// Passer en TRANSACTION
	m_phase = Phase::TRANSACTION;
	size_t count = count_not_deleted();
	size_t octets = total_octets_not_deleted();
	m_stream << "+OK " << count << " messages (" << octets << " octets)\r\n";
}

void Server::visit(RequestStat& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	size_t count = count_not_deleted();
	size_t octets = total_octets_not_deleted();
	m_stream << "+OK " << count << " " << octets << "\r\n";
}

void Server::visit(RequestList& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	auto messageId = request.getMessageId();
	if (messageId.has_value()) {
		// LIST avec argument spécifique
		size_t id = messageId.value();
		if (!valid_msg(id)) {
			m_stream << "-ERR no such message\r\n";
			return;
		}
		size_t size = m_maildrop[id - 1].getSize();
		m_stream << "+OK " << id << " " << size << "\r\n";
	} else {
		// LIST sans argument - multilignes
		m_stream << "+OK " << count_not_deleted() << " messages\r\n";
		for (size_t i = 0; i < m_maildrop.size(); ++i) {
			if (!m_deleted[i]) {
				size_t size = m_maildrop[i].getSize();
				m_stream << (i + 1) << " " << size << "\r\n";
			}
		}
		m_stream << ".\r\n";
	}
}

void Server::visit(RequestRetr& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	size_t id = request.getMessageId();
	if (!valid_msg(id)) {
		m_stream << "-ERR no such message\r\n";
		return;
	}
	
	const Message& msg = m_maildrop[id - 1];
	size_t size = msg.getSize();
	m_stream << "+OK " << size << " octets\r\n";
	
	// Envoyer le contenu avec dot-stuffing
	std::string content = msg.getContent();
	std::istringstream iss(content);
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(iss, line)) {
		// Nettoyer les \r en fin de ligne si présents
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		lines.push_back(line);
	}
	write_multiline(lines);
}

void Server::visit(RequestDele& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	size_t id = request.getMessageId();
	if (id == 0 || id > m_maildrop.size()) {
		m_stream << "-ERR no such message\r\n";
		return;
	}
	
	if (m_deleted[id - 1]) {
		m_stream << "-ERR message " << id << " already deleted\r\n";
		return;
	}
	
	m_deleted[id - 1] = true;
	m_stream << "+OK message " << id << " deleted\r\n";
}

void Server::visit(RequestNoop& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	m_stream << "+OK\r\n";
}

void Server::visit(RequestRset& request)
{
	if (m_phase != Phase::TRANSACTION) {
		m_stream << "-ERR not in correct state\r\n";
		return;
	}
	
	// Désmarquer tous les messages supprimés
	std::fill(m_deleted.begin(), m_deleted.end(), false);
	
	size_t count = count_not_deleted();
	size_t octets = total_octets_not_deleted();
	m_stream << "+OK " << count << " messages (" << octets << " octets)\r\n";
}
