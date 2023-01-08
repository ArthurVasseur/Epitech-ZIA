/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include "ziapi/Config.hpp"
#include "ModuleLoader.hpp"
#include "ziapi/Module.hpp"
#include "ziapi/Http.hpp"
#include "NetworkQueue.hpp"

class Core
{
public:
	explicit Core(std::shared_ptr<ModuleLoader>& ml);

	~Core() = default;

	void run();

private:
	std::shared_ptr<ModuleLoader> _ml;
	std::vector<std::shared_ptr<ziapi::IPreProcessorModule>> _preProcessModules;
	std::vector<std::shared_ptr<ziapi::IPostProcessorModule>> _postProcessModules;
	std::vector<std::shared_ptr<ziapi::IHandlerModule>> _handlerModules;
	std::unordered_map<std::shared_ptr<ziapi::INetworkModule>, NetworkQueue> _networkModules;
	std::atomic_bool _isRunning;

	void getModules();
};

#endif /* !CORE_HPP_ */
