#include <pd/pch/PCH.h>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>

#include <pd/ecs/cmp/root/WidgetsOwner.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::cmp::tabsHeader;

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
void DefaultTabsHeaderWidget::update(std::vector<std::string> names, 
	std::vector<std::optional<QIcon>> icons, std::vector<int> selected, int hovered, int active, 
	eAddButtonState addButtonState)
{
	Expects(names.size() == icons.size());
	Expects(selected.size() <= names.size());
	Expects(hovered < static_cast<int>(names.size()));
	Expects(active < static_cast<int>(names.size()));

	m_names = std::move(names);
	m_icons = std::move(icons);
	m_selected = std::move(selected);
	m_hovered = hovered;
	m_active = active;
	m_addButtonState = addButtonState;

	QWidget::update();
}

// ---------------------------------------------------------------------------------------------------------
int DefaultTabsHeaderWidget::getTabIdxFromPosition(const Vector2i& pos) const
{
	int result = -1;

	const QPoint fromGlobal = QWidget::mapFromGlobal({ pos.x(), pos.y() });

	for (int idx = 0; idx < m_names.size(); ++idx)
	{
		if (getTabRectAtIdx(idx).contains(Vector2i{ fromGlobal.x(), fromGlobal.y() }))
		{
			result = idx;
			break;
		}
	}

	return result;
}

// ---------------------------------------------------------------------------------------------------------
bool DefaultTabsHeaderWidget::isPositionOnTheRightOfLastTab(const Vector2i& pos) const
{
	return getTabRectAtIdx(static_cast<int>(m_names.size()) - 1).max().x() < pos.y();
}

// ---------------------------------------------------------------------------------------------------------
bool DefaultTabsHeaderWidget::hoversAddButton(const Eigen::Vector2i& pos) const
{
	const QPoint fromGlobal = QWidget::mapFromGlobal({ pos.x(), pos.y() });
	return getAddButtonRect().contains(Vector2i{ fromGlobal.x(), fromGlobal.y() });
}

// ---------------------------------------------------------------------------------------------------------
AlignedBox2i DefaultTabsHeaderWidget::getWidgetRect() const
{
	const QRect rect = QWidget::rect();
	const QPoint globalPos = QWidget::mapToGlobal(rect.topLeft());

	return AlignedBox2i(
		Vector2i{ globalPos.x(), globalPos.y() }, 
		Vector2i{ rect.width() + globalPos.x(), rect.height() + globalPos.y() });
}

// ---------------------------------------------------------------------------------------------------------
Vector2i DefaultTabsHeaderWidget::getCursorPosInTabSpace(const Vector2i& pos) const
{
	const int hoveredTab = getTabIdxFromPosition(pos);
	const AlignedBox2i hoveredTabRect = getTabRectAtIdx(hoveredTab);

	return pos - getWidgetRect().min() - hoveredTabRect.min();
}

