#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::root
{
	// ---------------------------------------------------------------------------------------------------------
	class DesktopSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;
	};
}