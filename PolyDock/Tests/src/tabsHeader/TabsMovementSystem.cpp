#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsSelectionSystem.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
// misc
#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd::ecs::sys::tabsHeader;
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
		auto& input = reg.assign<InputComponent>(root);

		input.setNewCursorPos({ 0, 0 });
		InputComponent::ButtonStateArrayType buttonsState = { false };
		buttonsState[static_cast<int>(InputComponent::eMouseButton::LEFT)] = true;
		input.setNewButtonState(std::move(buttonsState));
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupHoveredTab()
	{
		auto& hoveredCmp = reg.assign<HoveredTabComponent>(header);
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
//	ASSERT_TRUE(reg.has<SelectedTabsComponent>(header));
//	EXPECT_TRUE(reg.has<DirtyTabsHeaderComponent>(header));
//	EXPECT_EQ(reg.get<SelectedTabsComponent>(header).selectedTabs.size(), 1);
//	EXPECT_EQ(reg.get<SelectedTabsComponent>(header).selectedTabs.at(0), tab0);
//}