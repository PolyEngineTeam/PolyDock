#include <pd/pch/PCH.h>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetUpdateSystem.hpp>

// in
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>
#include <pd/ecs/cmp/tab/TabComponent.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidget.hpp>

using namespace ::pd::ecs::cmp;

namespace pd::ecs::sys
{

// ---------------------------------------------------------------------------------------------------------
void TabbedWindowWidgetUpdateSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<
		::tabbedWindow::RequestWidgetUpdate,
		::tabbedWindow::Component,
		::tabbedWindow::Widget,
		tabsHeader::Widget,
		tabbedWindowControl::Widget>();

	for (auto entity : view)
	{
		auto& window = view.get<::tabbedWindow::Component>(entity);
		auto& widget = view.get<::tabbedWindow::Widget>(entity);
		auto& tabsHeaderWidget = view.get<tabsHeader::Widget>(entity);
		auto& controlWidget = view.get<tabbedWindowControl::Widget>(entity);

		widget.window->setPos(window.position);
		widget.window->setSize(window.size);
		widget.window->setTabsHeaderWidget(tabsHeaderWidget.getTabsHeaderWidget());
		widget.window->setControlWidget(controlWidget.widget->getWidget());

		if (auto* activeTabCmp = registry.try_get<tabsHeader::ActiveTab>(entity))
		{
			if (auto* tabContentCmp = registry.try_get<tab::Content>(activeTabCmp->activeTab))
				widget.window->setContentWidget(tabContentCmp->contentWidget);
			else
				widget.window->setContentWidget(nullptr);
		}
		else
			widget.window->setContentWidget(nullptr);

		registry.remove<::tabbedWindow::RequestWidgetUpdate>(entity);
	}
}

}