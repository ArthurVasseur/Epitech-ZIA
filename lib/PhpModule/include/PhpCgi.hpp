/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** PhpCgi
*/

#ifndef PHPCGI_HPP_
#define PHPCGI_HPP_

#include <string>
#include "ziapi/Module.hpp"

class PhpCgi : public ziapi::IHandlerModule
{
public:
	PhpCgi() = default;

	~PhpCgi() override = default;

	void Init(const ziapi::config::Node& cfg) override;

	[[nodiscard]] ziapi::Version GetVersion() const noexcept override;

	[[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;

	[[nodiscard]] const char* GetName() const noexcept override;

	[[nodiscard]] const char* GetDescription() const noexcept override;

	void Handle(ziapi::http::Context& ctx, const ziapi::http::Request& req, ziapi::http::Response& res) override;

	[[nodiscard]] double GetHandlerPriority() const noexcept override;

	[[nodiscard]] bool ShouldHandle(const ziapi::http::Context& ctx, const ziapi::http::Request& req) const override;
	ziapi::http::Response parse(const std::string &str);

private:
	std::string _cgiPath;
	std::string _filesPath;
	std::string _defaultPage;
};

#endif /* !PHPCGI_HPP_ */
