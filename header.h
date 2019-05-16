#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <execution>

auto cmpr = [](auto &lhs, auto &rhs){ return lhs.route_id < rhs.route_id; };
auto cmpt = [](auto &lhs, auto &rhs){ return lhs.trip_id < rhs.trip_id; };


struct Route
{
    std::string agency_id;
    std::string route_id;
    std::string route_short_name;
    std::string route_long_name;
    std::string route_type;
    std::string route_desc;
    std::string route_color;
    std::string route_text_color;
};

std::ostream& operator<<( std::ostream& o, Route const& A )
{
    
    o << A.agency_id << "--";
    o << A.route_id << "--";
    o << A.route_short_name << "--";
    o << A.route_long_name << "--";
    o << A.route_type << "--";
    o << A.route_desc << "--";
    o << A.route_color << "--"; 
    o << A.route_text_color << "\n";
    return o;   
}


struct Stop
{
    std::string stop_id;
    std::string stop_name;
    std::string stop_lat;
    std::string stop_lon;
    std::string stop_code;
    std::string location_type;
    std::string parent_station;
    std::string wheelchair_boarding;
    std::string stop_direction;
};

std::ostream& operator<<( std::ostream& o, Stop const& A )
{
    
    o << A.stop_id << "--";
    o << A.stop_name << "--";
    o << A.stop_lat << "--";
    o << A.stop_lon << "--";
    o << A.stop_code << "--";
    o << A.location_type << "--";
    o << A.parent_station << "--";
    o << A.wheelchair_boarding << "--";  
    o << A.stop_direction << "\n";
    return o;   
}

struct Stop_time
{
    std::string trip_id;	
    std::string stop_id;
    std::string arrival_time;
    std::string departure_time; 	
    int stop_sequence;
    std::string stop_headsign;
    std::string pickup_type;	
    std::string drop_off_type;
    std::string shape_dist_traveled;
};

std::ostream& operator<<( std::ostream& o, Stop_time const& A )
{
    
    o << A.trip_id << "--";
    o << A.stop_id << "--";
    o << A.arrival_time << "--";
    o << A.departure_time << "--";
    o << A.stop_sequence << "--";
    o << A.stop_headsign << "--";
    o << A.pickup_type << "--";
    o << A.drop_off_type << "--";  
    o << A.shape_dist_traveled << "\n";
    return o;   
}

struct Cal_date
{
    std::string service_id;
    std::string date;
    std::string exception_type;
};

std::ostream& operator<<( std::ostream& o, Cal_date const& A )
{
    
    o << A.service_id << "--";
    o << A.date << "--";
    o << A.exception_type << "\n";
    return o;   
}

struct Trip
{
    std::string route_id;
    std::string trip_id;
    std::string service_id; 	
    std::string trip_headsign;
    std::string direction_id;
    std::string block_id;
    std::string shape_id;
    std::string wheelchair_accessible;
    std::string bikes_allowed;
    std::string boarding_door;
};

std::ostream& operator<<( std::ostream& o, Trip const& A )
{
    
    o << A.route_id << "--";
    o << A.trip_id << "--";
    o << A.service_id << "--";
    o << A.trip_headsign << "--";
    o << A.direction_id << "--";
    o << A.block_id << "--";
    o << A.shape_id << "--";
    o << A.wheelchair_accessible << "--";  
    o << A.bikes_allowed << "--";  
    o << A.boarding_door << "\n";
    return o;   
}

struct Shape
{
    std::string shape_id;
    std::string shape_sequence_id;
    std::string shape_pt_lat;
    std::string shape_pt_lon;
    int shape_dist_traveled;
};

std::ostream& operator<<( std::ostream& o, Shape const& A)
{
    o << A.shape_id << "--";
    o << A.shape_sequence_id << "--";
    o << A.shape_pt_lat << "--";  
    o << A.shape_pt_lon << "--";  
    o << A.shape_dist_traveled << "\n";
    return o;
}

