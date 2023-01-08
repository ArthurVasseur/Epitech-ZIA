/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Proxy
*/

#ifndef PROXY_HPP_
#define PROXY_HPP_

#include <string>
#include "ziapi/Module.hpp"

class Proxy : public ziapi::IHandlerModule
{
public:
	Proxy() = default;

	~Proxy() override = default;

	void Init(const ziapi::config::Node& cfg) override;

	[[nodiscard]] ziapi::Version GetVersion() const noexcept override;

	[[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;

	[[nodiscard]] const char* GetName() const noexcept override;

	[[nodiscard]] const char* GetDescription() const noexcept override;

	void Handle(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res) override;

	[[nodiscard]] double GetHandlerPriority() const noexcept override;

	[[nodiscard]] bool ShouldHandle(const ziapi::http::Context& ctx, const ziapi::http::Request& req) const override;

private:
	std::unordered_map<std::string, std::string> _route;


};

#endif /* !PROXY_HPP_ */
