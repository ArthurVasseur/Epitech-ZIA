/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Session
*/

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include <asio.hpp>
#include <array>
#include <memory>
#include "ziapi/Http.hpp"

class SessionManager;
class Session : public std::enable_shared_from_this<Session>
{
public:
	Session() = delete;
	Session(asio::ip::tcp::socket socket, ziapi::http::IRequestOutputQueue& requests, std::size_t id, SessionManager &manager);
	Session(Session&&) = default;
	~Session() = default;
	void setExpired();
	void read();
	void write(const ziapi::http::Response& res, bool closeSocket = false);
	ziapi::http::Request parse();
	std::string makeHttpResponse(const ziapi::http::Response &res);

	std::size_t getID() const
	{
		return _id;
	}

	[[nodiscard]] bool expired() const;

private:
	asio::ip::tcp::socket _socket;
	std::array<char, 1024> _buffer{};
	ziapi::http::IRequestOutputQueue& _requests;
	std::size_t _id;
	SessionManager &_manager;
};

#endif /* !SESSION_HPP_ */
