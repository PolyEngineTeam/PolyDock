#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsHeaderHoverSystem.hpp>
// in
#include <pd/ecs/cmp/root/InputComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
// misc
#include <pd/ecs/cmp/tab/TabComponent.hpp>
// mock
#include <mocks/MockTabsHeaderWidget.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::tab;
using namespace ::pd::ecs::cmp::root;
using ::testing::Return;

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
class TabsHeaderHoverSystemTest : public ::testing::Test
{
public:
	// ---------------------------------------------------------------------------------------------------------
	TabsHeaderHoverSystemTest()
	{
		root = reg.create();
		header = reg.create();
		tab0 = reg.create();
		tab1 = reg.create();
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupInput()
	{
		auto& input = reg.assign<InputComponent>(root);

		input.setNewCursorPos({ 0, 0 });
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupTabsHeader()
	{
		auto& headerCmp = reg.assign<TabsHeaderComponent>(header);
		headerCmp.tabs.push_back(tab0);
		headerCmp.tabs.push_back(tab1);
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupTabsHeaderWidget()
	{
		reg.assign<TabsHeaderWidgetComponent>(header, &mock);
	}

	TabsHeaderHoverSystem sys;
	entt::registry reg;
	MockTabsHeaderWidget mock;

	entt::entity root;
	entt::entity header;
	entt::entity tab0;
	entt::entity tab1;
};

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsHeaderHoverSystemTest, SetHover_WithMouseOverFirstTab)
{
	setupInput();
	setupTabsHeader();
	setupTabsHeaderWidget();

	EXPECT_CALL(mock, getTabIdxFromPosition(Vector2i{ 0, 0 })).WillOnce(Return(0));

	sys.update(reg, root);

	ASSERT_TRUE(reg.has<HoveredTabComponent>(header));
	EXPECT_TRUE(reg.has<HoveredTabsHeaderComponent>(header));
	EXPECT_TRUE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_EQ(reg.get<HoveredTabComponent>(header).hoveredTab, tab0);
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsHeaderHoverSystemTest, SetHover_WithMouseOverSecondTab)
{
	setupInput();
	setupTabsHeader();
	setupTabsHeaderWidget();

	EXPECT_CALL(mock, getTabIdxFromPosition(Vector2i{ 0, 0 })).WillOnce(Return(1));

	sys.update(reg, root);

	ASSERT_TRUE(reg.has<HoveredTabComponent>(header));
	EXPECT_TRUE(reg.has<HoveredTabsHeaderComponent>(header));
	EXPECT_TRUE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_EQ(reg.get<HoveredTabComponent>(header).hoveredTab, tab1);
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsHeaderHoverSystemTest, SetHover_WithMouseOverJustTabsHeader)
{
	setupInput();
	setupTabsHeader();
	setupTabsHeaderWidget();

	EXPECT_CALL(mock, getTabIdxFromPosition(Vector2i{ 0, 0 })).WillOnce(Return(-1));
	EXPECT_CALL(mock, getWidgetRect()).WillOnce(Return(AlignedBox2i{ Vector2i{ -1, -1 }, Vector2i{ 1, 1 } }));

	sys.update(reg, root);

	EXPECT_TRUE(reg.has<HoveredTabsHeaderComponent>(header));
	EXPECT_FALSE(reg.has<HoveredTabComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabsHeaderComponent>(header));
}