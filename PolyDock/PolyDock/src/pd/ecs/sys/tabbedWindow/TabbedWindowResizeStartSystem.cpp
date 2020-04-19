#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizeStartSystem.hpp>

#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabbedWindow/Resizing.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::root;
using namespace ::Eigen;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowResizeStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<ResizeHover>();
	
	if (const auto* inputComponent = registry.try_get<Input>(root))
	{
		if (inputComponent->wasJustPressed(Input::eMouseButton::LEFT))
		{
			for (auto entity : view)
			{
				const auto& hoverCmp = view.get<ResizeHover>(entity);
				auto& activeCmp = registry.get_or_assign<ResizeActive>(entity);
				activeCmp.horizontal = hoverCmp.horizontal;
				activeCmp.vertical = hoverCmp.vertical;
			}
		}
	}
}