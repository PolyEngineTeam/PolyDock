#pragma once

#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsDragInRequestComponent
	{
	public:
		entt::entity source;
		int destinationIndex = 0;
	};
}