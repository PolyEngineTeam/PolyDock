#pragma once

namespace pd::ecs::cmp::tabbedWindowControl
{
	class IWidget 
	{
	public:
		virtual ~IWidget() = default;

		virtual QWidget* getWidget() = 0;

	};

	// ---------------------------------------------------------------------------------------------------------
	class DefaultWidget : public IWidget, private QWidget
	{
	public:
		DefaultWidget()
			: m_layout(new QHBoxLayout()), m_minimize(new QPushButton("Minimize")), 
				m_maximize(new QPushButton("Maximize")), m_close(new QPushButton("Close"))
		{
			setLayout(m_layout);
			m_layout->setContentsMargins(0, 0, 0, 0);
			m_layout->setSpacing(0);
			m_layout->addWidget(m_minimize);
			m_layout->addWidget(m_maximize);
			m_layout->addWidget(m_close);

			m_minimize->setStyleSheet(
				"QpushButton{qproperty-icon:url(:/icons/tabbedWindow/minimize.png);}"
				"QpushButton:hover{qproperty-icon:url(:/icons/tabbedWindow/minimizeHover.png);}"
				"QpushButton:press{qproperty-icon:url(:/icons/tabbedWindow/minimizePressed.png);}");

			m_maximize->setStyleSheet(
				"QpushButton{qproperty-icon:url(:/icons/tabbedWindow/maximize.png);}"
				"QpushButton:hover{qproperty-icon:url(:/icons/tabbedWindow/maximizeHover.png);}"
				"QpushButton:press{qproperty-icon:url(:/icons/tabbedWindow/maximizePressed.png);}");

			m_close->setStyleSheet(
				"QpushButton{qproperty-icon:url(:/icons/tabbedWindow/close.png);}"
				"QpushButton:hover{qproperty-icon:url(:/icons/tabbedWindow/closeHover.png);}"
				"QpushButton:press{qproperty-icon:url(:/icons/tabbedWindow/closePressed.png);}");
		}

		QWidget* getWidget() override { return this; }

	private:
		QHBoxLayout* m_layout = nullptr;
		QPushButton* m_minimize = nullptr;
		QPushButton* m_maximize = nullptr;
		QPushButton* m_close = nullptr;
	};

	// ---------------------------------------------------------------------------------------------------------
	class WidgetComponent
	{
	public:
		IWidget* widget = nullptr;
	};
}