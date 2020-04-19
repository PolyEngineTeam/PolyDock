#include <gtest/gtest.h>
#include <gmock/gmock.h>

// sys
#include <pd/ecs/sys/tabsHeader/TabsMovementStartSystem.hpp>
// in
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/tabsHeader/HoveredTabComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/SelectedTabsComponent.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeaderWidgetComponent.hpp>
// out
#include <pd/ecs/cmp/tabsHeader/TabsMovementActiveComponent.hpp>
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
class TabsMovementStartSystemTest : public ::testing::Test
{
public:
	TabsMovementStartSystemTest()
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

	// ---------------------------------------------------------------------------------------------------------
	void setupTabsHeaderWidget()
	{
		reg.assign<TabsHeaderWidgetComponent>(header, &mock);
	}

	TabsMovementStartSystem sys;
	entt::registry reg;
	MockTabsHeaderWidget mock;

	entt::entity root;
	entt::entity header;
	entt::entity tab0;

private:
};

// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
TEST_F(TabsMovementStartSystemTest, UpdateActiveTab_OnMousePressWithHoveredTab)
{
	setupInput();
	setupHoveredTab();
	setupTabsHeaderWidget();

	const auto cursorPosInTabSpace = Vector2i{ -5, -5 };
	EXPECT_CALL(mock, getCursorPosInTabSpace(Vector2i{ 0, 0 })).WillOnce(Return(cursorPosInTabSpace));

	sys.update(reg, root);

	ASSERT_TRUE(reg.has<TabsMovementActiveComponent>(header));
	EXPECT_EQ(reg.get<TabsMovementActiveComponent>(header).cursorInTabSpacePosition, cursorPosInTabSpace);
}