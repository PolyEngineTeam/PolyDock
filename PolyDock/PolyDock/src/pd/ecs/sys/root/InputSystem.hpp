#pragma once

#include <pd/ecs/sys/SystemBase.hpp>

namespace pd::ecs::cmp::root { class InputComponent; }

namespace pd::ecs::sys::root
{
	// ---------------------------------------------------------------------------------------------------------
	class InputSystem : public SystemBase
	{
	public:
		void update(entt::registry&, entt::entity root) const final;

	private:
		void updateCursorPos(cmp::root::InputComponent& cmp) const;
		void updateMouseButtonState(cmp::root::InputComponent& cmp) const;
	};
}