/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** SSLModule
*/
#include "dylib/dylib.hpp"
#include "SSLModule.hpp"
#include "ziapi/Logger.hpp"

void SSLModule::Init(const ziapi::config::Node &config)
{
    try
    {
        _port = config["modules"].AsDict()["SSL"]->AsDict()["port"]->AsInt();
        _listening = config["modules"].AsDict()["SSL"]->AsDict()["listening"]->AsString();
        _keyPath = config["modules"].AsDict()["SSL"]->AsDict()["keyPath"]->AsString();
    }
    catch (std::exception &e)
    {
        _port = 8443;
        _listening = "0.0.0.0";
        _keyPath = "./ssl";
    }
}

ziapi::Version SSLModule::GetVersion() const noexcept
{
    return {1, 0, 0};
}

ziapi::Version SSLModule::GetCompatibleApiVersion() const noexcept
{
    return {1, 0, 0};
}

const char *SSLModule::GetName() const noexcept
{
    return "SSLModule";
}

const char *SSLModule::GetDescription() const noexcept
{
    return "SSL Module";
}

void SSLModule::Run(ziapi::http::IRequestOutputQueue &requests, ziapi::http::IResponseInputQueue &responses)
{
	if (_SSLServer && _worker)
		return;
    try
    {
        _SSLServer = std::make_unique<SSLServer>(_port, _listening, _keyPath, requests, responses);
    }
    catch (...)
    {
        while (true)
        {
            try
            {
                _port++;
                _SSLServer = std::make_unique<SSLServer>(_port, _listening, _keyPath, requests, responses);
                break;
            }
            catch (...)
            {
            }
        }
    }
    ziapi::Logger::Info("SSLModule working on port : " + std::to_string(_port));
    _worker = std::make_unique<std::thread>([this]()
                                            { _SSLServer->run(); });
}

void SSLModule::Terminate()
{
	_SSLServer->terminate();
	_worker->join();
//    _worker.reset();
//    _SSLServer.reset();
}

SSLModule::~SSLModule()
{
    _SSLServer->terminate();
//	_worker->join();
}

DYLIB_API ziapi::IModule *LoadZiaModule()
{
    return new SSLModule;
}