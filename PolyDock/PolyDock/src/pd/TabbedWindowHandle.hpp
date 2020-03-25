#pragma once

#include <pd/TabsHeaderHandle.hpp>

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowHandle final
	{
	public:
		TabbedWindowHandle(TabsHeaderHandle tabsHeader) : m_tabsHeader(tabsHeader) {}

		TabsHeaderHandle getTabsHeader() { return m_tabsHeader; }

	private:
		TabsHeaderHandle m_tabsHeader;
	};
}