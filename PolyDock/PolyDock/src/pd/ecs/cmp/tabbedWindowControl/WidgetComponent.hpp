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
			: m_layout(new QHBoxLayout()), m_minimize(new QLabel()), 
				m_maximize(new QLabel()), m_close(new QLabel())
		{
			setLayout(m_layout);
			m_layout->setContentsMargins(0, 0, 0, 0);
			m_layout->setSpacing(0);
			m_layout->addWidget(m_minimize);
			m_layout->addWidget(m_maximize);
			m_layout->addWidget(m_close);

			m_minimize->setFixedSize(45, 20);
			m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimize.png"));

			m_maximize->setFixedSize(45, 20);
			m_maximize->setPixmap(QPixmap(":/icons/tabbedWindow/maximize.png"));

			m_close->setFixedSize(45, 20);
			m_close->setPixmap(QPixmap(":/icons/tabbedWindow/close.png"));

			QWidget::setFixedSize(145, 20);
		}

		QWidget* getWidget() override { return this; }

	private:
		QHBoxLayout* m_layout = nullptr;
		QLabel* m_minimize = nullptr;
		QLabel* m_maximize = nullptr;
		QLabel* m_close = nullptr;
	};

	// ---------------------------------------------------------------------------------------------------------
	class WidgetComponent
	{
	public:
		IWidget* widget = nullptr;
	};
}

