#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::cmp::root { class Input; }

namespace pd::ecs::sys::root
{
	// ---------------------------------------------------------------------------------------------------------
	class WidgetsOwnerSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;
	};
}