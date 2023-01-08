/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Pipe
*/

#ifndef PIPE_HPP_
#define PIPE_HPP_
#include <string>
#include <memory>
#include <exception>
#include <array>
#include <unordered_map>
#include <unistd.h>
#include "subprocess-prefix/src/subprocess/src/cpp/subprocess.hpp"

class Pipe {
    public:
        explicit Pipe(const std::string &cmd, std::unordered_map<std::string, std::string> &envMap) : _file(nullptr)
        {
            if (!open(cmd, envMap))
                throw std::runtime_error("popen: unable execute command : " + cmd);
        }
        ~Pipe()
        {
            close();
        }
        bool open(const std::string &cmd,std::unordered_map<std::string, std::string> &envMap)
        {
//			std::vector<std::string> env(envMap.size());
//			for (auto &pair : envMap)
//			{
//				std::string str = pair.first;
//				std::transform(str.begin(), str.end(),str.begin(), toupper);
//				std::replace(str.begin(), str.end(), ' ', '_');
//				str += "=" + pair.second;
//				env.push_back(std::move(str));
//			}
//			execle(cmd.c_str(), cmd.c_str(), nullptr, env.data());
			return false;
        }

        bool close()
        {
//            if (_file)
//            {
//                if(PCLOSE(_file) == 0)
//                    return true;
//            }
            return false;
        }

        void get(std::string &headers, std::string &body)
        {
            if (!_file)
                return;
            std::array<char, 1024> buffer {'\0'};
            std::string res;
            while (fgets(buffer.data(), buffer.size(), _file))
            {
                res += buffer.data();
                buffer.fill('\0');
            }
            if (res.empty())
                return;
            body = res.substr(res.find("\r\n\r\n") + 4);
            headers = res.substr(0, res.find("\r\n\r\n"));
        }
    private:
        FILE *_file;
};

#endif /* !PIPE_HPP_ */
