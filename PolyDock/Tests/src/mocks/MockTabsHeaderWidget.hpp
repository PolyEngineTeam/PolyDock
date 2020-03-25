#include <gmock/gmock.h>

#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>

// ---------------------------------------------------------------------------------------------------------
class MockTabsHeaderWidget : public pd::ecs::cmp::tabsHeader::ITabsHeaderWidget
{
public:
	MOCK_METHOD(void, update, (std::vector<std::string>, std::vector<std::optional<QIcon>>,
		std::vector<int>, int, int), (override));
	MOCK_METHOD(int, getTabIdxFromPosition, (const pd::Eigen::Vector2i&), (const, override));
	MOCK_METHOD(pd::Eigen::AlignedBox2i, getWidgetRect, (), (const, override));
	MOCK_METHOD(pd::Eigen::Vector2i, getCursorPosInTabSpace, (const pd::Eigen::Vector2i&), (const, override));
	MOCK_METHOD(QWidget*, getWidget, (), (override));
};