/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** SSLServer
*/

#ifndef ZIA_SSLSERVER_HPP
#define ZIA_SSLSERVER_HPP

#include <functional>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <atomic>
#include "asio.hpp"
#include "asio/ssl.hpp"
#include "ziapi/Http.hpp"
#include "Session.hpp"
#include "SessionManager.hpp"

class SSLServer
{
public:
	SSLServer(unsigned short port,
			const std::string&,
			const std::string& keyPath,
			ziapi::http::IRequestOutputQueue& requests,
			ziapi::http::IResponseInputQueue& responses);

	~SSLServer();

	void run();

	void terminate();

private:
	[[nodiscard]] std::string get_password() const;

	void accept();

	std::vector<std::shared_ptr<Session>> _sessions;
	asio::io_context _context;
	asio::ip::tcp::acceptor acceptor_;
	asio::ssl::context _sslContext;
	ziapi::http::IRequestOutputQueue& _requests;
	ziapi::http::IResponseInputQueue& _responses;
	SessionManager _manager;
	std::size_t _maxID;
	std::atomic_bool _stopWorker;
	std::atomic_bool  _isStopped;
};

#endif //ZIA_SSLSERVER_HPP
