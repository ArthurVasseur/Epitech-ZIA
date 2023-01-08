/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** HttpRequest
*/

#ifndef ZIA_HTTPREQUEST_HPP
#define ZIA_HTTPREQUEST_HPP

#include "asio.hpp"
#include "ziapi/Http.hpp"

class HttpRequest
{
public:
	HttpRequest() = delete;

	~HttpRequest() = delete;

	static void make(const std::string& target, ziapi::http::Response& res,
			const std::unordered_map<std::string, std::string>& route);
};


#endif /* !HTTP_REQUEST_HPP_ */
