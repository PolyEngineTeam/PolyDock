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
			: m_tabsHeader(tabsHeader), m_tabbedWindowControl(controlButtons) {}

		TabsHeaderHandle getTabsHeader() { return m_tabsHeader; }
		TabbedWindowControlHandle getTabbedWindowControl() { return m_tabbedWindowControl; }

	private:
		TabsHeaderHandle m_tabsHeader;
		TabbedWindowControlHandle m_tabbedWindowControl;
	};
}