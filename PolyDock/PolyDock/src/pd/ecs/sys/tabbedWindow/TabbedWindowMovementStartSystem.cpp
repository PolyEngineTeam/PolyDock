#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovementStartSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/Movement.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		Widget,
		Component,
		SelectedTabs>();

	if (const auto* inputComponent = registry.try_get<Input>(root))
	{
		if (inputComponent->wasJustPressed(Input::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				const auto& widget = view.get<Widget>(entity);
				const auto& header = view.get<Component>(entity);
				const auto& selected = view.get<SelectedTabs>(entity);

				if (widget.getWidgetRect().contains(inputComponent->getCursorPos()))
				{
					if (!registry.has<HoveredTab>(entity) 
						|| selected.selectedTabs.size() == header.tabs().size())
					{
						auto& newCmp = registry.assign<MovementActive>(entity);

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