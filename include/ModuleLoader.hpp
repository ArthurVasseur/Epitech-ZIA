/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ModuleLoader
*/

#ifndef MODULELOADER_HPP_
#define MODULELOADER_HPP_
#include <memory>
#include <vector>
#include <string>
#include <filesystem>
#include <functional>
#include <map>
#include "ziapi/Module.hpp"
#include "dylib/dylib.hpp"
#include "ZiaLibraryInstance.hpp"

class ModuleLoader
{
public:
    ModuleLoader();
    explicit ModuleLoader(const std::shared_ptr<ziapi::config::Node> &config);
    ~ModuleLoader() = default;
    ModuleLoader(const ModuleLoader &) = default;
    ModuleLoader &operator=(const ModuleLoader &) = default;

    template<typename T>
    std::vector<std::shared_ptr<T>> getAll()
    {
        std::vector<std::shared_ptr<T>> vec;
        for (auto &mod : _modules)
        {
            auto ptr = std::dynamic_pointer_cast<T>(mod.get());
            if (ptr == nullptr)
                continue;
            vec.push_back(ptr);
        }
        return vec;
    }

    void loadLibrary(const std::string &path, bool absolutePath = true);
	void reloadLibrary(const std::string &name);
	void unloadLibrary(const std::string &name);
	bool flush();
private:
    std::string getPath(const std::shared_ptr<ziapi::config::Node> &config);
    void loadAll();
	std::shared_ptr<ziapi::config::Node> _config;
    std::string _modulesPath;
    std::vector<ZiaLibraryInstance> _modules;
	std::vector<std::string> _toBeDestroyed;
	bool _update;
};

#endif /* !MODULELOADER_HPP_ */
