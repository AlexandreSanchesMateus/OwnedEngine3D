#include <OwnedEngine3D/Engine/Core.h>
#include <SDL3/SDL_init.h>
#include <SDL3_TTF/SDL_ttf.h>

Core::Core(std::uint32_t flags)
{
	//SDL_SetAppMetadata("OwnedEngine", "1.0", "com.asm.owned-engine");

	SDL_Init(flags);
	TTF_Init();
}

Core::~Core()
{
	TTF_Quit();
	SDL_Quit();
}

bool Core::PollEvent(SDL_Event* event)
{
	return SDL_PollEvent(event) > 0;
}