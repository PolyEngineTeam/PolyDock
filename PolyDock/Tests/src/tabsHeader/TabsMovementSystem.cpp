#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsHeader.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// misc
#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::tab;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
class TabsSelectionSystemTest : public ::testing::Test
{
public:
	TabsSelectionSystemTest()
	{
		root = reg.create();
		header = reg.create();
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupInput()
	{
		auto& input = reg.assign<Input>(root);

		input.setNewCursorPos({ 0, 0 });
		Input::KeyStateContainer<Input::eMouse> buttonsState = { false };
		buttonsState[static_cast<int>(Input::eMouse::LEFT)] = true;
		input.setNewKeysState(std::move(buttonsState));
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupHoveredTab()
	{
		auto& hoveredCmp = reg.assign<HoveredTab>(header);
		tab0 = reg.create();
		hoveredCmp.hoveredTab = tab0;
	}

	TabsSelectionSystem sys;
	entt::registry reg;

	entt::entity root;
	entt::entity header;
	entt::entity tab0;

private:
};

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
//TEST_F(TabsSelectionSystemTest, UpdateSelection_OnMousePressWithHoveredTab)
//{
//	setupInput();
//	setupHoveredTab();
//
//	sys.update(reg, root);
//
//	ASSERT_TRUE(reg.has<SelectedTabs>(header));
//	EXPECT_TRUE(reg.has<WidgetUpdateRequest>(header));
//	EXPECT_EQ(reg.get<SelectedTabs>(header).selectedTabs.size(), 1);
//	EXPECT_EQ(reg.get<SelectedTabs>(header).selectedTabs.at(0), tab0);
//}