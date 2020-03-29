#pragma once

#include <Eigen/Dense>

namespace pd::ecs::cmp::root { class WidgetsOwnerComponent; }

namespace pd::ecs::cmp::tabbedWindow
{
	// ---------------------------------------------------------------------------------------------------------
	class ITabbedWindowWidget
	{
	public:
		virtual ~ITabbedWindowWidget() = default;

		virtual void setPos(Eigen::Vector2i pos) = 0;
		virtual void setSize(Eigen::Vector2i size) = 0;

		virtual void setTabsHeaderWidget(QWidget* widget) = 0;
		virtual void setControlWidget(QWidget* widget) = 0;
		virtual void setContentWidget(QWidget* widget) = 0;

		virtual QWidget* getWidget() = 0;
	};

	// ---------------------------------------------------------------------------------------------------------
	class DefaultTabbedWindowWidget : public ITabbedWindowWidget, private QWidget
	{
	public:
		DefaultTabbedWindowWidget();
		~DefaultTabbedWindowWidget();

		void setPos(Eigen::Vector2i pos) override { QWidget::move(pos.x(), pos.y()); }
		void setSize(Eigen::Vector2i size) override { QWidget::resize(size.x(), size.y()); }

		void setTabsHeaderWidget(QWidget* widget) override;
		void setControlWidget(QWidget* widget) override;
		void setContentWidget(QWidget* widget) override;

		QWidget* getWidget() override { return this; }

	private:
		// QWidget
		void paintEvent(QPaintEvent* event) override;

		QPointer<QGridLayout> m_mainLayout;
		QPointer<QWidget> m_controlWidget;
		QPointer<QWidget> m_tabsHeaderWidget;
		QPointer<QWidget> m_contentWidget;
		QPointer<QWidget> m_placeholderContentWidget;
	};

	// ---------------------------------------------------------------------------------------------------------
	class TabbedWindowWidgetComponent
	{
	public:
		TabbedWindowWidgetComponent(ITabbedWindowWidget* window) : m_window(window) {}

		void setPos(Eigen::Vector2i pos) { m_window->setPos(pos); }
		void setSize(Eigen::Vector2i size) { m_window->setSize(size); }

		void setControlWidget(QWidget* widget) { m_window->setControlWidget(widget); }
		void setTabsHeaderWidget(QWidget* widget) { m_window->setTabsHeaderWidget(widget); }
		void setContentWidget(QWidget* widget) { m_window->setContentWidget(widget); }

	private:
		ITabbedWindowWidget* m_window;
	};
}