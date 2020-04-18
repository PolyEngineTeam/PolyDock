#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragOutDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragOutDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<TabsHeaderWidgetComponent, TabsMovementActiveComponent>();

	if (auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->getCursorDiff() != Vector2i{ 0, 0 })
		{
			for (auto entity : view)
			{
				auto& widget = registry.get<TabsHeaderWidgetComponent>(entity);

				auto pos = inputComponent->getCursorPos();
				auto rect = widget.getWidgetRect();

				if (!widget.getWidgetRect().contains(inputComponent->getCursorPos()))
					registry.assign<TabsDragOutRequestComponent>(entity);
			}
		}
	}
}