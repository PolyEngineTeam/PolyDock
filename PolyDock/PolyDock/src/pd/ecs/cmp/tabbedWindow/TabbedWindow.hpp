#pragma once

#include <Eigen/Dense>

namespace pd { class TabbedWindow; }

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class Component
	{
	public:
		Eigen::Vector2i position;
		Eigen::Vector2i size;
		QUuid layerUuid;
	};
	
	// ---------------------------------------------------------------------------------------------------------
	class RequestWidgetUpdate
	{
	public:

	};
	
	// ---------------------------------------------------------------------------------------------------------
	class Focused
	{
	public:
	};
}