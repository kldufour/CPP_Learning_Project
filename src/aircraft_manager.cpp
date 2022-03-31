#include "aircraft_manager.hpp"

#include <algorithm>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(), [](Aircraft& a1, Aircraft& a2) { a1 < a2; });

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