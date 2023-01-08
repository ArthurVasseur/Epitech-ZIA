/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Session
*/

#include "Session.hpp"
#include "ziapi/Http.hpp"
#include "ziapi/Logger.hpp"
#include "SessionManager.hpp"

Session::Session(asio::ssl::stream<asio::ip::tcp::socket> socket, ziapi::http::IRequestOutputQueue& requests,
		SessionManager& manager, std::size_t id) : _socket(std::move(socket)), _requests(requests), _manager(manager),
												   _id(id)
{
	ziapi::Logger::Info("New connection from " + _socket.lowest_layer().remote_endpoint().address().to_string());
}

void Session::readHandshake()
{
	checkHandshake();
}

void Session::checkHandshake()
{
	auto self = shared_from_this();
	_socket.async_handshake(asio::ssl::stream_base::server,
			[this, self](const asio::error_code& error)
			{
				if (!error)
				{
					read();
					return;
				}
				else if (error.value() == 336130204)
				{
					ziapi::Logger::Info("SSLModule : Receive HTTP instead of HTTPS");
				}
				else
				{
					ziapi::Logger::Info("SSLModule : ", error.message());
				}
				_socket.lowest_layer().close();
			});
}

ziapi::http::Request Session::parse()
{
	ziapi::http::Request request;
	std::string data = _buffer.data();
	std::string delim = "\r\n";
	std::size_t pos;
	std::string token;
	while ((pos = data.find(delim)) != std::string::npos)
	{
		token = data.substr(0, pos);
		if (token.find("HTTP/") != std::string::npos)
		{
			std::size_t d = token.find(' ');
			request.method = token.substr(0, d);
			token.erase(0, d + 1);
			request.target = token.substr(0, token.find(' '));
		}
		std::size_t del = token.find(':');
		if (del != std::string::npos)
		{
			request.fields[token.substr(0, del)] = token.substr(del + 2, token.length() - 1);
		}
		data.erase(0, pos + delim.length());
		if (data.substr(0, 3) == "\r\n\r")
		{
			data.erase(0, 3);
			break;
		}
	}
	if (data.length() == 0)
		request.body = "";
	else
		request.body = data;
	return request;
}

void Session::read()
{
	auto self = shared_from_this();
	_socket.async_read_some(asio::buffer(_buffer),
			[this, self](const std::error_code& ec, std::size_t length)
			{
				if (!ec)
				{
					auto req = parse();
					ziapi::http::Context ctx;
					ctx.insert(std::make_pair(std::string("client.socket.id"), std::any(_id)));
					ctx["client.socket.address"] = std::any(_socket.lowest_layer().remote_endpoint().address().to_string());
					ctx["client.socket.port"] = std::any(_socket.lowest_layer().remote_endpoint().port());
					if (req.fields.find("Connection") != req.fields.end() && req.fields.at("Connection") == "keep-alive")
					{
						ctx["client.socket.keepAlive"] = std::make_any<bool>(true);
					}
					auto s = std::make_pair(req, ctx);
					_requests.Push(std::forward<std::pair<ziapi::http::Request, ziapi::http::Context>>(s));
					_buffer.fill('\0');
					read();
				}
				else
				{
					_manager.stopAndErase(self);
				}
			});

}

void Session::write(const ziapi::http::Response& res, bool closeSocket)
{
	if (!_socket.lowest_layer().is_open())
		return;
	std::string str = makeHttpResponse(res);
	try
	{
		auto self = shared_from_this();
		std::size_t writeSize = 0;
		while (writeSize != str.size())
		{
			if(writeSize + 8192 > str.size())
				writeSize += _socket.write_some(asio::buffer(str.data() + writeSize, str.size() - writeSize));
			else writeSize += _socket.write_some(asio::buffer(str.data() + writeSize, 8192));
		}
//				if (closeSocket)
//				{
//					_manager.stopAndErase(self);
//				}
		_manager.stopAndErase(self);
	}
	catch (const std::exception &e)
	{
		ziapi::Logger::Error(e.what());
	}
}

void Session::setExpired()
{
	asio::error_code e;
	_socket.shutdown(e);
}

std::string Session::makeHttpResponse(const ziapi::http::Response &res)
{
	std::string str;
	str += "HTTP/1.1 " + std::to_string((int)res.status_code) + " " + res.reason + "\r\n";
	std::for_each(res.fields.begin(), res.fields.end(), [&str](const std::pair<std::string, std::string>& value)
	{
		if (value.first.empty() || value.second.empty())
			return;
		str += value.first + ": " + value.second + "\r\n";
	});
	str += "\r\n";
	str += res.body;
	return str;
}