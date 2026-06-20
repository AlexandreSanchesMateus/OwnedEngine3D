#pragma once
#include "OwnedEngine3D/Export.h"
#include <functional>
#include <string>
#include <vector>

class OWNED_ENGINE_API InputAction
{
public:
	
	enum EventState
	{
		JUST_PRESSED,
		PRESS,
		RELEASE
	};

private:
	std::string m_actionName = "";
	EventState m_eventState = EventState::RELEASE;


};