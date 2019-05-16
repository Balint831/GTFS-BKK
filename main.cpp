#include "header.h"
#include <chrono>


struct no_routes{};
struct no_stops{};
struct no_stop_times{};
struct no_cal_dates{};
struct no_trips{};

int main()
{

    auto t1 = std::chrono::high_resolution_clock::now();
    std::ifstream routes_input("data/routes.txt");
    std::ifstream stops_input("data/stops.txt");
    std::ifstream stop_times_input("data/stop_times.txt");
    std::ifstream cal_dates_input("data/calendar_dates.txt");
    std::ifstream trips_input("data/trips.txt");
    std::ifstream shapes_input("data/shapes.txt");
    if (!routes_input.is_open()){std::cout << "Couldn't open routes' input file.\n"; return 1;}
    if (!stops_input.is_open()){std::cout << "Couldn't open stops' input file.\n"; return 1;}
    if (!stop_times_input.is_open()){std::cout << "Couldn't open stop times' input file.\n"; return 1;}
    if (!cal_dates_input.is_open()){std::cout << "Couldn't open calendar dates' input file.\n"; return 1;}
    if (!trips_input.is_open()){std::cout << "Couldn't open trips' input file.\n"; return 1;}
    if (!shapes_input.is_open()){std::cout << "Couldn't open shapes' input file.\n"; return 1;}
    
    
    std::cout << "Reading routes...";
    std::vector<Route>      routes      = scan_routes(routes_input);
    std::cout << "done.\n";
    std::cout << "Reading stops...";
    std::vector<Stop>       stops       = scan_stops(stops_input);  
    std::cout << "done.\n";
    std::cout << "Reading stop times...";
    std::vector<Stop_time>  stop_times  = scan_stop_times(stop_times_input);
    std::cout << "done.\n";
    std::cout << "Reading calendar dates...";
    std::vector<Cal_date>   cal_dates   = scan_cal_dates(cal_dates_input);
    std::cout << "done.\n";
    std::cout << "Reading trips...";
    std::vector<Trip>       trips       = scan_trips(trips_input);
    std::cout << "done.\n";
    std::cout << "Reading shapes...";
    std::vector<Shape>       shapes     = scan_shapes(shapes_input);
    std::cout << "done.\n";

    std::cout << "\nMean of transport:\tTram\tMetro\tBus\tFerry\tSuburban rail\tTrolleybus\n";
    std::cout << "Longest distance route:\t" << longest_route_distance(routes,trips,shapes,0) << "\t" <<
    longest_route_distance(routes,trips,shapes,1) << " \t" <<
    longest_route_distance(routes,trips,shapes,3) << " \t"<<
    longest_route_distance(routes,trips,shapes,4) << " \t"<<
    longest_route_distance(routes,trips,shapes,109) << " \t\t"<<
    longest_route_distance(routes,trips,shapes,800) << "\n" << 
    "Route with most stops:\t" <<
    most_stops(routes,trips,stop_times,0) << "\t" <<
    most_stops(routes,trips,stop_times,1) << "\t" <<
    most_stops(routes,trips,stop_times,3) << "\t" <<
    most_stops(routes,trips,stop_times,4) << "\t" <<
    most_stops(routes,trips,stop_times,109) <<"\t\t" <<
    most_stops(routes,trips,stop_times,800) <<"\n" <<
    "Number of stops:\t" <<
    how_many(routes, trips, stop_times, 0) << "\t" <<
    how_many(routes, trips, stop_times, 1) << "\t" <<
    how_many(routes, trips, stop_times, 3) << "\t" <<
    how_many(routes, trips, stop_times, 4) << "\t" <<
    how_many(routes, trips, stop_times, 109) << "\t\t" <<
    how_many(routes, trips, stop_times, 800) << "\t";


    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "\nRun time: " << (static_cast<std::chrono::duration<double, std::milli>>(t2-t1)).count() << " ms";


    return 0;
}