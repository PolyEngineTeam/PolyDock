#pragma once

#include <pd/TabsHeaderHandle.hpp>
#include <pd/TabbedWindowControlHandle.hpp>

namespace pd
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowHandle final
	{
	public:
		TabbedWindowHandle(TabsHeaderHandle tabsHeader, TabbedWindowControlHandle controlButtons) 
			: m_tabsHeader(tabsHeader) {}

		TabsHeaderHandle getTabsHeader() { return m_tabsHeader; }
		TabsHeaderHandle getTabbedWindowControl() { return m_tabbedWindowControl; }

	private:
		TabsHeaderHandle m_tabsHeader;
		TabbedWindowControlHandle m_tabbedWindowControl;
	};
}