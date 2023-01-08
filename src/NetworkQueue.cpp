/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** NetworkQueue
*/

#include "NetworkQueue.hpp"

void NetworkQueue::pushNewResponse(std::pair<ziapi::http::Response, ziapi::http::Context> &&req)
{
    _responseQueue.push(std::move(req));
}

std::optional<std::pair<ziapi::http::Request, ziapi::http::Context>> NetworkQueue::popNewRequest()
{
	if (_requestQueue.empty())
		return {};
    auto x = _requestQueue.front();
    _requestQueue.pop();
    return {x};
}