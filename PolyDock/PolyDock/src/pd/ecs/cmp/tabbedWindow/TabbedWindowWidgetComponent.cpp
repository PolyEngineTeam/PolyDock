#include <pd/pch/PCH.h>
#include <pd/ecs/cmp/tabbedWindow/TabbedWindowWidgetComponent.hpp>

#include <Eigen/Dense>
#include <pd/ecs/cmp/root/WidgetsOwnerComponent.hpp>

using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::Eigen;

namespace
{
	constexpr int TABS_HEADER_IDX = 0;
	constexpr int CONTROL_WIDGET_IDX = 0;
	constexpr int CONTENT_IDX = 1;
}

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
DefaultTabbedWindowWidget::DefaultTabbedWindowWidget()
{
	// create main layout
	m_mainLayout = new QGridLayout();
	m_mainLayout->setContentsMargins(1, 1, 1, 1);
	m_mainLayout->setSpacing(0);

	m_placeholderContentWidget = new QWidget();
	m_contentWidget = m_placeholderContentWidget;
	m_mainLayout->addWidget(m_placeholderContentWidget, CONTENT_IDX, 0, 1, 2);

	QWidget::setLayout(m_mainLayout);
	QWidget::setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QWidget::setContentsMargins(5, 5, 5, 5);
	QPalette pal = QWidget::palette();
	pal.setColor(QPalette::Background, QColor(30, 30, 30));
	QWidget::setAutoFillBackground(true);
	QWidget::setPalette(pal);
	QWidget::show();
}

// ---------------------------------------------------------------------------------------------------------
DefaultTabbedWindowWidget::~DefaultTabbedWindowWidget()
{
	setTabsHeaderWidget(nullptr);
	setContentWidget(nullptr);

	if (m_mainLayout)
		delete m_mainLayout;
	if (m_placeholderContentWidget)
		delete m_placeholderContentWidget;
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::setPos(Eigen::Vector2i pos)
{
	if (QWidget::isMaximized() || QWidget::isMinimized())
		QWidget::showNormal();
	
	QWidget::move(pos.x(), pos.y()); 
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::setSize(Eigen::Vector2i size)
{
	if (QWidget::isMaximized() || QWidget::isMinimized())
		QWidget::showNormal();

	QWidget::resize(size.x(), size.y()); 
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::setTabsHeaderWidget(QWidget* widget)
{
	if (m_tabsHeaderWidget != widget)
	{
		if (m_tabsHeaderWidget)
		{
			m_mainLayout->removeWidget(m_tabsHeaderWidget);
			m_tabsHeaderWidget->setParent(nullptr);
			m_tabsHeaderWidget->hide();
			m_tabsHeaderWidget = nullptr;
		}

		if (widget)
		{
			m_tabsHeaderWidget = widget;
			m_mainLayout->addWidget(m_tabsHeaderWidget, TABS_HEADER_IDX, 0, 1, 1);
			m_tabsHeaderWidget->setFixedHeight(35);
			m_tabsHeaderWidget->show();
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::setControlWidget(QWidget* widget)
{
	if (m_controlWidget != widget)
	{
		if (m_controlWidget)
		{
			m_mainLayout->removeWidget(m_controlWidget);
			m_controlWidget->setParent(nullptr);
			m_controlWidget->hide();
			m_controlWidget = nullptr;
		}

		if (widget)
		{
			m_controlWidget = widget;
			m_mainLayout->addWidget(m_controlWidget, CONTROL_WIDGET_IDX, 1, 1, 1);
			m_controlWidget->setFixedHeight(35);
			m_controlWidget->show();
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::setContentWidget(QWidget* widget)
{
	if (m_contentWidget != widget)
	{
		if (m_contentWidget)
		{
			m_mainLayout->removeWidget(m_contentWidget);
			m_contentWidget->setParent(nullptr);
			m_contentWidget->hide();
			m_contentWidget = nullptr;
		}

		if (widget)
			m_contentWidget = widget;
		else
			m_contentWidget = m_placeholderContentWidget;

		m_mainLayout->addWidget(m_contentWidget, CONTENT_IDX, 0, 1, 2);
		m_contentWidget->show();
		m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	}
}

// ---------------------------------------------------------------------------------------------------------
void DefaultTabbedWindowWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);

	QPainter painter;
	painter.begin(this);

	painter.setPen(QColor(179, 136, 32));
	painter.drawRect(0, 0, QWidget::width() - 1, QWidget::height() - 1);

	painter.end();
}