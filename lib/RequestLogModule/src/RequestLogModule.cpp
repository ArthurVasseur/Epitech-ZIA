/*
** EPITECH PROJECT, 2022
** temp
** File description:
** RequestLogModule
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <string>
#include "dylib/dylib.hpp"
#include "RequestLogModule.hpp"


void RequestLogModule::Init(const ziapi::config::Node &cfg) 
{
    
}

ziapi::Version RequestLogModule::GetVersion() const noexcept 
{
   return {1,0, 0};
}

ziapi::Version RequestLogModule::GetCompatibleApiVersion() const noexcept 
{
   return {1,0, 0};
}

const char* RequestLogModule::GetName() const noexcept 
{
    return "RequestLogModule";
}

const char* RequestLogModule::GetDescription() const noexcept 
{
    return "RequestLogModule module";
}

bool RequestLogModule::ShouldPostProcess(const ziapi::http::Context &ctx, const ziapi::http::Response &res) const 
{
    return true;
}
bool RequestLogModule::ShouldPreProcess(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const
{
    return true;
}
void RequestLogModule::PostProcess (ziapi::http::Context &ctx, ziapi::http::Response &res) 
{
    auto ip = std::any_cast<std::string>(ctx["client.socket.address"]);
    std::ofstream logfile (ip + ".txt", std::ios::app);

    logfile << std::to_string((int)res.status_code) << ": " << res.reason << " (" << std::any_cast<std::string>(ctx["method"]) << " " << std::any_cast<std::string>(ctx["target"]) << ", " << std::setprecision(2) << difftime(std::time(nullptr), std::any_cast<time_t>(ctx["timestamp"])) << "s) \n";

}

void RequestLogModule::PreProcess(ziapi::http::Context &ctx, ziapi::http::Request &req) 
{
    ctx["timestamp"] = std::time(nullptr);
    ctx["target"] = req.target;
    ctx["method"] = req.method;
}

DYLIB_API ziapi::IModule* LoadZiaModule()
{
    return new RequestLogModule;
}