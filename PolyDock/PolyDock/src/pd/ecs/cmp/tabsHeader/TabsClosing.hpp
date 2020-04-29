#pragma once

#include <optional>
#include <vector>
#include <entt/entt.hpp>

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class CloseButtonHovered
	{
	public:
		entt::entity tab;
	};

	// ---------------------------------------------------------------------------------------------------------
	class CloseButtonPressed
	{
	};

	// ---------------------------------------------------------------------------------------------------------
	class CloseTabRequest
	{
	public:
		std::vector<entt::entity> tabsToClose;
	};
}