#pragma once

#include <vector>

#include <pd/TabbedWindowControlHandle.hpp>
#include <pd/ecs/cmp/tabbedWindowControl/TabbedWindowControlWidget.hpp>

namespace pd::ecs::cmp::tabbedWindowControl
{
	// ---------------------------------------------------------------------------------------------------------
	class Component
	{
	public:
		bool maximized = false;
	};

	// ---------------------------------------------------------------------------------------------------------
	class ObserversComponent
	{
	public:
		std::vector<TabbedWindowControlHandle::Observer*> observers;
	};

	// ---------------------------------------------------------------------------------------------------------
	class HoverComponent
	{
	public:
		IWidget::eButton hovered = IWidget::eButton::NONE;
	};

	// ---------------------------------------------------------------------------------------------------------
	class PressComponent
	{
	public:

	};
	
	// ---------------------------------------------------------------------------------------------------------
	class CloseRequestComponent
	{
	public:
		bool force = false;
	};

	// ---------------------------------------------------------------------------------------------------------
	class WidgetUpdateRequestComponent
	{
	public:
	};
}