//
// Created by arthur on 01/03/2022.
//


#include "ShellInterpreter.hpp"
#include "ziapi/Logger.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <csignal>
#include "Application.hpp"

static const std::unordered_map<std::string, std::function<void(const std::vector<std::string>&,
		std::shared_ptr<ModuleLoader>& ml)>> commandMap =
		{
				{ "-",      [](const std::vector<std::string>& args, std::shared_ptr<ModuleLoader>& ml)
							{
								ml->unloadLibrary(args[1]);
							}},
				{ "+",      [](const std::vector<std::string>& args, std::shared_ptr<ModuleLoader>& ml)
							{
								ml->loadLibrary(args[1], false);
							}},
				{ "~",      [](const std::vector<std::string>& args, std::shared_ptr<ModuleLoader>& ml)
							{
								ml->reloadLibrary(args[1]);
							}},
				{ "ls",     [](const std::vector<std::string>& args, std::shared_ptr<ModuleLoader>& ml)
							{
								auto preProcessModules = ml->getAll<ziapi::IPreProcessorModule>();
								auto postProcessModules = ml->getAll<ziapi::IPostProcessorModule>();
								auto handlerModules = ml->getAll<ziapi::IHandlerModule>();
								auto networkModules = ml->getAll<ziapi::INetworkModule>();
								auto printInfo = [&args](ziapi::IModule& mod)
								{
									std::cout << '\t' << mod.GetName();
									if (std::find(args.begin(), args.end(), "-d") != args.end())
									{
										std::cout << "\n\t\tDescription " << mod.GetDescription();
									}
									if (std::find(args.begin(), args.end(), "-v") != args.end())
									{
										std::cout << "\n\t\tVersion " << mod.GetVersion().major << '.'
												  << mod.GetVersion().minor << '.' << mod.GetVersion().patch;
									}
									std::cout << std::endl;
								};
								std::cout << "PreProcessor Modules : " << std::endl;
								std::for_each(preProcessModules.begin(), preProcessModules.end(),
										[&printInfo](std::shared_ptr<ziapi::IPreProcessorModule>& mod)
										{
											printInfo(static_cast<ziapi::IModule&>(*mod));
										});
								std::cout << "PostProcessor Modules : " << std::endl;
								std::for_each(postProcessModules.begin(), postProcessModules.end(),
										[&printInfo](std::shared_ptr<ziapi::IPostProcessorModule>& mod)
										{
											printInfo(static_cast<ziapi::IModule&>(*mod));
										});
								std::cout << "Handler Modules : " << std::endl;
								std::for_each(handlerModules.begin(), handlerModules.end(),
										[&printInfo](std::shared_ptr<ziapi::IHandlerModule>& mod)
										{
											printInfo(static_cast<ziapi::IModule&>(*mod));
										});
								std::cout << "Network Modules : " << std::endl;
								std::for_each(networkModules.begin(), networkModules.end(),
										[&printInfo](std::shared_ptr<ziapi::INetworkModule>& mod)
										{
											printInfo(static_cast<ziapi::IModule&>(*mod));
										});
							}}
		};

ShellInterpreter::ShellInterpreter(std::shared_ptr<ModuleLoader>& ml) : _ml(ml)
{
}

void ShellInterpreter::run()
{
	std::string command;
	while (command != "stop")
	{
		GetCommand(command);
	}
}

std::vector<std::string> ShellInterpreter::split(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string line;
	while (std::getline(ss, line, delimiter))
	{
		tokens.push_back(line);
	}
	return tokens;
}

void ShellInterpreter::GetCommand(std::string& command)
{
	std::vector<std::string> splitCommand;

	std::getline(std::cin, command);

	splitCommand = split(command, ' ');
	try
	{
		commandMap.at(splitCommand[0])(splitCommand, _ml);
	}
	catch (const std::exception& e)
	{
		ziapi::Logger::Error("Unknown command");
	}
}