# PhpModule Module Documentation

A module that implements a PHP CGI protocol.

## Module Type

The PhpModule module implements the following module interfaces:
    - IHandlerModule

## Configuration

This section defines the configuration values the module depends on.

| Key | Type | Required | Description |
|-----|------|----------|-------------|
| cgiPath | std::string | No | Default value is `/usr/bin/php`|
|filespath |std::string | No | Default value is `./www`|
| defaultPage | std::string | No | Default value is `index.php`

<!-- ## Additional Comments -->

<!-- Any information the user should be aware of -->