/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** HttpRequest
*/

#include "HttpRequest.hpp"
#include <iostream>
#include <array>

void HttpRequest::make(const std::string& target, ziapi::http::Response& res,
		const std::unordered_map<std::string, std::string>& route)
{
	asio::io_service io_service;
	asio::ip::tcp::resolver resolver(io_service);
	std::string base = target.substr(0, target.find('/', 1));
	auto pos = target.find('/', 1);
	std::string strQuery;
	if (pos == std::string::npos) strQuery = "";
	else strQuery = target.substr(pos, target.length());
	if (base.empty()) base = target;
	if (route.find(base) == route.end() || route.at(base).find(':') == std::string::npos)
	{
		res.reason = ziapi::http::reason::kNotFound;
		res.status_code = ziapi::http::Code::kNotFound;
		return;
	}
	auto& str = route.at(base);
	pos = str.find(':');
	asio::ip::tcp::resolver::query query(str.substr(0, pos), str.substr(pos + 1, str.length()));
	asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
	asio::ip::tcp::endpoint endpoint = iterator->endpoint();
	asio::ip::tcp::socket socket(io_service);
	asio::connect(socket, iterator);
	std::string request = "GET /" + strQuery + " HTTP/1.1\r\n";
	request += "Host: 127.0.0.1\r\n";
	request += "Accept: */*\r\n";
	request += "Connection: close\r\n\r\n";
	asio::write(socket, asio::buffer(request));
	asio::streambuf response;
	asio::read_until(socket, response, "\r\n");
	std::istream response_stream(&response);
	std::string http_version;
	response_stream >> http_version;
	unsigned int status_code;
	response_stream >> status_code;
	if (status_code != 200)
	{
		res.status_code = (ziapi::http::Code)status_code;
		return;
	}
	asio::read_until(socket, response, "\r\n\r\n");
	std::string header;
	while (std::getline(response_stream, header) && header != "\r")
	{
		std::size_t del = header.find(':');
		if (del != std::string::npos)
		{
			res.fields[header.substr(0, del)] = header.substr(del + 2, header.length() - 1);
		}
	}
	std::string s(std::istreambuf_iterator<char>(response_stream), {});
	res.body = s;
	res.status_code = ziapi::http::Code::kOK;
	res.reason = ziapi::http::reason::kOK;
}
