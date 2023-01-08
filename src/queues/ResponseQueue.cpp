/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ResponseQueue
*/

#include "queues/ResponseQueue.hpp"


std::size_t ResponseQueue::Size() const noexcept
{
    return _responseQueue.size();
}
std::optional<std::pair<ziapi::http::Response, ziapi::http::Context>> ResponseQueue::Pop()
{
    if (Size() == 0)
        return {};
    auto res = _responseQueue.front();
    _responseQueue.pop();
    return res;
}
