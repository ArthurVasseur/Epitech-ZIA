/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Session
*/

#ifndef ZIA_SESSION_HPP
#define ZIA_SESSION_HPP

#include <functional>
#include <iostream>
#include <vector>
#include <array>
#include "asio.hpp"
#include "asio/ssl.hpp"
#include "ziapi/Http.hpp"

class SessionManager;
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(asio::ssl::stream<asio::ip::tcp::socket> socket, ziapi::http::IRequestOutputQueue& _requests, SessionManager &manager, std::size_t id);
	void setExpired();
    void readHandshake();
	void write(const ziapi::http::Response& res, bool closeSocket = false);
	std::string makeHttpResponse(const ziapi::http::Response &res);
	ziapi::http::Request parse();
	std::size_t getID() const
	{
		return _id;
	}

private:
    void checkHandshake();
	void read();

    asio::ssl::stream<asio::ip::tcp::socket> _socket;
	std::array<char, 1024> _buffer{};
	ziapi::http::IRequestOutputQueue& _requests;
	std::size_t _id;
	SessionManager &_manager;
};



#endif //ZIA_SESSION_HPP
