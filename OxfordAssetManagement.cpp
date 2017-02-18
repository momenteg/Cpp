/*
    author: Giulio Momente'
    email: momenteg@gmail.com
    date: Jan 2017
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

bool process_command_line(int argc, char **argv, std::string &file_name){
    try{
        po::options_description desc("Program Usage", 1024, 512);
        desc.add_options()
        ("help,h",       "produce help message")
        ("file_name,f",   po::value<std::string>(&file_name)->required(),     " enter the file to read");
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")){
            std::cout << desc << "\n";
            return false;
        }
        po::notify(vm);
        return true;
    }
    catch(std::exception& e){
        std::cerr << "Error: " << e.what() << "\n";
        return false;
    }
    catch(...){
        std::cerr << "Unknown error!" << "\n";
        return false;
    }
}

class Orderbook {
    struct data {
        int timestamp_begin;
        double price;
    };
    std::map < long int , data > orderbook_map;
public:
    void insert (int, long int, double);
    void erase (int, long int);
    double get_highest_price();
};

void Orderbook::insert (int timestamp_, long int id_, double price_) {
    orderbook_map[id_].timestamp_begin = timestamp_;
    orderbook_map[id_].price = price_;
}

void Orderbook::erase (int timestamp_, long int id_) {
    orderbook_map.erase(id_);
}

double Orderbook::get_highest_price () {
    if(orderbook_map.empty()){
        return std::numeric_limits<double>::quiet_NaN();
    }
    std::map < long int , data >::iterator max = std::max_element(orderbook_map.begin(), orderbook_map.end(), orderbook_map.value_comp()); //hopefully faster than a for loop
    return max->second.price;
}

void read_file_and_compute_average(std::string filename, Orderbook &orderbook, double &sum, double &sum_weight){
    std::ifstream file(filename.c_str());
    std::string line;
    double previous_timestamp=0, previous_price=0;
    bool skip=false;
    while (std::getline(file, line)) {
        int timestamp;
        std::string operation;
        long int id;
        double price;
        std::istringstream ss(line);
        ss >> timestamp >> operation >> id;
        if (operation.compare("I")==0) {
            ss >> price;
            orderbook.insert(timestamp, id, price);
            price < previous_price ? skip = true : skip= false;
        }
        if (operation.compare("E")==0) {
            orderbook.erase(timestamp, id);
        }

        if(isnan(previous_price)== true || previous_price == 0){
            previous_timestamp = timestamp;
            previous_price = orderbook.get_highest_price();
            continue;
        }
        sum_weight += (timestamp - previous_timestamp);
        sum += (timestamp - previous_timestamp)*previous_price;

        previous_timestamp = timestamp ;
        skip == true ? previous_price= previous_price : previous_price = orderbook.get_highest_price();
        skip=false;
    }
}

int main(int argc, char ** argv) {
    std::string file_name;
    double sum=0, sum_weight=0;
    bool result = process_command_line(argc, argv, file_name);
    if (!result){
        return 1;
    }

    Orderbook orderbook;
    read_file_and_compute_average(file_name, orderbook, sum, sum_weight);
    std::cout << "######################################################################" << std::endl;
    std::cout << "The time‐weighted average of the highest price is :  "<< sum/sum_weight << std::endl;
    std::cout << "######################################################################" << std::endl;

    return 0;
}
