#pragma once

#include <entt/entt.hpp>

namespace pd::ecs::cmp::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class UndockRequestComponent final
	{
	public:
		entt::entity dock;
	};
}