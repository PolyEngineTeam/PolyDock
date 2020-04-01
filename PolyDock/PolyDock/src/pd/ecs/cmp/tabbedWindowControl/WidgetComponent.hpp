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

			m_minimize->setPixmap(QPixmap(":/icons/tabbedWindow/minimize.png"));
			m_minimize->setAutoFillBackground(true);
			m_maximize->setPixmap(QPixmap(":/icons/tabbedWindow/maximize.png"));
			m_maximize->setAutoFillBackground(true);
			m_close->setPixmap(QPixmap(":/icons/tabbedWindow/close.png"));
			m_close->setAutoFillBackground(true);

			QWidget::setFixedSize(145, 20);

			QPalette pal = QWidget::palette();
			pal.setColor(QPalette::Background, QColor(30, 30, 30));
			QWidget::setAutoFillBackground(true);
			QWidget::setPalette(pal);
		}

		void update(eButton pressed, eButton hovered, bool maximized) final
		{
			QPalette normal = QWidget::palette();
			normal.setColor(QPalette::Background, QColor(30, 30, 30));
			QPalette hover = QWidget::palette();
			hover.setColor(QPalette::Background, QColor(60, 60, 60));
			QPalette press = QWidget::palette();
			press.setColor(QPalette::Background, QColor(90, 90, 90));
			QPalette closeHover = QWidget::palette();
			closeHover.setColor(QPalette::Background, QColor(232, 17, 35));
			QPalette closePress = QWidget::palette();
			closePress.setColor(QPalette::Background, QColor(140, 12, 22));


			{ // eButton::MINIMIZE
				if (pressed == eButton::MINIMIZE)
					m_minimize->setPalette(press);
				else if (hovered == eButton::MINIMIZE)
					m_minimize->setPalette(hover);
				else
					m_minimize->setPalette(normal);
			}
			{ // eButton::MAXIMIZE
				QString part = maximized ? "restore" : "maximize";

				if (pressed == eButton::MAXIMIZE)
					m_maximize->setPalette(press);
				else if (hovered == eButton::MAXIMIZE)
					m_maximize->setPalette(hover);
				else
					m_maximize->setPalette(normal);
			}
			{ // eButton::CLOSE
				if (pressed == eButton::CLOSE)
					m_close->setPalette(closePress);
				else if (hovered == eButton::CLOSE)
					m_close->setPalette(closeHover);
				else
					m_close->setPalette(normal);
			}
		}

		Eigen::AlignedBox2i getWidgetRect() const final
		{
			const QRect rect = QWidget::rect();
			const QPoint globalPos = QWidget::mapToGlobal(rect.topLeft());

			return Eigen::AlignedBox2i(
				Eigen::Vector2i{ globalPos.x(), globalPos.y() },
				Eigen::Vector2i{ rect.width() + globalPos.x(), rect.height() + globalPos.y() });
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

