#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControl.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementRequestComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowRestoreRequestComponent.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindowControl;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabbedWindowMovementActiveComponent, 
		TabbedWindowComponent, 
		Component>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->getCursorDiff() != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				const auto& window = view.get<TabbedWindowComponent>(entity);
				const auto controlCmp = view.get<Component>(entity);

				if (controlCmp.maximized)
				{
					registry.get_or_assign<TabbedWindowRestoreRequestComponent>(entity);
					registry.get_or_assign<TabbedWindowMovementRequestComponent>(
						entity, inputComponent->getCursorPos() - Vector2i{window.size.x() / 2, 20} );
				}
				else
				{
					registry.get_or_assign<TabbedWindowMovementRequestComponent>(
						entity, window.position + inputComponent->getCursorDiff());
				}
			}
		}
	}
}