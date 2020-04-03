#pragma once

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowResizeActiveComponent
	{
	public:
		enum class eVertical { TOP, MIDDLE, BOTTOM };
		enum class eHorizontal { LEFT, MIDDLE, RIGHT };

		eVertical vertical = eVertical::MIDDLE;
		eHorizontal horizontal = eHorizontal::MIDDLE;
	};
}