/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Proxy
*/

#include <iostream>

#include "dylib/dylib.hpp"
#include "ziapi/Logger.hpp"
#include "Proxy.hpp"
#include "HttpRequest.hpp"


void Proxy::Init(const ziapi::config::Node& config)
{
	try
	{
		for (auto& elem: config["modules"].AsDict()["PROXY"]->AsDict())
		{
			_route[elem.first] = elem.second->AsString();
		}
	}
	catch (std::exception &e)
	{
		ziapi::Logger::Error(std::string(GetName()) + " No configuration provided");
	}
}

ziapi::Version Proxy::GetVersion() const noexcept
{
	return { 1, 0, 0 };
}

ziapi::Version Proxy::GetCompatibleApiVersion() const noexcept
{
	return { 1, 0, 0 };
}

const char* Proxy::GetName() const noexcept
{
	return "Proxy";
}

const char* Proxy::GetDescription() const noexcept
{
	return "proxy";
}

void Proxy::Handle(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res)
{
	HttpRequest::make(req.target, res, _route);
	res.fields["Content-Length"] = std::to_string(res.body.length());
	res.fields["Content-Type"] = "text/html";
}

double Proxy::GetHandlerPriority() const noexcept
{
	return 0.5;
}

bool Proxy::ShouldHandle(const ziapi::http::Context&, const ziapi::http::Request& req) const
{
	return std::find_if(_route.begin(), _route.end(), [&req](const std::pair<const std::string, std::string>& elem)
	{
		return req.target.starts_with(elem.first);
	}) != _route.end();
}

DYLIB_API ziapi::IModule* LoadZiaModule()
{
	return new Proxy();
}