std::vector<Shape>const scan_shapes(std::ifstream& shapes_input)
{
    std::vector<Shape> shapes;
    std::string input{std::istreambuf_iterator<char>(shapes_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header

    while (std::getline(ss, line))
    {
        Shape temp;
        std::stringstream in(line);
        std::string qq;
        std::getline(in, temp.shape_id, ',');
        std::getline(in, temp.shape_sequence_id, ',');
        std::getline(in, temp.shape_pt_lat, ',');
        std::getline(in, temp.shape_pt_lon, ',');
        std::getline(in, qq, ',');
        temp.shape_dist_traveled = std::stoi(qq);
        shapes.push_back(temp);
    }
    return shapes;
}

std::vector<Route>const scan_routes(std::ifstream& routes_input)
{
    std::vector<Route> routes;
    std::string input{std::istreambuf_iterator<char>(routes_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header

    while (std::getline(ss, line))
    {
        Route temp;
        std::stringstream in(line);
        std::getline(in, temp.agency_id, ',');
        std::getline(in, temp.route_id, ',');
        std::getline(in, temp.route_short_name, ',');
        std::getline(in, temp.route_long_name, ',');
        std::getline(in, temp.route_type, ',');
        std::string tmp;
        if (in.peek() == '"')
        {
            in >> std::quoted(tmp);
            std::string discard;
            std::getline(in, discard, ',');
        }
        else 
        { 
                std::getline(in, tmp, ',');
        }
        temp.route_desc = tmp;
        std::getline(in, temp.route_color, ',');
        std::getline(in, temp.route_text_color, ',');
        routes.push_back(temp);
    }
    return routes;
}

std::vector<Stop>const scan_stops(std::ifstream& file_input)
{
    std::vector<Stop> stops;
    std::string input{std::istreambuf_iterator<char>(file_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header
    while(std::getline(ss, line))
    {
        Stop temp;
        std::stringstream in(line);
        std::string tmp;
        std::getline(in, temp.stop_id, ',');
        if (in.peek() == '"')
        {
            in >> std::quoted(tmp);
            std::string discard;
            std::getline(in, discard, ',');
        }
        else 
        { 
                std::getline(in, tmp, ',');
        }
        temp.stop_name = tmp;
        std::getline(in, temp.stop_lat, ',');
        std::getline(in, temp.stop_lon, ',');
        std::getline(in, temp.stop_code, ',');
        std::getline(in, temp.location_type, ',');
        std::getline(in, temp.parent_station, ',');
        std::getline(in, temp.wheelchair_boarding, ',');
        std::getline(in, temp.stop_direction, ',');
        stops.push_back(temp);
    }
    return stops;
}

std::vector<Stop_time>const scan_stop_times(std::ifstream& file_input)
{
    std::vector<Stop_time> stop_times;
    std::string input{std::istreambuf_iterator<char>(file_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header

    while(std::getline(ss, line)) //TODO: constructor
    {
        Stop_time temp;
        std::stringstream in(line);
        std::string tmp;
        std::string q;
        std::getline(in, temp.trip_id, ',');
        std::getline(in, temp.stop_id, ',');
        std::getline(in, temp.arrival_time, ',');
        std::getline(in, temp.departure_time, ',');
        std::getline(in, q, ',');
        temp.stop_sequence = std::stoi(q);
        if (in.peek() == '"')
        {
            in >> std::quoted(tmp);
            std::string discard;
            std::getline(in, discard, ',');
        }
        else 
        { 
                std::getline(in, tmp, ',');
        }
        temp.stop_headsign = tmp;
        std::getline(in, temp.pickup_type, ',');
        std::getline(in, temp.drop_off_type, ',');
        std::getline(in, temp.shape_dist_traveled, ',');
        stop_times.push_back(temp);
    }
    return stop_times;
}

std::vector<Cal_date>const scan_cal_dates(std::ifstream& file_input)
{
    std::vector<Cal_date> cal_dates;
    std::string input{std::istreambuf_iterator<char>(file_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header

    while(std::getline(ss, line)) //TODO: constructor
    {
        Cal_date temp;
        std::stringstream in(line);
        std::string tmp;
        std::getline(in, temp.service_id, ',');
        std::getline(in, temp.date, ',');
        std::getline(in, temp.exception_type, ',');
        cal_dates.push_back(temp);
    }
    return cal_dates;
}

std::vector<Trip>const scan_trips(std::ifstream& file_input)
{
    std::vector<Trip> trips;
    std::string input{std::istreambuf_iterator<char>(file_input),std::istreambuf_iterator<char>()};
    std::stringstream ss(input);
    
    std::string line;
    std::getline(ss, line); //* read & discard header

    while(std::getline(ss, line)) //TODO: constructor
    {
        Trip temp;
        std::stringstream in(line);
        std::string tmp;
        std::getline(in, temp.route_id, ',');
        std::getline(in, temp.trip_id, ',');
        std::getline(in, temp.service_id, ',');
        if (in.peek() == '"')
        {
            in >> std::quoted(tmp);
            std::string discard;
            std::getline(in, discard, ',');
        }
        else 
        { 
                std::getline(in, tmp, ',');
        }
        temp.trip_headsign = tmp;
        std::getline(in, temp.direction_id, ',');
        std::getline(in, temp.block_id, ',');
        std::getline(in, temp.shape_id, ',');
        std::getline(in, temp.wheelchair_accessible, ',');
        std::getline(in, temp.bikes_allowed, ',');
        std::getline(in, temp.boarding_door, ',');
        trips.push_back(temp);
    }
    return trips;
}




template<class InputIt1, class InputIt2,
         class OutputIt, class Compare>
OutputIt mod_set_intersection(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2,
                          OutputIt d_first, Compare comp)
{
    while (first1 != last1 && first2 != last2) 
    {
        if (comp(*first1, *first2)) 
        {
            ++first1;
        } 
        else 
        {
            if (!comp(*first2, *first1)) 
            {
                *d_first++ = *first1++;
            }
            else
            {
                ++first2;
            }
        }
    }
    return d_first;
}

int how_many(std::vector<Route> &routes,std::vector<Trip> &trips,std::vector<Stop_time> &stop_times, int i)
{
    std::vector<Route> vec1;
    std::vector<Trip> vec2;
    std::vector<Stop_time> vec3;
    std::string i_str = std::to_string(i);
    for (Route r: routes)
    {
        if(r.route_type == i_str)
        {
            vec1.push_back(r);
        }
    }
    std::sort(vec1.begin(), vec1.end(), cmpr);
    std::sort(trips.begin(), trips.end(), cmpr);
    mod_set_intersection(trips.begin(), trips.end(), vec1.begin(), vec1.end(), std::back_inserter(vec2), cmpr);
    
    std::sort(stop_times.begin(), stop_times.end(),cmpt);
    std::sort(vec2.begin(), vec2.end(),cmpt);
    mod_set_intersection ( stop_times.begin(), stop_times.end(), vec2.begin(), vec2.end(), std::back_inserter(vec3),cmpt);
    std::sort(vec3.begin(),vec3.end(),[](auto &lhs, auto &rhs){ return lhs.stop_id < rhs.stop_id;});
    auto last = std::unique(vec3.begin(), vec3.end(),[](auto &lhs, auto &rhs){ return lhs.stop_id == rhs.stop_id;});
    vec3.erase(last,vec3.end());
    return static_cast<int>(vec3.size());
}

std::string longest_route_distance(std::vector<Route> &routes,std::vector<Trip> &trips,std::vector<Shape> &shapes, int i)
{
    std::vector<Route> vec1; //Every route for the specified route_type
    std::vector<Trip> vec2; //One instance of every vec1 routes
    std::vector<Shape> vec3; //Every shape of the 
    std::string longest_route_id;
    std::string longest_route_name;
    std::string i_str = std::to_string(i);
    for (Route r: routes)
    {
        if(r.route_type == i_str)
        {
            vec1.push_back(r);
        }
    }
    std::sort(vec1.begin(), vec1.end(), cmpr);
    std::sort(trips.begin(), trips.end(), cmpr);
    mod_set_intersection(trips.begin(), trips.end(), vec1.begin(), vec1.end(), std::back_inserter(vec2), cmpr);
    
    std::sort(vec2.begin(), vec2.end(), [](auto &lhs, auto &rhs){ return lhs.shape_id < rhs.shape_id;});
    auto last = std::unique(vec2.begin(),vec2.end(), [](auto &lhs, auto &rhs){ return lhs.shape_id == rhs.shape_id;});
    vec2.erase(last,vec2.end());

    std::sort(shapes.begin(), shapes.end(), [](auto &lhs, auto &rhs){ return lhs.shape_id < rhs.shape_id;});
    std::sort(vec2.begin(), vec2.end(), [](auto &lhs, auto &rhs){ return lhs.shape_id < rhs.shape_id;});
    mod_set_intersection(shapes.begin(), shapes.end(), vec2.begin(), vec2.end(), std::back_inserter(vec3), [](auto &lhs, auto &rhs){ return lhs.shape_id < rhs.shape_id;});
    std::sort(vec3.begin(),vec3.end(), [](auto &lhs, auto &rhs){ return lhs.shape_dist_traveled > rhs.shape_dist_traveled;});
    for (auto e: trips)
    {
        if (e.shape_id == vec3[0].shape_id){ longest_route_id = e.route_id;}
    }

    for (auto e: routes)
    {
        if(e.route_id == longest_route_id){longest_route_name = e.route_short_name;}
    }
    return longest_route_name;
}

std::string most_stops(std::vector<Route> &routes,std::vector<Trip> &trips,std::vector<Stop_time> &stop_times, int i)
{
    std::vector<Route> vec1;
    std::vector<Trip> vec2;
    std::vector<Stop_time> vec3;
    std::string i_str = std::to_string(i);
    std::string longest_route_id;
    std::string longest_route_name;
    for (Route r: routes)
    {
        if(r.route_type == i_str)
        {
            vec1.push_back(r);
        }
    }
    std::sort(vec1.begin(), vec1.end(), cmpr);
    std::sort(trips.begin(), trips.end(), cmpr);
    mod_set_intersection(trips.begin(), trips.end(), vec1.begin(), vec1.end(), std::back_inserter(vec2), cmpr);
    
    std::sort(stop_times.begin(), stop_times.end(),cmpt);
    std::sort(vec2.begin(), vec2.end(),cmpt);
    mod_set_intersection ( stop_times.begin(), stop_times.end(), vec2.begin(), vec2.end(), std::back_inserter(vec3),cmpt);
    std::sort(vec3.begin(),vec3.end(), [](auto &lhs, auto &rhs){ return lhs.stop_sequence > rhs.stop_sequence; });
    for (auto e: trips)
    {
        if (e.trip_id == vec3[0].trip_id){ longest_route_id = e.route_id;}
    }

    for (auto e: routes)
    {
        if(e.route_id == longest_route_id){longest_route_name = e.route_short_name;}
    }
    return longest_route_name;
}