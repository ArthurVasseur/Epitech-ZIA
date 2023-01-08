/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** PhpCgi
*/

#include <iostream>
#include <filesystem>
#include <locale>

#include "subprocess.hpp"
#include "dylib/dylib.hpp"
#include "PhpCgi.hpp"
#include "ziapi/Logger.hpp"

#ifndef _MSC_VER
#define	CONVERT
#else
#define CONVERT(x) std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(x)
#endif

void PhpCgi::Init(const ziapi::config::Node& config)
{
	try {
	_cgiPath = config["modules"].AsDict()["PHP-CGI"]->AsDict()["cgiPath"]->AsString();
	_filesPath = config["modules"].AsDict()["PHP-CGI"]->AsDict()["path"]->AsString();
	_defaultPage = config["modules"].AsDict()["PHP-CGI"]->AsDict()["defaultPage"]->AsString();
	}
	catch (std::exception &e)
	{
		_cgiPath = "/usr/bin/php-cgi";
		_filesPath = "./www";
		_defaultPage = "index.php";
	}
}

ziapi::Version PhpCgi::GetVersion() const noexcept
{
	return { 1, 0, 0 };
}

ziapi::Version PhpCgi::GetCompatibleApiVersion() const noexcept
{
	return { 1, 0, 0 };
}

const char* PhpCgi::GetName() const noexcept
{
	return "PhpCgi";
}

const char* PhpCgi::GetDescription() const noexcept
{
	return "php cgi";
}

void PhpCgi::Handle(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res)
{
	std::string target = req.target;
	if (req.target == "/")
		target = "/" + _defaultPage;
	try
	{
		std::string queryStr;
		auto pos = req.target.find('?');
		if (pos != std::string::npos)
		{
			queryStr = req.target.substr(pos + 1, req.target.length());
			target = req.target.substr(0, pos);
		}
		const auto filepath = std::filesystem::path(_filesPath + target);
		subprocess::environment environment = {{
													   { CONVERT("AUTH_TYPE"), CONVERT("") },
													   { CONVERT("CONTENT_LENGTH"), CONVERT(std::to_string(req.body.size()))},
													   { CONVERT("GATEWAY_INTERFACE"), CONVERT("CGI/1.1") },
													   { CONVERT("PATH_INFO"), CONVERT(filepath.string()) },
													   { CONVERT("PATH_TRANSLATED"), CONVERT("") },
													   { CONVERT("QUERY_STRING"), CONVERT(queryStr) },
													   { CONVERT("REMOTE_ADDR"), CONVERT("127.0.0.1") },
													   { CONVERT("REMOTE_HOST"), CONVERT("127.0.0.1") },
													   { CONVERT("REMOTE_IDENT"), CONVERT("") },
													   { CONVERT("REMOTE_USER"), CONVERT("") },
													   { CONVERT("REQUEST_METHOD"), CONVERT(req.method) },
													   { CONVERT("SCRIPT_NAME"), CONVERT(filepath.string()) },
													   { CONVERT("SERVER_NAME"), CONVERT("zia") },
													   { CONVERT("SERVER_PORT"), CONVERT(std::any_cast<std::string>(ctx["client.socket.port"])) },
													   { CONVERT("SERVER_PROTOCOL"), CONVERT("HTTP/1.1") },
													   { CONVERT("SERVER_SOFTWARE"), CONVERT("") },
													   { CONVERT("SCRIPT_FILENAME"), CONVERT(filepath.string()) },
													   { CONVERT("REDIRECT_STATUS"), CONVERT("200") },
													   { CONVERT("CONTENT_TYPE"), CONVERT("application/x-www-form-urlencoded")}
											   }};
		for (auto& pair: req.fields)
		{
			std::string str = pair.first;
			std::transform(str.begin(), str.end(), str.begin(), toupper);
			std::replace(str.begin(), str.end(), '-', '_');
			environment.env_[CONVERT(std::string("HTTP_") + str)] = CONVERT(pair.second);
		}

		std::string result;
		if (req.method == ziapi::http::method::kPost)
		{
			auto echo = subprocess::Popen({ "echo", req.body }, subprocess::output{ subprocess::PIPE });
			auto cgi = subprocess::Popen({ _cgiPath, filepath.string() },
					subprocess::input{ echo.output() }, subprocess::output{ subprocess::IOTYPE::PIPE },
					subprocess::environment{ environment });
			result = cgi.communicate().first.buf.data();
		}
		else
		{
			auto cgi = subprocess::Popen({ _cgiPath, filepath.string() },
					subprocess::output{ subprocess::IOTYPE::PIPE },
					subprocess::environment{ environment });
			result = cgi.communicate().first.buf.data();
		}
		std::string body = result.substr(result.find("\r\n\r\n") + 4);
		res.body = body;
		std::string headers = result.substr(0, result.find("\r\n\r\n"));
		res.fields["Content-Type"] = "text/html";
		res.fields["Content-Length"] = std::to_string(res.body.length());
	}
	catch (const std::exception& e)
	{
		ziapi::Logger::Error(e.what());
	}
}

double PhpCgi::GetHandlerPriority() const noexcept
{
	return 0.5;
}

bool PhpCgi::ShouldHandle(const ziapi::http::Context&, const ziapi::http::Request& req) const
{
	std::string queryStr;
	auto pos = req.target.find('?');
	if (pos != std::string::npos)
	{
		queryStr = req.target.substr(0, pos);
	}
	else queryStr = req.target;
	return queryStr.ends_with(".php") &&
		   (req.method == ziapi::http::method::kGet || req.method == ziapi::http::method::kPost ||
			req.method == ziapi::http::method::kHead);
}

ziapi::http::Response PhpCgi::parse(const std::string &str)
{
	ziapi::http::Response response;
	std::string delim = "\r\n";
	std::size_t pos;
	std::string token;
	std::string data = str;
	auto statusPos = str.find("Status: ") + 8;
	std::string code = str.substr(statusPos, 3);
	auto firstLineEnd = str.find(delim);
	try
	{
		response.status_code = (ziapi::http::Code)std::stoi(code);
		response.reason = str.substr(statusPos + 4, firstLineEnd - (statusPos + 4));
	}
	catch (const std::exception &e)
	{
		response.status_code = ziapi::http::Code::kOK;
		response.reason = ziapi::http::reason::kOK;
	}
	if ((pos = data.find(delim)) == std::string::npos)
	{
		token = data.substr(0, pos);
		size_t del = token.find(':');
		if (del != std::string::npos)
		{
			response.fields[token.substr(0, del)] = token.substr(del + 2, token.length() - 1);
		}
	}
	while ((pos = data.find(delim)) != std::string::npos)
	{
		token = data.substr(0, pos);
		size_t del = token.find(':');
		if (del != std::string::npos)
		{
			response.fields[token.substr(0, del)] = token.substr(del + 2, token.length() - 1);
		}
		data.erase(0, pos + delim.length());
		if (data.substr(0, 3) == "\r\n\r")
		{
			data.erase(0, 3);
			break;
		}
	}
	return response;
}

DYLIB_API ziapi::IModule* LoadZiaModule()
{
	return new PhpCgi();
}