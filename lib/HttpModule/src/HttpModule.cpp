/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** HttpModule
*/

#include "HttpModule.hpp"
#include "dylib/dylib.hpp"
#include "ziapi/Logger.hpp"
#include <iomanip>
#include <fstream>
#include <chrono>
#include <iostream>

static const std::unordered_map<std::string, std::string> getContentTypeByExtention{
	{".html", "text/html"},
	{".css", "text/css"},
	{".scss", "text/scss"},
	{".js", "text/html"},
	{".ico", "image"},
	{".jpg", "image"},
	{".png", "image"},
	{".jpeg", "image"},
	{".woff", "application/font-woff"},
	{".woff2", "application/font-woff"},
	{".ttf", "application/font-ttf"}};

void HttpModule::Init(const ziapi::config::Node &cfg)
{
	try
	{
		filesPath = cfg["modules"].AsDict()["HTTP"]->AsDict()["path"]->AsString();
		defaultPage = cfg["modules"].AsDict()["HTTP"]->AsDict()["defaultPage"]->AsString();
	}
	catch (std::exception &e)
	{
		filesPath = "./www";
		defaultPage = "index.html";
	}
	_getResponseFomMethod = {
		{ziapi::http::method::kGet, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handleGet(std::forward<decltype(PH1)>(PH1),
					   std::forward<decltype(PH2)>(PH2),
					   std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kPost, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handlePost(std::forward<decltype(PH1)>(PH1),
						std::forward<decltype(PH2)>(PH2),
						std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kPut, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handlePut(std::forward<decltype(PH1)>(PH1),
					   std::forward<decltype(PH2)>(PH2),
					   std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kDelete, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handleDelete(std::forward<decltype(PH1)>(PH1),
						  std::forward<decltype(PH2)>(PH2),
						  std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kPatch, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handlePatch(std::forward<decltype(PH1)>(PH1),
						 std::forward<decltype(PH2)>(PH2),
						 std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kOptions, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handleOptions(std::forward<decltype(PH1)>(PH1),
						   std::forward<decltype(PH2)>(PH2),
						   std::forward<decltype(PH3)>(PH3));
		 }},
		{ziapi::http::method::kHead, [this](auto &&PH1, auto &&PH2, auto &&PH3)
		 {
			 handleHead(std::forward<decltype(PH1)>(PH1),
						std::forward<decltype(PH2)>(PH2),
						std::forward<decltype(PH3)>(PH3));
		 }}};
}

ziapi::Version HttpModule::GetVersion() const noexcept
{
	return {1, 0, 0};
}

ziapi::Version HttpModule::GetCompatibleApiVersion() const noexcept
{
	return {1, 0, 0};
}

const char *HttpModule::GetName() const noexcept
{
	return "HttpModule";
}

const char *HttpModule::GetDescription() const noexcept
{
	return "module for http requests";
}

bool HttpModule::ShouldHandle(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const
{
	return std::any_of(getContentTypeByExtention.begin(), getContentTypeByExtention.end(),
					   [&req, this](const std::pair<const std::string, std::string> &item) -> bool
					   {
						   std::error_code error;
						   if (req.target[0] == '/')
							   return true;
						   if (req.target.find(item.first) != std::string::npos)
							   return true;
						   if (std::filesystem::is_directory(filesPath + req.target, error))
							   return true;
						   return false;
					   });
}

void HttpModule::Handle(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	try
	{
		_getResponseFomMethod.at(req.method)(ctx, req, res);
	}
	catch (const std::exception &e)
	{
		ziapi::Logger::Error(std::string(GetName()) + " : unknown request method " + req.method);
		res.reason = ziapi::http::reason::kMethodNotAllowed;
		res.status_code = ziapi::http::Code::kMethodNotAllowed;
	}
}

double HttpModule::GetHandlerPriority() const noexcept
{
	return 0.5;
}

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
	return system_clock::to_time_t(sctp);
}

void HttpModule::handleGet(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	std::string target = req.target;
	if (req.target == "/")
		target = "/" + defaultPage;
	auto filepath = std::filesystem::path(filesPath + target);
	std::error_code error;
	if (std::filesystem::is_directory(filepath, error))
	{
		std::ostringstream ss;
		ss << "<table> <thead> <tr> <th>Name </th> <th>Date of creation </th> <th> Size</th> </tr> </thead> <tbody>";
		for (const auto &entry : std::filesystem::directory_iterator(filepath))
		{
			try
			{
				auto time = to_time_t(entry.last_write_time());
				auto x = std::asctime(std::localtime(&time));
				std::string temp = entry.path().string().substr(filesPath.length(), entry.path().string().length());
				if (entry.is_directory())
				{
					ss << "<tr> <td> <a href= " << temp << ">" << entry.path().filename().string() << "</td> <td>" << x << "</td> <td>   -   </td> </tr>";
				}
				else
				{
					ss << "<tr> <td> <a href= " << temp << ">" << entry.path().filename().string() << "</td> <td>" << x << "</td> <td>  " << entry.file_size() << "  </td> </tr>";
				}
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		ss << "</tbody> </table>";
		res.body = ss.str();
	}
	else
	{
		std::ifstream file_stream(filepath.string());
		if (file_stream.is_open())
		{
			std::ostringstream ss;
			ss << file_stream.rdbuf();
			res.body = ss.str();
		}
		else
		{
			res.status_code = ziapi::http::Code::kNotFound;
			res.reason = ziapi::http::reason::kNotFound;
			return;
		}
	}
	res.status_code = ziapi::http::Code::kOK;
	res.reason = ziapi::http::reason::kOK;
	try
	{
		res.fields["Content-Type"] = getContentTypeByExtention.at(filepath.extension().string());
		res.fields["Content-Length"] = std::to_string(res.body.length());
	}
	catch (const std::exception &e)
	{
		ziapi::Logger::Warning("Unknown Extension : " + filepath.extension().string());
	}
}

void HttpModule::handleHead(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	HttpModule::handleGet(ctx, req, res);
	res.body = "";
}

void HttpModule::handlePost(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	handleGet(ctx, req, res);
}

void HttpModule::handlePut(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	std::ifstream file;
	file.open(filesPath + req.target);
	if (file)
	{
		std::filesystem::remove(filesPath + req.target);
		res.status_code = ziapi::http::Code::kOK;
		res.fields[ziapi::http::header::kETag] = ziapi::http::reason::kOK;
	}
	else
	{
		res.status_code = ziapi::http::Code::kCreated;
		res.fields[ziapi::http::header::kETag] = ziapi::http::reason::kCreated;
	}
	std::ofstream newFile(filesPath + req.target);
	newFile << req.body << std::endl;
	newFile.close();
	res.fields[ziapi::http::header::kContentLocation] = req.target;
}

void HttpModule::handleDelete(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	std::ifstream file;
	file.open(filesPath + req.target);
	if (file)
	{
		std::filesystem::remove(filesPath + req.target);
		res.status_code = ziapi::http::Code::kOK;
		res.fields[ziapi::http::header::kETag] = ziapi::http::reason::kOK;
	}
	else
	{
		res.status_code = ziapi::http::Code::kNoContent;
		res.fields[ziapi::http::header::kETag] = ziapi::http::reason::kNoContent;
	}
}

void HttpModule::handleConnect(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	// nope
}

void HttpModule::handleOptions(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	res.fields[ziapi::http::header::kAllow] = "GET, HEAD, POST, PUT, DELETE, OPTIONS, PATCH";
	res.status_code = ziapi::http::Code::kOK;
	res.reason = ziapi::http::reason::kOK;
}

void HttpModule::handleTrace(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
	// nope
}

void HttpModule::handlePatch(ziapi::http::Context &ctx, const ziapi::http::Request &req, ziapi::http::Response &res)
{
}

DYLIB_API ziapi::IModule *LoadZiaModule()
{
	return new HttpModule;
}
