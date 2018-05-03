#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>
#include <boost/program_options.hpp>

namespace chameleon_tongue {

class List: public SubCommand {
public:
    List() {
        options.add_options()
            ("help,h",  "show this help message");
    }

    void run(Environment &env, const Options::SubCommandArgs &args) override {
        using namespace boost::program_options;

        variables_map vm;
        parse_and_store_args(vm, args);
        if (vm.count("help") >= 1) {
            print_help(std::cout);
            return;
        }

        for (InputMethod* im: env.get_input_methods()) {
            std::cout << im->name << ":" << im->path << std::endl;
        }
    }

    virtual std::string get_description() const override {
        return "list all the input methods installed";
    }
};

}