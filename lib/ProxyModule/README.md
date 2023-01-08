# ProxyModule Module Documentation

A module that handles proxy requests.

## Module Type

The HttpModule module implements the following module interfaces:
    - IHandlerModule

## Configuration

This section defines the configuration values the module depends on.

| Key                    | Type        | Required | Description                                           |
|------------------------|-------------|----------|-------------------------------------------------------|
| Proxy redirection name | std::string | Yes      | Address and port of the redicrection `127.0.0.1:5000` |
