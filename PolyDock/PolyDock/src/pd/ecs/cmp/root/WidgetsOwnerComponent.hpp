#pragma once

#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>
#include <pd/ecs/cmp/dock/DockWidgetComponent.hpp>

namespace pd::ecs::cmp::root
{
	// ---------------------------------------------------------------------------------------------------------
	class WidgetsOwnerComponent
	{
	public:
		WidgetsOwnerComponent() = default;
		WidgetsOwnerComponent(const WidgetsOwnerComponent&) { assert(false); }
		~WidgetsOwnerComponent()
		{
			for (auto&[key, value] : windows)
				delete value;
			for (auto&[key, value] : tabsHeaders)
				delete value;
			for (auto&[key, value] : windowControls)
				delete value;
			for (auto&[key, value] : docks)
				delete value;
		}

		std::map<entt::entity, tabbedWindow::ITabbedWindowWidget*> windows;
		std::map<entt::entity, tabsHeader::ITabsHeaderWidget*> tabsHeaders;
		std::map<entt::entity, tabbedWindowControl::IWidget*> windowControls;
		std::map<entt::entity, dock::DockWidget*> docks;
	};
}