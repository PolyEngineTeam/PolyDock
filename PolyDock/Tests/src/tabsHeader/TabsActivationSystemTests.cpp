#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsMovement.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeader.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>
// out
#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
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
		auto& input = reg.assign<Input>(root);

		input.setNewCursorPos({ 0, 0 });
		Input::ButtonStateArrayType buttonsState = { false };
		buttonsState[static_cast<int>(Input::eMouseButton::LEFT)] = true;
		input.setNewButtonState(std::move(buttonsState));
	}

	// ---------------------------------------------------------------------------------------------------------
	void setupHoveredTab()
	{
		auto& hoveredCmp = reg.assign<HoveredTab>(header);
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

	ASSERT_TRUE(reg.has<ActiveTab>(header));
	EXPECT_TRUE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_TRUE(reg.has<RequestWidgetUpdate>(header));
	EXPECT_EQ(reg.get<ActiveTab>(header).activeTab, tab0);
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutMousePress)
{
	setupHoveredTab();

	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTab>(header));
	EXPECT_FALSE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_FALSE(reg.has<RequestWidgetUpdate>(header));
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutHoveredTab)
{
	setupInput();

	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTab>(header));
	EXPECT_FALSE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_FALSE(reg.has<RequestWidgetUpdate>(header));
}

// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsActivationSystemTest, DontUpdateActiveTab_WithoutMousePressNorHoveredTab)
{
	sys.update(reg, root);

	EXPECT_FALSE(reg.has<ActiveTab>(header));
	EXPECT_FALSE(reg.has<WidgetUpdateRequest>(header));
	EXPECT_FALSE(reg.has<RequestWidgetUpdate>(header));
}