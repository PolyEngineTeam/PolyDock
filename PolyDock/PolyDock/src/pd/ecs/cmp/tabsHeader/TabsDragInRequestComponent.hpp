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
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}