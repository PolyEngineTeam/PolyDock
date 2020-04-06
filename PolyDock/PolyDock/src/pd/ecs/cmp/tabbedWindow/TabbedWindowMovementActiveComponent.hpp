#pragma once


namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowMovementActiveComponent
	{
	public:
		Eigen::Vector2i cursorInTabSpacePosition = { 0, 0 };
	};
}