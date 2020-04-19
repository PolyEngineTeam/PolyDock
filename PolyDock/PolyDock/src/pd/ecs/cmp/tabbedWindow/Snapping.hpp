#pragma once

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class MaximizeRequest
	{
	public:

	};

	// ---------------------------------------------------------------------------------------------------------
	class MinimizeRequest
	{
	public:

	};

	// ---------------------------------------------------------------------------------------------------------
	class RestoreRequest
	{
	public:

	};
	
	// ---------------------------------------------------------------------------------------------------------
	class SnapRequest
	{
	public:
		enum class ePosition
		{
			TOP_LEFT, 
			TOP_RIGHT, 
			BOTTOM_LEFT, 
			BOTTOM_RIGHT, 
			LEFT, 
			RIGHT, 
			MAXIMIZE, 
			RESTORE, 
			MINIMIZE,
			INVALID
		};

		ePosition position = ePosition::INVALID;
		int screenIndex = -1;
	};
}