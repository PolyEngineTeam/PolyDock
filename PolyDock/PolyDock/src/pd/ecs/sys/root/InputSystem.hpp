#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::cmp::root { class Input; }

namespace pd::ecs::sys
{
	// ---------------------------------------------------------------------------------------------------------
	class InputSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;

	private:
		void updateCursorPos(cmp::root::Input& cmp) const;
		void updateMouseButtonState(cmp::root::Input& cmp) const;
	};
}