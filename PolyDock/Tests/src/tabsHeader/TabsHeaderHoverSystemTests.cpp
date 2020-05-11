#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsHeader.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidget.hpp>
// misc
#include <pd/ecs/cmp/tab/TabComponent.hpp>
// mock
#include <mocks/MockTabsHeaderWidget.hpp>

using namespace ::Eigen;
using namespace ::pd::ecs::sys;
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
		auto& input = reg.assign<Input>(root);

		input.setNewCursorPos({ 0, 0 });
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupTabsHeader()
	{
		auto& headerCmp = reg.assign<::pd::ecs::cmp::tabsHeader::Component>(header, std::vector<entt::entity>{ tab0, tab1 });
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupTabsHeaderWidget()
	{
		reg.assign<Widget>(header, &mock);
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

	ASSERT_TRUE(reg.has<HoveredTab>(header));
	EXPECT_TRUE(reg.has<HoveredHeader>(header));
	EXPECT_TRUE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_EQ(reg.get<HoveredTab>(header).hoveredTab, tab0);
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsHeaderHoverSystemTest, SetHover_WithMouseOverSecondTab)
{
	setupInput();
	setupTabsHeader();
	setupTabsHeaderWidget();

	EXPECT_CALL(mock, getTabIdxFromPosition(Vector2i{ 0, 0 })).WillOnce(Return(1));

	sys.update(reg, root);

	ASSERT_TRUE(reg.has<HoveredTab>(header));
	EXPECT_TRUE(reg.has<HoveredHeader>(header));
	EXPECT_TRUE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_EQ(reg.get<HoveredTab>(header).hoveredTab, tab1);
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

	EXPECT_TRUE(reg.has<HoveredHeader>(header));
	EXPECT_FALSE(reg.has<HoveredTab>(header));
	EXPECT_FALSE(reg.has<WidgetUpdateRequest>(header));
}