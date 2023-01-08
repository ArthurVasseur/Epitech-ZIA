The Zia MUST be an exhaustive implementation of the HTTP/1.1 protocol, as described in RFC 2616, with
the exception of proxy support.

# Build

```bash
mkdir build && cd build && conan install .. --build=missing && cmake .. -G “Unix Makefiles” && cmake --build .
```
# Project Guidelines

## SERVER CONFIGURATION

The server must be fully configurable by means of a configuration file. Any software configuration done by
re-compiling the program (such as macros) will NOT be accepted and have severe consequences.
You an use any format for your configuration files, such as XML, Json, INI...
Some notes about the configuration file:
- You MAY use a parsing library specific to XML, Json or any other language you choose. Before you ask, Boost::Spirit is NOT authorized.
- You MUST implement a regular and coherent parser if you choose to not use any parsing library.
- You MUST NOT use XML or Json libraries for any other purpose than parsing the configuration file.  This will be considered as cheating.
- The server MUST NOT crash if it the configuration file is corrupt or missing: you MUST set defaultvalues.
- The configuration file MUST NOT be opened with an absolute path.
- It MUST be possible to reload the configuration file without restarting nor recompiling the server


## Modules

As a modular server, the Zia MUST be able to handle modules. The Zia executable could be seen as anempty shell that must be filled with modules in order to work.
A module is an atomic processing unit that can receive input from other modules, and send output to them.
It MUST be possible to use any number of modules together to create a processing line that will handle anHTTP request and create an appropriate HTTP response.
You MUST design a complete Application Programming Interface to handle you Zia’s modules.
Although submitting your API to the election is optional, we greatly encourage you to do design one and present it in the first follow-up.
Once the election is finished, your modules MUST conform to the locally choosen API.
No matter what API is elected, each group MUST provide two mandatory modules: the secure connection module and the PHP CGI module. Once these two modules work perfectly, you MUST add as many other modules as you like in order to raise your final grade.
As always, when designing your API, question its flexibility. How easy would it be to add a log module that would keep a log file of all incoming requests, and that would let other modules send it log messages? How easy would it be to add a video game module that would be a Snake clone in which each incoming request spawns a food item?

## SSL Module

The server MUST let clients establish secure connections using SSL or TLS. This feature MUST be a module.
You are allowed to use OpenSSL

## PHP CGI Module

This module MUST make it possible for the server to execute PHP scripts. The scripts MUST run as CGI.