#include <cts-core/base/log.h>
#include <cts-core/network/network.h>
#include <cts-core/simulation/simulation.h>
#include <cts-gui/networkrenderwidget.h>
#include <cts-gui/scripting/scriptingwidget.h>

#include <cts-gui/mainwindow.h>
#include <cts-gui/networkrenderwidget.h>

#include <cts-lua/cts-lua.h>

#include <QtWidgets/QApplication>

#include <lua.hpp>
#include <sol.hpp>

int main(int argc, char** argv)
{
	auto cs = std::make_unique<cts::core::ConsoleLogger>(false, true);
	cts::core::LogManager::get().addLogger(std::move(cs));

	cts::core::Network network;
	network.importLegacyXml("intersection.xml");
	//network.importLegacyXml("minimal.xml");
	//network.importLegacyXml("network.xml");

	cts::core::Simulation simulation(network);
	simulation.start(1000);

	QApplication app(argc, argv);
	cts::gui::MainWindow mw;
	mw.getNetworkRenderWidget()->setNetwork(&network);
	mw.getNetworkRenderWidget()->setSimulation(&simulation);
	mw.show();
	mw.showMaximized();

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::table, sol::lib::string, sol::lib::utf8);
	lua.script_file("inspect.lua");
	lua["n"] = &network;
	lua["s"] = &renderWidget.getSimulation();

	cts::lua::Registration::registerWith(lua);
	auto sw = new cts::gui::ScriptingWidget(lua);
	sw->show();

	return app.exec();
}
