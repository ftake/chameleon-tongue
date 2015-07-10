#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>

namespace chameleon_tongue {

class Options {
private:
	boost::program_options::variables_map global_vm;
	boost::program_options::options_description global_desc;
	std::string subcommand; //TODO

	unsigned int find_subcommand(int argc, char** argv);
	
public:
	struct SubCommandArgs {
		int argc;
		char** argv;
	} subcommand_args;
	
	Options(int argc, char* argv[]);
	
	const std::string& get_subcommand();
	void print_help();
	const Options::SubCommandArgs &get_subcommand_args();
};

}

#endif