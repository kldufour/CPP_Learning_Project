#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "aircraft_factory.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c',
                           [this]() { aircraft_manager.add(factory->create_random_aircraft(*airport)); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('u', []() { GL::up_framerate(); });
    GL::keystrokes.emplace('d', []() { GL::down_framerate(); });
    GL::keystrokes.emplace('p', []() { GL::set_pause(); });

    // Display numbers of aicraft in specify airlines
    GL::keystrokes.emplace(
        '0', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[0]) << std::endl; });
    GL::keystrokes.emplace(
        '1', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[1]) << std::endl; });
    GL::keystrokes.emplace(
        '2', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[2]) << std::endl; });
    GL::keystrokes.emplace(
        '3', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[3]) << std::endl; });
    GL::keystrokes.emplace(
        '4', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[4]) << std::endl; });
    GL::keystrokes.emplace(
        '5', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[5]) << std::endl; });
    GL::keystrokes.emplace(
        '6', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[6]) << std::endl; });
    GL::keystrokes.emplace(
        '7', [this]() { std::cout << aircraft_manager.count_aircraft(factory->airlines[7]) << std::endl; });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, function] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::move_queue.emplace(airport);
    GL::move_queue.emplace(&aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();

    factory = new AircraftFactory();

    GL::loop();
}
