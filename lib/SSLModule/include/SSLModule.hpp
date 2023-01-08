/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** SSLModule
*/

#ifndef PHPCGI_HPP_
#define PHPCGI_HPP_
#include "ziapi/Module.hpp"
#include <memory>
#include <thread>
#include "SSLServer.hpp"

class SSLModule : public ziapi::INetworkModule
{
public:
    SSLModule() : _worker(nullptr), _SSLServer(nullptr) {}
    ~SSLModule() override;

    void Init(const ziapi::config::Node &cfg) override;
    [[nodiscard]] ziapi::Version GetVersion() const noexcept override;
    [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;
    [[nodiscard]] const char *GetName() const noexcept override;
    [[nodiscard]] const char *GetDescription() const noexcept override;
    void Run(ziapi::http::IRequestOutputQueue &requests, ziapi::http::IResponseInputQueue &responses) override;
    void Terminate() override;

protected:
private:
    int _port{};
    std::string _listening;
    std::string _keyPath;
    std::unique_ptr<SSLServer> _SSLServer;
    std::unique_ptr<std::thread> _worker;
};

#endif /* !SSLModule_HPP_ */
