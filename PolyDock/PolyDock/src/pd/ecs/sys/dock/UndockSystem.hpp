#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::dock
{
	// ---------------------------------------------------------------------------------------------------------
	class UndockSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}