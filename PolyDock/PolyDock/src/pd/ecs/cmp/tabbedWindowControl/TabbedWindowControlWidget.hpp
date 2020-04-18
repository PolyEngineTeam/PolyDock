#pragma once

#include <qlabel.h>
#include <qgridlayout.h>
#include <Eigen/Dense>

namespace pd::ecs::cmp::tabbedWindowControl
{
	class IWidget 
	{
	public:
		enum class eButton
		{
			NONE,
			MINIMIZE,
			MAXIMIZE,
			CLOSE
		};

		virtual ~IWidget() = default;

		virtual void update(eButton hovered, bool pressed, bool maximized) = 0;
		virtual Eigen::AlignedBox2i getWidgetRect() const = 0;
		virtual eButton getButtonFromPos(const Eigen::Vector2i& pos) const = 0;

		virtual QWidget* getWidget() = 0;

	};

	// ---------------------------------------------------------------------------------------------------------
	class DefaultWidget : public IWidget, private QWidget
	{
	public:
		DefaultWidget();
		
		void update(eButton hovered, bool pressed, bool maximized) final;
		Eigen::AlignedBox2i getWidgetRect() const final;
		eButton getButtonFromPos(const Eigen::Vector2i& pos) const final;
		QWidget* getWidget() override { return this; }

	private:
		QGridLayout* m_layout = nullptr;
		QLabel* m_minimize = nullptr;
		QLabel* m_maximize = nullptr;
		QLabel* m_close = nullptr;
	};

	// ---------------------------------------------------------------------------------------------------------
	class Widget
	{
	public:
		IWidget* widget = nullptr;
	};
}

