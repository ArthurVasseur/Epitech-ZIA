# RequestLogModule Module Documentation

--> Log each request made to the server in a file

## Module Type

The RequestLogModule module implements the following module interfaces:
    - IPostProcessorModule
    - IPreProcessorModule

## Configuration

No configuration needed from the user.

## Context

This section defines the request/response context values the module depends on.

| Key       | Type        | Actions | Description                          |
|-----------|-------------|---------|--------------------------------------|
| timestamp | std::time   | Read    | Get the current time.                |
| target    | std::string | Read    | Get the HTTP request's target URL.   |
| method    | std::string | Read    | Get the HTTP requests's method used. |

## Additional Comments

<!-- Any information the user should be aware of -->