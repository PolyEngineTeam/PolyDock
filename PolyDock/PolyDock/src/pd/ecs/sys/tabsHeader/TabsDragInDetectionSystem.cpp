#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsDragInDetectionSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsDragInDetectionSystem::update(entt::registry& registry, entt::entity root) const
{
	auto srcView = registry.view<MovementActive, HoveredTab>();
	auto dstView = registry.view<
		Widget,
		Component
			>(entt::exclude<MovementActive>);

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		for (auto source : srcView)
		{
			for (auto destination : dstView)
			{
				const auto& movementCmp = srcView.get<MovementActive>(source);
				const auto& dstWidget = dstView.get<Widget>(destination);
				const auto& dstHeader = dstView.get<Component>(destination);
				int dstPos = dstWidget.getTabIdxFromPosition(inputComponent->getCursorPos());

				if (dstPos == -1 && dstWidget.isPositionOnTheRightOfLastTab(inputComponent->getCursorPos()))
					dstPos = static_cast<int>(dstHeader.tabs().size());

				if (dstPos != -1 && dstWidget.getWidgetRect().contains(inputComponent->getCursorPos()))
				{
					registry.assign<TabsDragInRequest>(destination, source, dstPos,
						movementCmp.cursorInTabSpacePosition);
				}
			}
		}
	}
}