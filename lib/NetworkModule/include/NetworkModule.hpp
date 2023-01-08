/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** NetworkModule
*/

#ifndef NETWORKMODULE_HPP_
#define NETWORKMODULE_HPP_
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include "ziapi/Module.hpp"
#include "TCPServer.hpp"
class NetworkModule : public ziapi::INetworkModule
{
    public:
        NetworkModule();
        ~NetworkModule() override;

        void Init(const ziapi::config::Node &cfg) override;
        [[nodiscard]] ziapi::Version GetVersion() const noexcept override;

        [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;

        [[nodiscard]] const char *GetName() const noexcept override;

        [[nodiscard]] const char *GetDescription() const noexcept override;
        void Run(ziapi::http::IRequestOutputQueue &requests, ziapi::http::IResponseInputQueue &responses) override;

        void Terminate() override;
    private:
        int _port;
        std::string _listening;
        std::unique_ptr<TCPServer> _tcpServer;
        std::unique_ptr<std::thread> _worker;
		std::atomic_bool _stop;
};

#endif /* !NETWORKMODULE_HPP_ */
