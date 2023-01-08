/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ConfigLoader
*/

#ifndef CONFIGLOADER_HPP_
#define CONFIGLOADER_HPP_
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "ziapi/Config.hpp"
class ConfigLoader
{
public:
    explicit ConfigLoader(const std::string &configPath);
    ~ConfigLoader() = default;
    [[nodiscard]] const std::shared_ptr<ziapi::config::Node> getConfig() const { return _config; }

private:
    std::shared_ptr<ziapi::config::Node> getConfig(const std::string &configPath);
    std::shared_ptr<ziapi::config::Node> getObject(const nlohmann::json &json);
    std::shared_ptr<ziapi::config::Node> getValue(const nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<const nlohmann::json>> &item);
    std::shared_ptr<ziapi::config::Node> getLiteralValue(const nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<const nlohmann::json>> &item);
    ziapi::config::Dict getArray(nlohmann::json &items);
	std::shared_ptr<ziapi::config::Node> _config;
};

#endif /* !CONFIGLOADER_HPP_ */
