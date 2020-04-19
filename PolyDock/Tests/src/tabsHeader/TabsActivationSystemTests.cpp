#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsActivationSystem.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/ActiveTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/DirtyTabsHeaderComponent.hpp>
#include <pd/ecs/cmp/tabbedWindow/DirtyTabbedWindowComponent.hpp>
// misc
#include <pd/ecs/cmp/tab/TabComponent.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::tabbedWindow;
using namespace ::pd::ecs::cmp::tabsHeader;
using namespace ::pd::ecs::cmp::tab;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
class TabsActivationSystemTest : public ::testing::Test
{
public:
	TabsActivationSystemTest()
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

	TabsActivationSystem sys;
	entt::registry reg;

	entt::entity root;
	entt::entity header;
	entt::entity tab0;

private:
};

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, UpdateActiveTab_OnMousePressWithHoveredTab)
{
	setupInput();
	setupHoveredTab();

	sys.update(reg, root);

	ASSERT_TRUE(reg.has<ActiveTabComponent>(header));
	EXPECT_TRUE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_TRUE(reg.has<DirtyTabbedWindowComponent>(header));
	EXPECT_EQ(reg.get<ActiveTabComponent>(header).activeTab, tab0);
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutMousePress)
{
	setupHoveredTab();

	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTabComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabbedWindowComponent>(header));
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutHoveredTab)
{
	setupInput();

	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTabComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabbedWindowComponent>(header));
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutMousePressNorHoveredTab)
{
	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTabComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabsHeaderComponent>(header));
	EXPECT_FALSE(reg.has<DirtyTabbedWindowComponent>(header));
}