#include <gmock/gmock.h>

#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>

// ---------------------------------------------------------------------------------------------------------
class MockTabsHeaderWidget : public pd::ecs::cmp::tabsHeader::ITabsHeaderWidget
{
public:
	MOCK_METHOD(void, update, (std::vector<std::string>, std::vector<std::optional<QIcon>>,
		std::vector<int>, int, int, eAddButtonState), (override));
	MOCK_METHOD(int, getTabIdxFromPosition, (const Eigen::Vector2i&), (const, override));
	MOCK_METHOD(bool, isPositionOnTheRightOfLastTab, (const Eigen::Vector2i& pos), (const, override));
	MOCK_METHOD(bool, hoversAddButton, (const Eigen::Vector2i& pos), (const override));
	MOCK_METHOD(Eigen::AlignedBox2i, getWidgetRect, (), (const, override));
	MOCK_METHOD(Eigen::Vector2i, getCursorPosInTabSpace, (const Eigen::Vector2i&), (const, override));
	MOCK_METHOD(QWidget*, getWidget, (), (override));
};