// Draw an X sign only on the active tab, add a system for handling a hover and a press as before
// ---------------------------------------------------------------------------------------------------------
void DefaultTabsHeaderWidget::paintEvent(QPaintEvent* event)
{
	int mid = 45;
	constexpr int DIFF = 15;

	const int lighter = mid + DIFF;
	const int lightest = mid + 2 * DIFF;
	const int darkest = mid - 2 * DIFF;
	const int darker = mid - DIFF;

	// active tabs gradient
	m_activeTabGradient = QLinearGradient(0, 0, 0, QWidget::height());
	m_activeTabGradient.setSpread(QGradient::RepeatSpread);
	m_activeTabGradient.setColorAt(0, QColor(lightest, lightest, lightest));
	m_activeTabGradient.setColorAt(1, QColor(mid, mid, mid));

	// hovered tabs gradient
	m_hoveredTabGradient = QLinearGradient(0, 0, 0, QWidget::height());
	m_hoveredTabGradient.setSpread(QGradient::RepeatSpread);
	m_hoveredTabGradient.setColorAt(0, QColor(mid, mid, mid));
	m_hoveredTabGradient.setColorAt(0.5, QColor(lighter, lighter, lighter));
	m_hoveredTabGradient.setColorAt(0.97, QColor(darker, darker, darker));
	m_hoveredTabGradient.setColorAt(1, QColor(darker, darker, darker));

	// inactive tabs gradient
	m_inactiveTabGradient = QLinearGradient(0, 0, 0, QWidget::height());
	m_inactiveTabGradient.setSpread(QGradient::RepeatSpread);
	m_inactiveTabGradient.setColorAt(0, QColor(mid, mid, mid));
	m_inactiveTabGradient.setColorAt(0.97, QColor(darker, darker, darker));
	m_inactiveTabGradient.setColorAt(1, QColor(darker, darker, darker));

	// separator gradient
	m_separatorGradient = QLinearGradient(0, 0, 0, QWidget::height());
	m_separatorGradient.setSpread(QGradient::RepeatSpread);
	m_separatorGradient.setColorAt(0, QColor(darkest, darkest, darkest));
	m_separatorGradient.setColorAt(0.97, QColor(darker, darker, darker));
	m_separatorGradient.setColorAt(1, QColor(darker, darker, darker));

	m_tempGradient = QLinearGradient(0, 0, 0, QWidget::height());
	m_tempGradient.setSpread(QGradient::RepeatSpread);
	m_tempGradient.setColorAt(0, QColor(lightest, lightest, lightest));
	m_tempGradient.setColorAt(0.97, QColor(lighter,lighter, lighter));
	m_tempGradient.setColorAt(1, QColor(lighter, lighter, lighter));


	// fill color
	m_filColor = QColor(darker, darker, darker);

	QPainter painter;
	painter.begin(this);
	painter.setFont(QFont("Arial", 9));

	// clear with dark gray
	painter.fillRect(QRect{ 0, 0, QWidget::width(), QWidget::height() }, m_filColor);

	// draw tabs
	const int totalTabsCount = static_cast<int>(m_names.size());
	const int tabWidth = getTabWidth();
	for (int i = 0; i < totalTabsCount; ++i)
	{
		// draw spacer
		if (i > 0)
		{
			const AlignedBox2i rect = getSeparatorRectAtIdx(i);
			painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().y(), rect.sizes().y()), m_separatorGradient);
		}

		// draw tab background
		if (i == m_active)
		{
			const AlignedBox2i rect = getTabRectAtIdx(i);
			painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_activeTabGradient);
		}
		else
		{
			if (i == m_hovered)
			{
				const AlignedBox2i rect = getTabRectAtIdx(i);
				painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_hoveredTabGradient);
			}
			else
			{
				const AlignedBox2i rect = getTabRectAtIdx(i);
				painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_inactiveTabGradient);
			}
		}

		// draw tab title
		{
			const AlignedBox2i rect = getTextRectAtIdx(i);
			painter.drawText(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), 0, QString::fromStdString(m_names[i]));
		}
	}

	const AlignedBox2i rect = getAddButtonRect();
	switch (m_addButtonState)
	{
		case eAddButtonState::IDLE:
		painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_inactiveTabGradient);
		break;

		case eAddButtonState::HOVERED:
		painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_hoveredTabGradient);
		break;

		case eAddButtonState::PRESSED:
		painter.fillRect(QRect(rect.min().x(), rect.min().y(), rect.sizes().x(), rect.sizes().y()), m_activeTabGradient);
		break;
	}

	QPainterPath path;
	path.moveTo(rect.center().x(), rect.min().y() + 4);
	path.lineTo(rect.center().x(), rect.max().y() - 4);
	path.moveTo(rect.min().x() + 4, rect.center().y());
	path.lineTo(rect.max().x() - 4, rect.center().y());
	painter.drawPath(path);

	painter.end();
}

// ---------------------------------------------------------------------------------------------------------
AlignedBox2i DefaultTabsHeaderWidget::getTabRectAtIdx(int idx) const
{
	const int left = (getTabWidth() + m_separatorWidth) * idx;
	return AlignedBox2i(
		Vector2i{ left, 0 }, 
		Vector2i{ getTabWidth() + left, QWidget::height() });
}

// ---------------------------------------------------------------------------------------------------------
AlignedBox2i DefaultTabsHeaderWidget::getTextRectAtIdx(int idx) const
{
	const AlignedBox2i tabRect = getTabRectAtIdx(idx);
	const bool withIcon = m_icons[idx].has_value();

	const int left = tabRect.min().x() + (withIcon ? QWidget::height() : (QWidget::height() / 3));
	const int top = tabRect.min().y() + QWidget::height() / 3;
	const int right = tabRect.sizes().x() - QWidget::height();
	const int bottom = tabRect.sizes().y() - QWidget::height() / 3;
	return AlignedBox2i(
		Vector2i{ left, top }, 
		Vector2i{ right + left, bottom + top });
}

// ---------------------------------------------------------------------------------------------------------
AlignedBox2i DefaultTabsHeaderWidget::getSeparatorRectAtIdx(int idx) const
{
	const int left = (getTabWidth() + m_separatorWidth) * idx - m_separatorWidth;
	return AlignedBox2i(
		Vector2i{ left, 0 }, 
		Vector2i{ m_separatorWidth + left, QWidget::height() });
}

// ---------------------------------------------------------------------------------------------------------
AlignedBox2i DefaultTabsHeaderWidget::getAddButtonRect() const
{
	const AlignedBox2i lastTab = getTabRectAtIdx(static_cast<int>(m_names.size() > 0 ? m_names.size() - 1 : 0));
	const int left = lastTab.min().x() + lastTab.sizes().x() + m_separatorWidth;
	const int top = (QWidget::height() - m_interactiveBoxSize.y()) / 2;
	return AlignedBox2i(
		Vector2i{ left, top },
		Vector2i{ left + m_interactiveBoxSize.x(), top + m_interactiveBoxSize.y() });
}

// ---------------------------------------------------------------------------------------------------------
int DefaultTabsHeaderWidget::getTabWidth() const
{
	if (m_names.size() * (m_maxTabWidth + m_separatorWidth) + m_separatorWidth <= QWidget::width())
		return m_maxTabWidth;
	else
		return getAlternativeTabWidth();
}

// ---------------------------------------------------------------------------------------------------------
int DefaultTabsHeaderWidget::getAlternativeTabWidth() const
{
	const int newAllTabsWidth = QWidget::width() - (static_cast<int>(m_names.size() + 10) * m_separatorWidth);
	return newAllTabsWidth / static_cast<int>(m_names.size());
}