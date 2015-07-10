#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>

#include <boost/program_options.hpp>

namespace chameleon_tongue {

class Config: public SubCommand {
private:
	boost::program_options::variables_map vm;
	boost::program_options::options_description desc;
public:
	void run(Environment &env, const Options::SubCommandArgs &args) override {
		using namespace	boost::program_options;
		desc.add_options()
			("help",  "show this help message")
			("get", value<std::string>(), "get the value");
		
		store(parse_command_line(args.argc, args.argv, desc), vm);
		notify(vm);
		
		if (vm.count("get") >= 1) {
			std::string name = vm["get"].as<std::string>();
			std::cout << env.get_config_val(name) << std::endl;
		}
			
		
	}
};

}