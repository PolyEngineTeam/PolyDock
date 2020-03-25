#pragma once

namespace pd::ecs::cmp::tabsHeader
{
	// ---------------------------------------------------------------------------------------------------------
	class SelectedTabsComponent
	{
	public:
		std::vector<entt::entity> selectedTabs;
	};
}