#include "SubCommand.hh"
#include "AutoSelect.hh"
#include "Environment.hh"
#include "List.hh"
#include "Help.hh"
#include "Config.hh"
#include "Version.hh"
#include "Options.hh"
#include "Select.hh"
#include <iostream>
#include <vector>
#include <map>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>

using namespace chameleon_tongue;

int main(int argc, char* argv[]) {
    try {
        boost::log::add_console_log(std::clog);
        Options opts(argc, argv);
        
        if (opts.get_log_level() == 0) {
            boost::log::core::get()->set_filter(
                boost::log::trivial::severity >= boost::log::trivial::warning
            );
        }
        
        const std::string &subcommand_name = opts.get_subcommand();
        Environment env;
        SubCommandRegistory registory;
        registory.add("autoselect", new AutoSelect());
        registory.add("help", new Help(registory));
        registory.add("list", new List());
        registory.add("config", new Config());
        registory.add("select", new Select());
        registory.add("version", new Version());
        SubCommand* subcommand = registory.find_subcommand(subcommand_name);
        subcommand->run(env, opts.get_subcommand_args());
        
    } catch (std::exception &e) {
        std::cerr << "Error: ";
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
