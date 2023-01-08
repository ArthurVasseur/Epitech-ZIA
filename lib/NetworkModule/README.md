# NetworkModule Module Documentation

A module that implements a TCP server.

## Module Type

The NetworkModule module implements the following module interfaces:
    - INetworkModule

## Configuration

This section defines the configuration values the module depends on.

| Key | Type | Required | Description                            |
|-----|------|----------|----------------------------------------|
| port | int | No | Default value is `8080`                |
|listening |std::string | No | Default value is `0.0.0.0`             |


## Context

This section defines the request/response context values the module depends on.

| Key | Type        | Actions | Description |
|-----|-------------|---------|-------------|
|client.socket.address| std::string |Read + Write|The address of the client's socket.|
|client.socket.port| std::string |Read + Write|The port of the client's socket.|
|client.socket.keepAlive| bool        |Read + Write|Variable to know if the user's session should be kept or killed.|

<!-- ## Additional Comments -->

<!-- Any information the user should be aware of -->