#pragma once

#include <entt/entt.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	class SystemBase
	{
	public:
		virtual ~SystemBase() = default;

		virtual void update(entt::registry& registry, entt::entity root) const = 0;
	};
}
