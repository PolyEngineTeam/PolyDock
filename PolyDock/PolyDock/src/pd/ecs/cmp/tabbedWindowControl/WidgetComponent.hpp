#pragma once

#include <qlabel.h>
#include <qgridlayout.h>

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

		virtual void update(eButton pressed, eButton hovered, bool maximized) = 0;
		virtual Eigen::AlignedBox2i getWidgetRect() const = 0;
		virtual eButton getButtonFromPos(const Eigen::Vector2i& pos) const = 0;

		virtual QWidget* getWidget() = 0;

	};

	// ---------------------------------------------------------------------------------------------------------
	class DefaultWidget : public IWidget, private QWidget
	{
	public:
		DefaultWidget()
			: m_layout(new QGridLayout()), m_minimize(new QLabel()),
				m_maximize(new QLabel()), m_close(new QLabel())
		{
			setLayout(m_layout);
			m_layout->setContentsMargins(0, 0, 0, 0);
			m_layout->setSpacing(0);
			m_layout->addWidget(m_minimize, 0, 0);
			m_layout->addWidget(m_maximize, 0, 1);
			m_layout->addWidget(m_close, 0, 2);
			m_layout->setRowStretch(0, 0);
			m_layout->setRowStretch(1, 1);

			m_minimize->setFixedSize(45, 20);
			m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimize.png"));

			m_maximize->setFixedSize(45, 20);
			m_maximize->setPixmap(QPixmap(":/icons/tabbedWindow/maximize.png"));

			m_close->setFixedSize(45, 20);
			m_close->setPixmap(QPixmap(":/icons/tabbedWindow/close.png"));

			QWidget::setFixedSize(145, 20);
		}

		void update(eButton pressed, eButton hovered, bool maximized) final
		{
			{ // eButton::MINIMIZE
				if (pressed == eButton::MINIMIZE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimizePressed.png"));
				else if (hovered == eButton::MINIMIZE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimizeHover.png"));
				else
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimize.png"));
			}
			{ // eButton::MAXIMIZE
				QString part = maximized ? "restore" : "maximize";

				if (pressed == eButton::MAXIMIZE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/" + part + "Pressed.png"));
				else if (hovered == eButton::MAXIMIZE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/" + part + "Hover.png"));
				else
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/" + part + ".png"));
			}
			{ // eButton::CLOSE
				if (pressed == eButton::CLOSE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/closePressed.png"));
				else if (hovered == eButton::CLOSE)
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/closeHover.png"));
				else
					m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/close.png"));
			}
		}

		Eigen::AlignedBox2i getWidgetRect() const final
		{
			const QRect rect = QWidget::rect();
			const QPoint globalPos = QWidget::mapToGlobal(rect.topLeft());

			return AlignedBox2i(
				Vector2i{ globalPos.x(), globalPos.y() },
				Vector2i{ rect.width() + globalPos.x(), rect.height() + globalPos.y() });
		}

		eButton getButtonFromPos(const Eigen::Vector2i& pos) const final
		{
			eButton result = eButton::NONE;

			const QPoint fromGlobal = QWidget::mapFromGlobal({ pos.x(), pos.y() });

			if (m_minimize->rect().contains(fromGlobal))
				return eButton::MINIMIZE;
			else if (m_maximize->rect().contains(fromGlobal))
				return eButton::MAXIMIZE;
			else if (m_close->rect().contains(fromGlobal))
				return eButton::CLOSE;
			else
				return eButton::NONE;
		}

		QWidget* getWidget() override { return this; }

	private:
		QGridLayout* m_layout = nullptr;
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

