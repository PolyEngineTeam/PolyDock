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

using namespace ::Eigen;
using namespace ::pd::ecs::sys::tabsHeader;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::tab;
using namespace ::pd::ecs::cmp::root;

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
	}

	// ---------------------------------------------------------------------------------------------------------
	void activateMovementSystem()
	{
		auto& input = reg.assign<InputComponent>(root);

		input.setNewCursorPos({ 0, 0 });
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupActiveTab()
	{
		auto& input = reg.assign<InputComponent>(root);

		input.setNewCursorPos({ 0, 0 });
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupHoveredTab()
	{
		auto& headerCmp = reg.assign<TabsHeaderComponent>(header);
		headerCmp.tabs.push_back(tab0);
	}

	TabsHeaderHoverSystem sys;
	entt::registry reg;

	entt::entity root;
	entt::entity header;
	entt::entity tab0;
};

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
//TEST_F(TabsHeaderHoverSystemTest, SetHover_WithMouseOverFirstTab)
//{
//	setupInput();
//	setupTabsHeader();
//	setupTabsHeaderWidget();
//
//	EXPECT_CALL(mock, getTabIdxFromPosition(Vector2i{ 0, 0 })).WillOnce(Return(0));
//
//	sys.update(reg, root);
//
//	ASSERT_TRUE(reg.has<HoveredTabComponent>(header));
//	EXPECT_TRUE(reg.has<HoveredTabsHeaderComponent>(header));
//	EXPECT_TRUE(reg.has<DirtyTabsHeaderComponent>(header));
//	EXPECT_EQ(reg.get<HoveredTabComponent>(header).hoveredTab, tab0);
//}