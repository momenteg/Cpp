#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <exception>
#include <vector>
#include <stdlib.h>
#include <boost/program_options.hpp>

/*

 This is a snap of a code, developed to provide the LIGO collaboration with
 data (time, significance), detected by IceCube.

 This is a snap of refactoring, done by me on a code wrote by a former Master student.

*/

/*
compile the code (on ubuntu) like:
g++ snap_of_master_student_code.cpp -o output -lboost_program_options
*/

using namespace std;
namespace po = boost::program_options;

typedef pair <int, double> year_struct;

const double seconds_in_a_day = 86400;
double bin_differ = 0.5;
double bins = 800; //bins of the hole plot
double up_limit = 8; //maximum significance on the plot
double down_limit = -8; //minimum significance on the plot
double limit = 200; // Limit for fake probability
//int output_precision = 8;

void fill_year_vector(std::vector<year_struct> & v){
    int n[] = { 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015,
                2016, 2017, 2018, 2019, 2020, 2021, 2022};
    double s[] = {915148800, 946684800, 978307200, 1009843200, 1041379200,1072915200, 1104537600, 1136073600, 1167609600, 1199145600, 1230768000, 1262304000, 1293840000, 1325376000, 1356998400, 1388534400, 1420070400,
                  1451606400, 1483228800, 1514764800, 1546300800, 1577836800, 1609459200, 1640995200 };
    int l = sizeof(n)/sizeof(n[0]);
    for(int i=0; i<l; i++) {
        v.push_back(make_pair(n[i], s[i]));
    }
}

double assign_value_to_unix_zeit(int year, std::vector<year_struct> & v){
    for(vector < year_struct >::const_iterator it = v.begin(); it != v.end(); it++) {
        if(it->first == year) {
            return it->second;
        }
    }
}

bool process_command_line(int argc, char **argv, std::string &file_name, int &year){
    try{
        po::options_description desc("Program Usage", 1024, 512);
        desc.add_options()
          ("help,h",       "produce help message")
          ("file_name,f",   po::value<std::string>(&file_name)->required(),     " enter the root file  (include path) ")
          ("year,y",        po::value<int>(&year)->required(),                  " year ");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")){
            std::cout << desc << "\n";
            return false;
        }
        po::notify(vm);
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

int main(int argc, char ** argv) {
    std::string file_name;
    int year;
    double old_significance, corrected_significance, signal_significance, time_, time_next_chain, uptime, unix_time;
    double bin_size, round_, bin_up, bin_down, content_up, without_round, bin_correct;

    bool result = process_command_line(argc, argv, file_name, year);
    if (!result){
        return 1;
    }

    const char * file_name_char = file_name.c_str();

    std::vector<year_struct> year_unix_time_pair;
    fill_year_vector(year_unix_time_pair);
    unix_time = assign_value_to_unix_zeit(year, year_unix_time_pair);

    return 0;
}
