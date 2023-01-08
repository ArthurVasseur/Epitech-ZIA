/*
** EPITECH PROJECT, 2022
** ZIA
** File description:
** Application
*/

#include "Application.hpp"
#include "ShellInterpreter.hpp"

Application* Application::Instance = nullptr;

Application::Application(const std::string& path) : _path(path)
{
	Instance = this;
	startWithArgs(path);
}

Application::Application()
{
	Instance = this;
	_ml = std::make_shared<ModuleLoader>();
	_core = std::make_unique<Core>(_ml);
}

void Application::run()
{
	_shellWorker = std::thread([this]()
	{
		ShellInterpreter interpreter(_ml);
		interpreter.run();
		std::cout << "stop4455" << std::endl;
	});
	_core->run();
}

void Application::startWithArgs(const std::string& path)
{
	try
	{
		ConfigLoader loader(path);
		_ml = std::make_unique<ModuleLoader>(loader.getConfig());
		_core = std::make_unique<Core>(_ml);
	}
	catch (const std::exception &e)
	{
		ziapi::Logger::Error(e.what());
		ziapi::Logger::Error("Loading default configuration");
		_ml = std::make_unique<ModuleLoader>();
		_core = std::make_unique<Core>(_ml);
	}
}
