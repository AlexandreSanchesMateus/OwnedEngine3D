#include <OwnedEngine3D/Input/InputManager.h>
#include "SDL3/SDL_events.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::HandleEvent(const SDL_Event& event, double deltaTime)
{
    /*
    switch (event.type)
    {
        // Keayboard events
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:

        // Mouse events
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
    case SDL_EVENT_MOUSE_MOTION:
    case SDL_EVENT_MOUSE_WHEEL:

        // Gamepad
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        break;
    }
    */
}

void InputManager::HandleLateEvent(double deltaTime)
{

}