/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** TCPServer
*/

#ifndef ZIA_TCPSERVER_HPP
#define ZIA_TCPSERVER_HPP
#include <string>
#include <functional>
#include <asio.hpp>
#include <set>
#include <queue>
#include <atomic>
#include "ziapi/Http.hpp"
#include "Session.hpp"
#include "SessionManager.hpp"
class TCPServer
{
public:
    TCPServer(int port, std::string &listening, ziapi::http::IRequestOutputQueue &requests, ziapi::http::IResponseInputQueue &responses) :
		_port(port), _listening(listening), _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port)),
		_requests(requests), _responses(responses), _currentIndex(0), _stopWorker(false), _isStopped(false){}
    ~TCPServer();

	void run();
	void terminate();
    void startAccept();
private:
    int _port;
    std::string _listening;
    asio::io_context _context;
    asio::ip::tcp::acceptor _acceptor;
	ziapi::http::IRequestOutputQueue &_requests;
	ziapi::http::IResponseInputQueue &_responses;
	SessionManager _sessions;
	std::unique_ptr<std::thread> _worker;
	std::size_t _currentIndex;
	std::atomic_bool _stopWorker;
	std::atomic_bool  _isStopped;
};


#endif //ZIA_TCPSERVER_HPP