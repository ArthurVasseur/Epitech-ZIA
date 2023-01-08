/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ResponseQueue
*/

#ifndef ZIA_RESPONSEQUEUE_HPP
#define ZIA_RESPONSEQUEUE_HPP
#include <queue>
#include <mutex>
#include "ziapi/Http.hpp"

class ResponseQueue : public ziapi::http::IResponseInputQueue
{
public:
    std::optional<std::pair<ziapi::http::Response, ziapi::http::Context>> Pop() override;
    [[nodiscard]] std::size_t Size() const noexcept final;

protected:
    std::queue<std::pair<ziapi::http::Response, ziapi::http::Context>> _responseQueue;
};

#endif //ZIA_RESPONSEQUEUE_HPP
