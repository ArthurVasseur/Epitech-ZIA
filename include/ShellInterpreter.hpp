//
// Created by arthur on 01/03/2022.
//

#ifndef ZIA_SHELLINTERPRETER_HPP
#define ZIA_SHELLINTERPRETER_HPP
#include "ModuleLoader.hpp"

class ShellInterpreter
{
public:
	explicit ShellInterpreter(std::shared_ptr<ModuleLoader> & ml);

	ShellInterpreter(ShellInterpreter&&) = delete;

	ShellInterpreter(const ShellInterpreter&) = delete;

	ShellInterpreter& operator=(ShellInterpreter&&) = delete;

	ShellInterpreter& operator=(const ShellInterpreter&) = delete;

	~ShellInterpreter() = default;
	void run();

private:
	static std::vector<std::string> split(const std::string& str, char delimiter);

	void GetCommand(std::string& command);
	std::shared_ptr<ModuleLoader> _ml;
};


#endif //ZIA_SHELLINTERPRETER_HPP
