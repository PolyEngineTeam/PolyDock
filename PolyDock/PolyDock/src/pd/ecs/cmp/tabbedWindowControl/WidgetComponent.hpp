#pragma once

namespace pd::ecs::cmp::tabbedWindowControl
{
	class IWidget 
	{
	public:
		virtual ~IWidget() = default;

		virtual QWidget* getWidget() = 0;

	};

	class DefaultWidget : public IWidget, private QWidget
	{
	public:
		QWidget* getWidget() override { return this; }
	};

	// ---------------------------------------------------------------------------------------------------------
	class WidgetComponent
	{
	public:
		IWidget* widget = nullptr;
	};
}