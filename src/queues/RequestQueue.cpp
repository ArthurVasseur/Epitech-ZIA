/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** RequestQueue
*/

#include "queues/RequestQueue.hpp"
#include <iostream>
void RequestQueue::Push(std::pair<ziapi::http::Request, ziapi::http::Context> &&req)
{
    _requestQueue.push(std::move(req));
}

std::size_t RequestQueue::Size() const noexcept
{
    return _requestQueue.size();
}
