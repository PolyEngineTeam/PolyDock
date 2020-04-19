#pragma once

#include <Eigen/Dense>

namespace pd { class TabbedWindow; }

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowComponent
	{
	public:
		Eigen::Vector2i position;
		Eigen::Vector2i size;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class DirtyTabbedWindowComponent
	{
	public:

	};
	
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowFocusComponent
	{
	public:
	};
}