/*
** EPITECH PROJECT, 2022
** ZIA
** File description:
** Application
*/

#ifndef ZIA_APPLICATION_HPP
#define ZIA_APPLICATION_HPP

#include <memory>
#include "ConfigLoader.hpp"
#include "Core.hpp"
#include "ziapi/Logger.hpp"

class Application
{
public:
	explicit Application(const std::string &path);
	Application();

	Application(Application&&) = delete;

	Application(const Application&) = delete;

	Application& operator=(Application&&) = delete;

	Application& operator=(const Application&) = delete;

	~Application() = default;
	void run();
	static Application* Instance;
private:
	void startWithArgs(const std::string &path);
	std::string _path;
	std::thread _shellWorker;
	std::unique_ptr<Core> _core;
	std::shared_ptr<ModuleLoader> _ml;
};


#endif //ZIA_APPLICATION_HPP
