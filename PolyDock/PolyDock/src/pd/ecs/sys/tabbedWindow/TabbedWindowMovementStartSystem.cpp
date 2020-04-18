#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementStartSystem.hpp>

// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowMovementActiveComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		TabsHeaderWidgetComponent,
		TabsHeaderComponent,
		SelectedTabsComponent>();

	if (const auto* inputComponent = registry.try_get<InputComponent>(root))
	{
		if (inputComponent->wasJustPressed(InputComponent::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				const auto& widget = view.get<TabsHeaderWidgetComponent>(entity);
				const auto& header = view.get<TabsHeaderComponent>(entity);
				const auto& selected = view.get<SelectedTabsComponent>(entity);

				if (widget.getWidgetRect().contains(inputComponent->getCursorPos()))
				{
					if (!registry.has<HoveredTabComponent>(entity) 
						|| selected.selectedTabs.size() == header.tabs().size())
					{
						auto& newCmp = registry.assign<TabbedWindowMovementActiveComponent>(entity);

						if (selected.selectedTabs.size() == header.tabs().size())
						{
							newCmp.cursorInTabSpacePosition = 
								widget.getCursorPosInTabSpace(inputComponent->getCursorPos());
						}
					}
				}
			}
		}
	}
}