#include <ginac/ginac.h>
#include <iostream>
#include <numeric>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp> 
using namespace std;
using namespace GiNaC;
namespace po = boost::program_options;
#include "die.h"

void process(const po::variables_map& command_line_variables) {
    int white=command_line_variables["white"].as<int>();
    int yellow=command_line_variables["yellow"].as<int>();
    int red=command_line_variables["red"].as<int>();
    int black=command_line_variables["black"].as<int>();
    int reroll=command_line_variables["reroll"].as<int>();
    int target=command_line_variables["target"].as<int>();
    auto roll= Roll{}.white(white).yellow(yellow).red(red).black(black).reroll_blanks(reroll);
    cout<<roll.result().chance_of_at_least(target)<<endl;
    cout<<roll.result().chance_of_at_least(target).evalf()<<endl;    
}

void print_help(string program_name, const po::options_description& desc) {
	cout << "Usage: "<< program_name<< " [options]\n";
	cout << desc;
}


int main(int argc, char* argv[]) {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("white",po::value<int>()->default_value(0),"white dice")
            ("yellow",po::value<int>()->default_value(0),"yellow dice")
            ("red",po::value<int>()->default_value(0),"red dice")
            ("black",po::value<int>()->default_value(0),"black dice")
            ("reroll",po::value<int>()->default_value(0),"reroll")
            ("target",po::value<int>(),"target value")
            ;
		try {
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (vm.count("help")) print_help(argv[0],desc);            
            else process(vm);
            return 0;
        }
        catch (const boost::program_options::unknown_option& e) {
        		print_help(argv[0],desc);
        		return 1;
        }
}
