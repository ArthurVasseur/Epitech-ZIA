/*
** EPITECH PROJECT, 2022
** ZIA
** File description:
** main
*/

#include <iostream>
#include <csignal>
#include "Application.hpp"

int main(int argc, const char *argv[])
{
    try
    {
        if (argc == 2)
        {
			Application application(argv[1]);
			application.run();
        }
        else if (argc == 1)
        {
			Application application;
			application.run();
        }
    }
    catch (const std::exception &e)
    {
		ziapi::Logger::Error(e.what());
        return 84;
    }
    return 0;
}
