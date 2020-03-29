#pragma once

#include <vector>
#include <pd/TabbedWindowControlHandle.hpp>

namespace pd::ecs::cmp::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	class ObserversComponent
	{
	public:
		std::vector<TabbedWindowControlHandle::Observer*> observers;
	};
}