#include <ginac/ginac.h>
#include <iostream>
#include <numeric>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp> 
using namespace std;
using namespace GiNaC;
namespace po = boost::program_options;
#include "die.h"

struct Runner {
    int white, yellow, red, black, reroll, target;
    Runner(const po::variables_map& command_line_variables) {
        white=command_line_variables["white"].as<int>();
        yellow=command_line_variables["yellow"].as<int>();
        red=command_line_variables["red"].as<int>();
        black=command_line_variables["black"].as<int>();
        reroll=command_line_variables["reroll"].as<int>();
        target=command_line_variables["target"].as<int>();
    }
    virtual void run() const=0;
    static unique_ptr<Runner> create(const po::variables_map& command_line_variables);
};

struct PrintSuccessChance : Runner {
    using Runner::Runner;
    void run() const override {
        auto roll= Roll{}.white(white).yellow(yellow).red(red).black(black).reroll_blanks(reroll);
        cout<<roll.result().chance_of_at_least(target)<<endl;
        cout<<roll.result().chance_of_at_least(target).evalf()<<endl;    
    }
};

struct Advise : Runner {
    using Runner::Runner;
    void run() const override {
    }
};

unique_ptr<Runner> Runner::create(const po::variables_map& command_line_variables) {
    auto type=command_line_variables["mode"].as<string>();
    if (type=="success-chance") return make_unique<PrintSuccessChance>(command_line_variables);
    else if (type=="advise") return make_unique<Advise>(command_line_variables);
    else throw std::invalid_argument("invalid mode: "+type);
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
            ("mode",po::value<string>()->default_value("success-chance"),"success-chance|advise")
            ;
		try {
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (vm.count("help")) print_help(argv[0],desc);            
            else Runner::create(vm)->run();
            return 0;
        }
        catch (const boost::program_options::unknown_option& e) {
        		print_help(argv[0],desc);
        		return 1;
        }
}
