/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** NetworkQueue
*/

#ifndef ZIA_NETWORKQUEUE_HPP
#define ZIA_NETWORKQUEUE_HPP

#include <queue>
#include "ziapi/Http.hpp"
#include "queues/RequestQueue.hpp"
#include "queues/ResponseQueue.hpp"

class NetworkQueue : public RequestQueue, public ResponseQueue
{
public:
    NetworkQueue() = default;
    ~NetworkQueue() override = default;
	NetworkQueue(const NetworkQueue&) = default;
	NetworkQueue(NetworkQueue&&) = default;
	NetworkQueue& operator=(NetworkQueue&&) = default;
	NetworkQueue& operator=(const NetworkQueue&) = delete;
    void pushNewResponse(std::pair<ziapi::http::Response, ziapi::http::Context> &&req);
    std::optional<std::pair<ziapi::http::Request, ziapi::http::Context>> popNewRequest();

private:

};

#endif //ZIA_NETWORKQUEUE_HPP
