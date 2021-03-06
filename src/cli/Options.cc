#include "Options.hh"
#include <iostream>

namespace fs = boost::filesystem;
namespace po = boost::program_options;


namespace chameleon_tongue {


unsigned int Options::find_subcommand(int argc, char** argv) {
    int i;
    for (i = 1; i < argc; i++) {
        if (strlen(argv[i]) > 1 && argv[i][0] != '-') {
            return i;
        }
    }
    return i; // not found
}
    

Options::Options(int argc, char* argv[]): global_desc("Global options") {
    // split into global options, sub command, sub command options
    
    int subcommand_index = find_subcommand(argc, argv);
    if (subcommand_index == argc) {
        subcommand = "help";
    } else {
        subcommand = argv[subcommand_index];
    }
    
    global_desc.add_options()
        ("help,h", "show this help message")
        ("version", "print version")
        ("verbose,v", "verbose messages");
    po::store(po::parse_command_line(subcommand_index, argv, global_desc), global_vm);
    po::notify(global_vm);
    
    subcommand_args.argc = argc - subcommand_index;
    subcommand_args.argv = argv + subcommand_index;
    
    if (global_vm.count("help") > 0) {
        subcommand = "help";
    }
    
    if (global_vm.count("version") > 0) {
        subcommand = "version";
    }
    
    if (global_vm.count("verbose") > 0) {
        log_level = 1;
    } else {
        log_level = 0;
    }
}
    
const std::string& Options::get_subcommand() {
    return subcommand;
}

void Options::print_help(std::ostream &out) const {
    out << global_desc << std::endl;
}

const Options::SubCommandArgs &Options::get_subcommand_args() {
    return subcommand_args;
}


}