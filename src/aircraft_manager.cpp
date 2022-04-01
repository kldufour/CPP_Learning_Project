#include "aircraft_manager.hpp"

#include <algorithm>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft != nullptr);
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const std::unique_ptr<Aircraft>& a1, const std::unique_ptr<Aircraft>& a2)
              {
                  return std::make_tuple(!a1->has_terminal(), a1->get_fuel()) <
                         std::make_tuple(!a2->has_terminal(), a2->get_fuel());
              });

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