#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::sys::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class TabsHeaderAddButtonHoverSystem : public SystemBase
	{
	public:
		void update(entt::registry& registry, entt::entity root) const final;
	};
}
