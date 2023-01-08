/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** TCPServer
*/

#include "TCPServer.hpp"
#include <iostream>
#include "ziapi/Logger.hpp"

void TCPServer::run()
{
	startAccept();
	while (!_stopWorker)
	{
		if(_context.stopped())
			_context.restart();
		_context.poll();
		auto x = _responses.Pop();
		do
		{
			try
			{
				if (!x)
					continue;
				auto &[res, ctx] = x.value();
				auto clientId = ctx.at("client.socket.id");
				auto idx = std::any_cast<std::size_t>(clientId);
				if (ctx.find("client.socket.keepAlive") != ctx.end())
					_sessions[idx]->write(x->first, false);
				else _sessions[idx]->write(x->first, true);
				x = _responses.Pop();
			}
			catch (const std::exception& e)
			{
				x = _responses.Pop();
				ziapi::Logger::Error(e.what());
			}
		} while (x);
	}
	_isStopped = true;
}

void TCPServer::startAccept()
{
	_acceptor.async_accept([this](asio::error_code error, asio::ip::tcp::socket socket)
	{
		if (!error && _acceptor.is_open())
		{
			_sessions.AddAndStart(std::make_shared<Session>(std::move(socket), _requests, _currentIndex, _sessions));
			_currentIndex++;
		}
		startAccept();
	});
}

TCPServer::~TCPServer()
{
	terminate();
	_stopWorker = true;
}

void TCPServer::terminate()
{
	_stopWorker = true;
	while (!_isStopped){}
	_context.stop();
}
