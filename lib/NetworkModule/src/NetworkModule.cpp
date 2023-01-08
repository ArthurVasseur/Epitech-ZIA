/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** NetworkModule
*/

#include <mutex>
#include "dylib/dylib.hpp"
#include "NetworkModule.hpp"
#include "TCPServer.hpp"
#include "ziapi/Logger.hpp"
#include <iostream>
NetworkModule::NetworkModule()
    : _port(0), _listening({}), _tcpServer(nullptr), _worker(nullptr), _stop(true)
{
}

void NetworkModule::Init(const ziapi::config::Node &config)
{
    try
    {
        _port = config["modules"].AsDict()["Network"]->AsDict()["port"]->AsInt();
        _listening = config["modules"].AsDict()["Network"]->AsDict()["listening"]->AsString();
    }
    catch (std::exception &e)
    {
        _port = 8080;
        _listening = "0.0.0.0";
    }
}

ziapi::Version NetworkModule::GetVersion() const noexcept
{
    return {1, 0, 0};
}

ziapi::Version NetworkModule::GetCompatibleApiVersion() const noexcept
{
    return {1, 0, 0};
}

const char *NetworkModule::GetName() const noexcept
{
    return "NetworkModule";
}

const char *NetworkModule::GetDescription() const noexcept
{
    return "NetworkModule";
}

void NetworkModule::Run(ziapi::http::IRequestOutputQueue &requests, ziapi::http::IResponseInputQueue &responses)
{
	if(_tcpServer && _worker)
		return;
    try
    {
        _tcpServer = std::make_unique<TCPServer>(_port, _listening, requests, responses);
    }
    catch (...)
    {
        while (true)
        {
            try
            {
                _port++;
                _tcpServer = std::make_unique<TCPServer>(_port, _listening, requests, responses);
                break;
            }
            catch (...)
            {
            }
        }
    }
    ziapi::Logger::Info("NetworkModule working on port : " + std::to_string(_port));
    _worker = std::make_unique<std::thread>([this]()
                                            { _tcpServer->run(); });
}

void NetworkModule::Terminate()
{
	_tcpServer->terminate();
	_worker->join();
//    _worker.reset();
//    _tcpServer.reset();
}

NetworkModule::~NetworkModule()
{
    _tcpServer->terminate();
//	_worker->join();
}

DYLIB_API ziapi::IModule *LoadZiaModule()
{
    return new NetworkModule;
}