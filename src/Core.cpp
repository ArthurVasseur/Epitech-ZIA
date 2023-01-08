/*
** EPITECH PROJECT, 2022
** B-YEP-500-PAR-5-1-zia-arthur.vasseur
** File description:
** Core
*/

#include "Core.hpp"
#include <mutex>
Core::Core(std::shared_ptr<ModuleLoader>& ml) : _ml(ml), _isRunning(true)
{
	getModules();

}

void Core::run()
{
	while (_isRunning)
	{
		std::for_each(_networkModules.begin(), _networkModules.end(),
				[this](std::pair<const std::shared_ptr<ziapi::INetworkModule>, NetworkQueue>& networkModule)
				{
					std::optional<std::pair<ziapi::http::Request, ziapi::http::Context>> r;
					do
					{
						r = networkModule.second.popNewRequest();
						if (!r)
							continue;
						ziapi::http::Request& req = r->first;
						ziapi::http::Response res;
						ziapi::http::Context& ctx = r->second;

						std::for_each(_preProcessModules.begin(), _preProcessModules.end(),
								[&req, &ctx](std::shared_ptr<ziapi::IPreProcessorModule>& mod)
								{
									if (mod->ShouldPreProcess(ctx, req))
										mod->PreProcess(ctx, req);
								});
						std::for_each(_handlerModules.begin(), _handlerModules.end(),
								[&req, &ctx, &res](std::shared_ptr<ziapi::IHandlerModule>& mod)
								{
									if (mod->ShouldHandle(ctx, req))
										mod->Handle(ctx, req, res);
								});
						std::for_each(_postProcessModules.begin(), _postProcessModules.end(),
								[&ctx, &res](std::shared_ptr<ziapi::IPostProcessorModule>& mod)
								{
									if (mod->ShouldPostProcess(ctx, res))
										mod->PostProcess(ctx, res);
								});
						networkModule.second.pushNewResponse({ res, ctx });
					} while (r);
				});
		if (_ml->flush())
			getModules();
	}
}

void Core::getModules()
{
	_preProcessModules = _ml->getAll<ziapi::IPreProcessorModule>();
	_postProcessModules = _ml->getAll<ziapi::IPostProcessorModule>();
	_handlerModules = _ml->getAll<ziapi::IHandlerModule>();
	auto networkModules = _ml->getAll<ziapi::INetworkModule>();
	std::erase_if(_networkModules, [&networkModules](std::pair<const std::shared_ptr<ziapi::INetworkModule>, NetworkQueue>& networkModule){
		if(std::find(networkModules.begin(), networkModules.end(), networkModule.first) == networkModules.end())
		{
			networkModule.first->Terminate();
			return true;
		}
		return false;
	});
	std::for_each(networkModules.begin(), networkModules.end(), [this](std::shared_ptr<ziapi::INetworkModule>& module)
	{
		if (_networkModules.find(module) == _networkModules.end())
			_networkModules[module];
	});

	std::sort(_preProcessModules.begin(), _preProcessModules.end(),
			[](const std::shared_ptr<ziapi::IPreProcessorModule>& a,
					const std::shared_ptr<ziapi::IPreProcessorModule>& b)
			{
				return a->GetPreProcessorPriority() > b->GetPreProcessorPriority();
			});
	std::sort(_postProcessModules.begin(), _postProcessModules.end(),
			[](const std::shared_ptr<ziapi::IPostProcessorModule>& a,
					const std::shared_ptr<ziapi::IPostProcessorModule>& b)
			{
				return a->GetPostProcessorPriority() > b->GetPostProcessorPriority();
			});
	std::sort(_handlerModules.begin(), _handlerModules.end(),
			[](const std::shared_ptr<ziapi::IHandlerModule>& a, const std::shared_ptr<ziapi::IHandlerModule>& b)
			{
				return a->GetHandlerPriority() > b->GetHandlerPriority();
			});
	std::for_each(_networkModules.begin(), _networkModules.end(),
			[](std::pair<const std::shared_ptr<ziapi::INetworkModule>, NetworkQueue>& networkModule)
			{
				networkModule.first->Run(networkModule.second, networkModule.second);
			});
}