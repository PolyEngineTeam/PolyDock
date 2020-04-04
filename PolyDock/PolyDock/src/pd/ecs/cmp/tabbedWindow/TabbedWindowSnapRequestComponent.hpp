#pragma once

#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowSnapRequestComponent
	{
	public:
		enum class ePosition
		{
			TOP_LEFT, 
			TOP_RIGHT, 
			BOTTOM_LEFT, 
			BOTTOM_RIGHT, 
			LEFT, 
			RIGHT, 
			MAXIMIZE, 
			RESTORE, 
			MINIMIZE,
			INVALID
		};

		ePosition position = ePosition::INVALID;
		int screenIndex = -1;
	};
}