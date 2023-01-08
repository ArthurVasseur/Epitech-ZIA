/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** SessionManager
*/

#include <memory>
#include <map>
#include "Session.hpp"

class SessionManager {
public:
	SessionManager() = default;
	void AddAndStart(const std::shared_ptr<Session>& session)
	{
		_sessions[session->getID()] = session;
		session->readHandshake();
	}

	void stopAndErase(const std::shared_ptr<Session>& session)
	{
		_sessions.erase(session->getID());
		session->setExpired();
	}

	std::shared_ptr<Session> operator[](std::size_t index) {return _sessions.at(index);}

private:
	std::map<std::size_t, std::shared_ptr<Session>> _sessions;
};