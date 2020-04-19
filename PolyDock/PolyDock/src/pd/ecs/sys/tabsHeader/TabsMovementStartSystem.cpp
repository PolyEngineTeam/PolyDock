#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabsHeader/TabsMovementStartSystem.hpp>

// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsDragging.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void TabsMovementStartSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		Component,
		HoveredTab, 
		SelectedTabs,
		Widget>();

	if (auto* inputComponent = registry.try_get<Input>(root))
	{
		if (inputComponent->wasJustPressed(cmp::root::Input::eMouseButton::LEFT))
		{
			// @todo(squares): sort entities by depth (or maybe disable hovering anything other than top window)
			for (auto entity : view)
			{
				const auto& header = view.get<Component>(entity);
				const auto& hovered = view.get<HoveredTab>(entity);
				const auto& selected = view.get<SelectedTabs>(entity);
				const auto& widget = view.get<Widget>(entity);

				if (selected.selectedTabs.size() < header.tabs().size())
				{
					registry.assign<TabsMovementActive>(entity,
						widget.getCursorPosInTabSpace(inputComponent->getCursorPos()));
				}
			}
		}
	}
}