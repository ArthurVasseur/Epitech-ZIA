# HttpModule Module Documentation

A module that implements the HTTP 1.1 protocol.

## Module Type

The HttpModule module implements the following module interfaces:
    - IHandlerModule

## Configuration

This section defines the configuration values the module depends on.

| Key | Type | Required | Description |
|-----|------|----------|-------------|
| filesPath | std::string | No | Default value is `./www`|
|defaultPage |std::string | No | Default value is `index.html`|