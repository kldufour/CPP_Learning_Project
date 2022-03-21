#include "aircraft_manager.hpp"

#include <algorithm>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    // for (auto it = aircrafts.begin(); it != aircrafts.end();)
    // {
    //     auto& aircraft = **it;
    //     if (aircraft.update())
    //     {
    //         ++it;
    //     }
    //     else
    //     {
    //         it = aircrafts.erase(it);
    //     }
    // }

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](std::unique_ptr<Aircraft>& aircraft) { return !aircraft->update(); }),
                    aircrafts.end());

    return true;
}
int AircraftManager::count_aircraft(const std::string& airline)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [airline](std::unique_ptr<Aircraft>& aircraft)
                         { return aircraft->get_flight_num().rfind(airline, 0) == 0; });
}