#include <pd/pch/PCH.h>
#include <pd/PolyDockRegistry.hpp>

#include <pd/ecs/cmp/tabbedWindow/TabbedWindow.hpp>
#include <pd/ecs/cmp/tabsHeader/TabsHeader.hpp>

// input
#include <pd/ecs/sys/root/InputSystem.hpp>
#include <pd/ecs/sys/root/DesktopSystem.hpp>
// tabs header - no mode
#include <pd/ecs/sys/tabsHeader/TabsHeader.hpp>
// tabbed window control no mode
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControl.hpp>
// tabbed window focus
#include <pd/ecs/sys/tabbedWindow/TabbedWindow.hpp>
// tabbed window resize
#include <pd/ecs/sys/tabbedWindow/TabbedWindowSnapping.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowResizing.hpp>
// tabbed window movement
#include <pd/ecs/sys/tabbedWindow/TabbedWindowMovement.hpp>
// tabs movement
#include <pd/ecs/sys/tabsHeader/TabsMovement.hpp>
// tabs drag in
#include <pd/ecs/sys/tabsHeader/TabsDraggingInOut.hpp>
// tabbed window control widget support
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetInitialization.hpp>
#include <pd/ecs/sys/tabbedWindowControl/TabbedWindowControlWidgetUpdate.hpp>
// tabs header widget support
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetInitialization.hpp>
#include <pd/ecs/sys/tabsHeader/TabsHeaderWidgetUpdate.hpp>
// tabbed window widget support
#include <pd/ecs/sys/tabbedWindow/TabbedWindowClosing.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowOpening.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetInitialization.hpp>
#include <pd/ecs/sys/tabbedWindow/TabbedWindowWidgetUpdate.hpp>
// tab adding support
#include <pd/ecs/sys/tabsHeader/TabsAdding.hpp>
// tab removing support
#include <pd/ecs/sys/tabsHeader/TabsRemoving.hpp>

// dock widget support

// root components
#include <pd/ecs/cmp/root/Desktop.hpp>
#include <pd/ecs/cmp/root/Input.hpp>
#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
// window creation
#include <pd/ecs/cmp/tabbedWindow/Opening.hpp>
// dock
#include <pd/ecs/cmp/dock/Dock.hpp>

using namespace ::Eigen;
using namespace ::pd;

static void registerQtResources()
{
	Q_INIT_RESOURCE(Resource);
}

// ---------------------------------------------------------------------------------------------------------
PolyDockRegistry::PolyDockRegistry()
{
	registerQtResources();

	m_root = m_registry.create();
	m_registry.assign<ecs::cmp::root::Desktop>(m_root);
	m_registry.assign<ecs::cmp::root::Input>(m_root);
	m_registry.assign<ecs::cmp::root::WidgetsOwner>(m_root);

	// root
	auto inputSystem = std::make_unique<ecs::sys::InputSystem>();
	qApp->installEventFilter(inputSystem.get());
	m_systems.push_back(std::move(inputSystem));
	m_systems.push_back(std::make_unique<ecs::sys::DesktopSystem>());
	// tabs header - no mode
	m_systems.push_back(std::make_unique<ecs::sys::TabsSelectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsActivationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsHeaderHoverSystem>());
	// tabbed window control no mode
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowControlHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowControlReleaseSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowControlPressSystem>());
	// tabbed window focus
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowFocusSystem>());
	// tabbed window resize
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowSnapSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowRestoreSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMinimizeSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMaximizeSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowResizeHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowResizeStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowResizeDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowResizeEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowResizeSystem>());
	// tabbed window movement
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMovementStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMovementDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMovementEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowMovementSystem>());
	// tabs movement
	m_systems.push_back(std::make_unique<ecs::sys::TabsMovementStartSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsMovementDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsMovementEndSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsMovementSystem>());
	// tabs drag in
	m_systems.push_back(std::make_unique<ecs::sys::TabsDragInDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsDragInSystem>());
	// tabs drag out
	m_systems.push_back(std::make_unique<ecs::sys::TabsDragOutDetectionSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsDragOutSystem>());
	// tab adding
	m_systems.push_back(std::make_unique<ecs::sys::AddButtonHoverSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::AddButtonPressSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsCreationSystem>());
	// tabbed window control widget support
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowControlWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowControlWidgetUpdateSystem>());
	// tabs header widget support
	m_systems.push_back(std::make_unique<ecs::sys::TabsHeaderWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabsHeaderWidgetUpdateSystem>());
	// tabbed window widget support
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowCloseSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowRemovalSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowCreationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowWidgetInitializationSystem>());
	m_systems.push_back(std::make_unique<ecs::sys::TabbedWindowWidgetUpdateSystem>());

	//-----------------------------------------------------------------------------------------
	// Late systems
	//-----------------------------------------------------------------------------------------
	// tab removing
	m_lateSystems.push_back(std::make_unique<ecs::sys::TabsRemovalSystem>());
	m_lateSystems.push_back(std::make_unique<ecs::sys::TabsHeaderWidgetUpdateSystem>()); // needs to update state after removing and before TabsHeaderHoverSystem

	QObject::connect(&m_timer, &QTimer::timeout, this, [this]() { update(); lateUpdate(); });

	m_timer.start(10);
}

// ---------------------------------------------------------------------------------------------------------
PolyDockRegistry::~PolyDockRegistry()
{
}

// ---------------------------------------------------------------------------------------------------------
TabbedWindowHandle PolyDockRegistry::createWindow()
{
	auto windowEntity = m_registry.create();
	auto header = TabsHeaderHandle(m_registry, windowEntity);
	auto control = TabbedWindowControlHandle(m_registry, windowEntity);
	auto window = TabbedWindowHandle(header, control);

	m_registry.assign<ecs::cmp::tabbedWindow::CreateRequest>(windowEntity,
		std::vector<entt::entity>{}, std::vector<entt::entity>{}, std::optional<entt::entity>{},
		Vector2i{ 100, 100 }, Vector2i{ 500, 500 });

	update();

	return window;
}

// ---------------------------------------------------------------------------------------------------------
DockWidgetHandle pd::PolyDockRegistry::createDockWidget()
{
	auto dockEntity = m_registry.create();
	auto window = DockWidgetHandle(m_registry, dockEntity);

	m_registry.assign<ecs::cmp::dock::Component>(dockEntity);

	update();

	return window;
}

// ---------------------------------------------------------------------------------------------------------
void pd::PolyDockRegistry::update()
{
	for (const std::unique_ptr<ecs::sys::SystemBase>& system : m_systems)
		system->update(m_registry, m_root);
}

void pd::PolyDockRegistry::lateUpdate()
{
	for (const std::unique_ptr<ecs::sys::SystemBase>& system : m_lateSystems)
		system->update(m_registry, m_root);
}
