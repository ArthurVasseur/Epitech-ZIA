/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ModuleLoader
*/

#include "ModuleLoader.hpp"
#include "ziapi/Logger.hpp"

ModuleLoader::ModuleLoader(const std::shared_ptr<ziapi::config::Node> &config) : _modulesPath(getPath(config)), _update(false), _config(config)
{
	loadAll();
	for (auto& mod: _modules)
	{
		auto& c = *config;
		mod->Init(c);
	}
}

ModuleLoader::ModuleLoader() : _modulesPath("./build/lib"), _update(false), _config(std::make_shared<ziapi::config::Node>(
		nullptr))
{
	loadAll();
	for (auto& mod: _modules)
	{
		mod->Init(nullptr);
	}
}

std::string ModuleLoader::getPath(const std::shared_ptr<ziapi::config::Node> &config)
{
	return (*config)["modulesPath"].AsString();
}

void ModuleLoader::loadAll()
{
	for (const auto& entry: std::filesystem::directory_iterator(_modulesPath))
	{
		if (entry.is_directory())
			continue;
		loadLibrary(entry.path().string());
	}
}

void ModuleLoader::loadLibrary(const std::string& path, bool absolutePath)
{
	try
	{
		if (absolutePath)
			_modules.emplace_back(path);
		else _modules.emplace_back(_modulesPath + "/" + path + dylib::extension);
		_modules.back()->Init(*_config);
		_update = true;
	}
	catch (const std::exception& e)
	{
		ziapi::Logger::Error(e.what());
	}
}

void ModuleLoader::reloadLibrary(const std::string& name)
{
	std::for_each(_modules.begin(), _modules.end(), [&name, this](ZiaLibraryInstance& instance)
	{
		if (instance->GetName() == name)
		{
			instance.reload();
			instance->Init(*_config);
			_update = true;
		}
	});
}

void ModuleLoader::unloadLibrary(const std::string& name)
{
	_toBeDestroyed.push_back(name);
	_update = true;
}

bool ModuleLoader::flush()
{
	std::for_each(_toBeDestroyed.begin(), _toBeDestroyed.end(), [this](const std::string& name)
	{
		_modules.erase(
				std::remove_if(_modules.begin(), _modules.end(), [&name](ZiaLibraryInstance& instance)
				{
					return instance->GetName() == name;
				}), _modules.end());
	});
	_toBeDestroyed.clear();
	if (_update)
	{
		_update = false;
		return true;
	}
	return false;
}
