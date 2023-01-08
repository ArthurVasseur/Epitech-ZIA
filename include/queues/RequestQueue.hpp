/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** RequestQueue
*/

#include <queue>
#include <mutex>
#include "ziapi/Http.hpp"

class RequestQueue : public ziapi::http::IRequestOutputQueue
{
public:
    void Push(std::pair<ziapi::http::Request, ziapi::http::Context> &&req) override;
    [[nodiscard]] std::size_t Size() const noexcept final;
protected:
    std::queue<std::pair<ziapi::http::Request, ziapi::http::Context>> _requestQueue;
};