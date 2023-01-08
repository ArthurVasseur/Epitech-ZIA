/*
** EPITECH PROJECT, 2022
** temp
** File description:
** RequestLogModule
*/


#ifndef RequestLogModule_HPP_
#define RequestLogModule_HPP_
#include "ziapi/Module.hpp"

class RequestLogModule: virtual public ziapi::IPostProcessorModule, virtual public ziapi::IPreProcessorModule {
    public:
        RequestLogModule() = default;
        ~RequestLogModule() override = default;

        void Init(const ziapi::config::Node &cfg) override;
        [[nodiscard]]  ziapi::Version GetVersion() const noexcept override;
        [[nodiscard]] ziapi::Version GetCompatibleApiVersion() const noexcept override;
        [[nodiscard]] const char *GetName() const noexcept override;
        [[nodiscard]] const char *GetDescription() const noexcept override;
        [[nodiscard]] double GetPostProcessorPriority() const noexcept override {return 1; }
        [[nodiscard]] double GetPreProcessorPriority() const noexcept override {return 0; }
        [[nodiscard]] bool ShouldPostProcess(const ziapi::http::Context &ctx, const ziapi::http::Response &res) const override;
        [[nodiscard]] bool ShouldPreProcess(const ziapi::http::Context &ctx, const ziapi::http::Request &req) const override;
        void PostProcess (ziapi::http::Context &ctx, ziapi::http::Response &res) override;
        void PreProcess(ziapi::http::Context &ctx, ziapi::http::Request &req) override;
    protected:
    private:
        
};
#endif /* !RequestLogModule_HPP_ */