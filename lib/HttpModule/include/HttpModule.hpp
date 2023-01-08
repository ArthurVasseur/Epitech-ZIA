/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** HttpModule
*/

#ifndef HTTPMODULE_HPP_
#define HTTPMODULE_HPP_

#include <filesystem>
#include <fstream>
#include <functional>
#include "ziapi/Config.hpp"
#include "ziapi/Module.hpp"

class HttpModule : public ziapi::IHandlerModule
{
public:
	HttpModule() = default;

	~HttpModule() override = default;

	void Init(const ziapi::config::Node& cfg) override;

	[[nodiscard]] ziapi::Version GetVersion() const noexcept override;

	[[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;

	[[nodiscard]] const char* GetName() const noexcept override;

	[[nodiscard]] const char* GetDescription() const noexcept override;

	[[nodiscard]] bool ShouldHandle(const ziapi::http::Context& ctx, const ziapi::http::Request& req) const override;

	void Handle(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res) override;

	[[nodiscard]] double GetHandlerPriority() const noexcept override;

	void handleGet(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handleHead(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handlePost(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handlePut(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handleDelete(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handleConnect(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handleOptions(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handleTrace(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);
	void handlePatch(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res);

private:
	std::string filesPath;
	std::string defaultPage;
	std::unordered_map<std::string, std::function<void(ziapi::http::Context&, const ziapi::http::Request&, ziapi::http::Response&)>> _getResponseFomMethod;
};

#endif /* !HTTPMODULE_HPP_ */
