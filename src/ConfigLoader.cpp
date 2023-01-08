/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ConfigLoader
*/

#include "ConfigLoader.hpp"
#include <vector>
ConfigLoader::ConfigLoader(const std::string &configPath) : _config(getConfig(configPath))
{
}

std::shared_ptr<ziapi::config::Node> ConfigLoader::getConfig(const std::string &configPath)
{
    std::ifstream t(configPath);
    std::stringstream ss;
    ss << t.rdbuf();
    auto tt = ss.str();
    nlohmann::json j;
    ss >> j;
    ziapi::config::Dict dic;
    auto x = j.get<nlohmann::json::object_t>();
    for(auto &i : x)
    {
        if (i.second.is_array())
        {
            ziapi::config::Dict arrayElements = getArray(i.second);
            dic[i.first] = std::make_shared<ziapi::config::Node>(arrayElements);
        }
        if (i.second.is_primitive())
        {
            dic[i.first] = getObject(i.second);
        }

    }
    return std::make_shared<ziapi::config::Node>(dic);
}

ziapi::config::Dict ConfigLoader::getArray(nlohmann::json &items)
{
    ziapi::config::Dict array;

    for (auto &item : items)
    {
        switch (item.type())
        {
        case nlohmann::json::value_t::object:
        {
            auto obj = item.get<nlohmann::json::object_t>();
            ziapi::config::Dict element;
            for(auto &i : obj)
            {
                array[i.first] = getObject(i.second);
            }
            break;
        }
        default:
            break;
        }
    }
    return array;
}

std::shared_ptr<ziapi::config::Node> ConfigLoader::getObject(const nlohmann::json &json)
{
    auto items = json.items();
    if(json.is_primitive())
    {
        return getLiteralValue(json.items().begin());
    }
    if (json.type() == nlohmann::json::value_t::array)
    {
        auto a = getArray(const_cast<nlohmann::json&>(json));
        return std::make_shared<ziapi::config::Node>(a);
    }
    ziapi::config::Dict dict;
    for (auto &item : items)
    {
        dict[item.key()] = getValue(item);
    }
    return std::make_shared<ziapi::config::Node>(dict);
}

std::shared_ptr<ziapi::config::Node> ConfigLoader::getValue(const nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<const nlohmann::json>> &item)
{
    std::shared_ptr<ziapi::config::Node> obj(nullptr);
    if (item.value().type() != nlohmann::json::value_t::array && item.value().type() != nlohmann::json::value_t::object)
    {
        obj = getLiteralValue(item);
    }
    else
    {
        obj = getObject(item.value());
    }
    return obj;
}

std::shared_ptr<ziapi::config::Node> ConfigLoader::getLiteralValue(const nlohmann::detail::iteration_proxy_value<nlohmann::detail::iter_impl<const nlohmann::json>> &item)
{
    switch (item.value().type())
    {
    case nlohmann::json::value_t::number_integer:
        return std::make_shared<ziapi::config::Node>(item.value().items().begin().value().get<int>());
    case nlohmann::json::value_t::number_float:
        return  std::make_shared<ziapi::config::Node>(item.value().items().begin().value().get<float>());
    case nlohmann::json::value_t::string:
        return  std::make_shared<ziapi::config::Node>(item.value().items().begin().value().get<std::string>());
    case nlohmann::json::value_t::number_unsigned:
        return  std::make_shared<ziapi::config::Node>((int)item.value().items().begin().value().get<unsigned int>());
    default:
        break;
    }
    return  std::make_shared<ziapi::config::Node>();
}