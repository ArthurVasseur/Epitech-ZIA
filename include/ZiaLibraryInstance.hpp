/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** ZiaLibraryInstance
*/

#ifndef ZIALIBRARYINSTANCE_HPP_
#define ZIALIBRARYINSTANCE_HPP_

#include <memory>
#include "ziapi/Module.hpp"
#include "dylib/dylib.hpp"

class ZiaLibraryInstance
{
public:
    explicit ZiaLibraryInstance(const std::string &path) : _libraryInstance(path), _classInstance(std::shared_ptr<ziapi::IModule>(getInstance())), _path(path)
    {
    }
    ZiaLibraryInstance(ZiaLibraryInstance&&) = default;
    ~ZiaLibraryInstance() = default;
	ZiaLibraryInstance& operator=(ZiaLibraryInstance&&) = default;
	ziapi::IModule *operator->()
    {
        return _classInstance.get();
    }

    std::shared_ptr<ziapi::IModule> get()
    {
        return _classInstance;
    }
	void reload()
	{
		auto ptr = std::dynamic_pointer_cast<ziapi::INetworkModule>(_classInstance);
		if (ptr != nullptr)
		{
			ptr->Terminate();
		}
		_libraryInstance.open(_path);
	}

private:
    ziapi::IModule *getInstance()
    {
        return _libraryInstance.get_function<ziapi::IModule *()>("LoadZiaModule")();
    }
    dylib _libraryInstance;
    std::shared_ptr<ziapi::IModule> _classInstance;
	std::string _path;
};
#endif /* !ZIALIBRARYINSTANCE_HPP_ */
