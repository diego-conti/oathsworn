#include <ginac/ginac.h>
#include <iostream>
#include <numeric>
#include <boost/program_options.hpp>
#include <boost/exception/diagnostic_information.hpp> 
using namespace std;
using namespace GiNaC;
namespace po = boost::program_options;
#include "csvline.h"
#include "series.h"
#include "die.h"
#include "roll.h"
#include "sequence.h"
#include "bestsequence.h"
#include <optional>
#include <fstream>

struct Runner {
    int white, yellow, red, black, reroll, target, empower;
    Runner(const po::variables_map& command_line_variables) {
        white=command_line_variables["white"].as<int>();
        yellow=command_line_variables["yellow"].as<int>();
        red=command_line_variables["red"].as<int>();
        black=command_line_variables["black"].as<int>();
        reroll=command_line_variables["reroll"].as<int>();
        target=command_line_variables.count("target")? command_line_variables["target"].as<int>() : 0;
        empower=command_line_variables["empower"].as<int>();
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
        auto available_dice=AvailableDice{}.black(black).red(red).yellow(yellow).empower(empower);
        auto best=best_sequence(available_dice,target,reroll);
        cout<<best.seq<<"\t"<<(best.result)<<"\t"<<(best.result).evalf()<<endl;           
    }
};


struct PrintSuccessChanceCsv : Runner {
    using Runner::Runner;
    void print_csv(int black, int red, int yellow, int white, int reroll, int target) const {
        auto roll= Roll{}.white(white).yellow(yellow).red(red).black(black).reroll_blanks(reroll);
        auto chance=roll.result().chance_of_at_least(target);
        roll.print_csvline(cout,target,chance,chance.evalf());
    }
    void run() const override {
        for (int b=0;b<=black;++b)
        for (int r=0;r<=red;++r)
        for (int y=0;y<=yellow;++y)             
        for (int w=0;w<=white;++w)            
        for (int reroll=0;reroll<=this->reroll;++reroll)
        for (int target=this->target;target>=1;--target)
            print_csv(b,r,y,w,reroll,target); 
    }
};



struct AdviseCsv : Runner {
    optional<string> success_csv_file;
    AdviseCsv(const po::variables_map& command_line_variables) : Runner{command_line_variables} {
        if (command_line_variables.count("success")) success_csv_file=command_line_variables["success"].as<string>();
    }
    void print_csv(int black, int red, int yellow) const {
        auto available_dice=AvailableDice{}.black(black).red(red).yellow(yellow);
        for (int reroll=0;reroll<=this->reroll;++reroll)
        for (int empower=0;empower<=this->empower;++empower)
        for (int target=this->target;target>=1;--target) {    //use reverse order so highest order truncations of the series are computed first
            auto best=best_sequence(available_dice.empower(empower),target,reroll);
            print_csvline(cout,black,red,yellow,reroll,empower,target,best.seq);
        }
    }
    void run() const override {
        for (int b=0;b<=black;++b)
        for (int r=0;r<=red;++r)
        for (int y=0;y<=yellow;++y)           
            print_csv(b,r,y);        
        if (success_csv_file) {
            ofstream out{success_csv_file.value()};
            Roll::print_memory(out);
            cout<<"Success csv printed to "<<success_csv_file.value()<<endl;
        }        
    }
};

unique_ptr<Runner> Runner::create(const po::variables_map& command_line_variables) {
    auto type=command_line_variables["mode"].as<string>();
    if (type=="success-chance") return make_unique<PrintSuccessChance>(command_line_variables);
    else if (type=="advise") return make_unique<Advise>(command_line_variables);
    else if (type=="advise-csv") return make_unique<AdviseCsv>(command_line_variables);    
    else if (type=="success-chance-csv") return make_unique<PrintSuccessChanceCsv>(command_line_variables);    
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
            ("empower",po::value<int>()->default_value(0),"empower")
            ("success", po::value<string>(),"file for output of success chances, for use in advise-csv mode")
            ("mode",po::value<string>()->default_value("success-chance"),"success-chance|advise|advise-csv|success-chance-csv")
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
