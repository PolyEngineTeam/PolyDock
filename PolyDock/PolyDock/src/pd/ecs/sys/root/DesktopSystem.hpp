#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::root
{
	// ---------------------------------------------------------------------------------------------------------
	// Modified
	// 1. DesktopComponent
	class DesktopSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;
	};
}