#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>

namespace chameleon_tongue {

class Select: public SubCommand {
public:
    Select() {
        using namespace boost::program_options;

        options.add_options()
            ("help,h",  "show this help message")
            ("system", "select system-wide input method");
        positional_options.add("input-method", 1);
        hidden_options.add_options()
            ("input-method", value<std::string>(), "input method");
    }

    void run(Environment &env, const Options::SubCommandArgs &args) override {
        using namespace boost::program_options;

        variables_map vm;      
        parse_and_store_args(vm, args);

        if (vm.count("help") >= 1) {
            print_help(std::cout);
            return;
        }

        if (vm.count("input-method") == 0) {
            throw std::logic_error("no input method is specified.");
        }

        bool has_system = vm.count("system") >= 1;    
        const std::string &selected = vm["input-method"].as<std::string>();
        
        std::vector<InputMethod*> ims = env.get_input_methods();
        for (InputMethod *im: ims) {
            if (im->name == selected) {
                env.select_input_method(im, has_system);
                return;
            }
        }
        
        throw std::logic_error(std::string(args.argv[1]) + " is not available");
    }

    virtual std::string get_description() const override {
        return "select an input method to use";
    }

    virtual void print_usage(std::ostream &out) const override {
        out << "Usage:" << std::endl;
        out << "  im-settings select 'input method ID'" << std::endl;
    }
};

}