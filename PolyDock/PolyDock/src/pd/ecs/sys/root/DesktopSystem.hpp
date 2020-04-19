#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	// Modified
	// 1. Desktop
	class DesktopSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;
	};
}