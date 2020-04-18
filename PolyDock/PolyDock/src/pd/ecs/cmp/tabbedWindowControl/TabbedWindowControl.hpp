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
	class Observers
	{
	public:
		std::vector<TabbedWindowControlHandle::Observer*> observers;
	};

	// ---------------------------------------------------------------------------------------------------------
	class Hover
	{
	public:
		IWidget::eButton hovered = IWidget::eButton::NONE;
	};

	// ---------------------------------------------------------------------------------------------------------
	class Press
	{
	public:

	};
	
	// ---------------------------------------------------------------------------------------------------------
	class CloseRequest
	{
	public:
		bool force = false;
	};

	// ---------------------------------------------------------------------------------------------------------
	class WidgetUpdateRequest
	{
	public:
	};
}