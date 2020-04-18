#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetUpdateSystem.hpp>

// in
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/WidgetComponent.hpp>
#include <pd/ecs/cmp/tab/TabContentComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>

using namespace ::pd::ecs::sys::tabbedWindow;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp;
using namespace ::pd::ecs::cmp::tab;

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowWidgetUpdateSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		DirtyTabbedWindowComponent,
		TabbedWindowComponent,
		TabbedWindowWidgetComponent,
		TabsHeaderWidgetComponent,
		tabbedWindowControl::WidgetComponent>();

	for (auto entity : view)
	{
		auto& window = view.get<TabbedWindowComponent>(entity);
		auto& widget = view.get<TabbedWindowWidgetComponent>(entity);
		auto& tabsHeaderWidget = view.get<TabsHeaderWidgetComponent>(entity);
		auto& controlWidget = view.get<tabbedWindowControl::WidgetComponent>(entity);

		widget.window->setPos(window.position);
		widget.window->setSize(window.size);
		widget.window->setTabsHeaderWidget(tabsHeaderWidget.getTabsHeaderWidget());
		widget.window->setControlWidget(controlWidget.widget->getWidget());

		if (auto* activeTabCmp = registry.try_get<ActiveTabComponent>(entity))
		{
			if (auto* tabContentCmp = registry.try_get<TabContentComponent>(activeTabCmp->activeTab))
				widget.window->setContentWidget(tabContentCmp->contentWidget);
			else
				widget.window->setContentWidget(nullptr);
		}
		else
			widget.window->setContentWidget(nullptr);

		registry.remove<DirtyTabbedWindowComponent>(entity);
	}
}