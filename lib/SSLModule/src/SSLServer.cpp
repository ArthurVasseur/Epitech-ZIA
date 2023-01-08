/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** SSLServer
*/

#include "SSLServer.hpp"
#include "ziapi/Logger.hpp"
SSLServer::SSLServer(unsigned short port,
    const std::string&,
    const std::string& keyPath,
    ziapi::http::IRequestOutputQueue& requests,
    ziapi::http::IResponseInputQueue& response)
    : _context(), acceptor_(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _sslContext(asio::ssl::context::tlsv13_server), _requests(requests), _responses(response), _maxID(0), _manager(), _stopWorker(false), _isStopped(false)

{
    _sslContext.set_options(
        asio::ssl::context::default_workarounds | asio::ssl::context::no_sslv2 | asio::ssl::context::single_dh_use);
    _sslContext.set_password_callback(std::bind(&SSLServer::get_password, this));
	_sslContext.use_certificate_chain_file(keyPath + "/user.crt");
    _sslContext.use_private_key_file(keyPath + "/user.key", asio::ssl::context::pem);
    _sslContext.use_tmp_dh_file(keyPath + "/dh2048.pem");
}

void SSLServer::run()
{
    accept();
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

std::string SSLServer::get_password() const
{
    return "toto";
}

void SSLServer::accept()
{
    acceptor_.async_accept(
        [this](const std::error_code& error, asio::ip::tcp::socket socket)
        {
            if (!error)
            {
				_sessions.emplace_back(std::make_shared<Session>(asio::ssl::stream<asio::ip::tcp::socket>(std::move(socket),_sslContext), _requests, _manager, _maxID));
				_sessions.back()->readHandshake();
				_maxID++;
            }

            accept();
        });
}

SSLServer::~SSLServer()
{
	terminate();
	_stopWorker = true;
}

void SSLServer::terminate()
{
	_stopWorker = true;
	while (!_isStopped){}
	_context.stop();
}
