#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>

namespace chameleon_tongue {

class Select: public SubCommand {
private:
    boost::program_options::variables_map vm;
    boost::program_options::options_description desc;
public:
    void run(Environment &env, const Options::SubCommandArgs &args) override {
        using namespace    boost::program_options;
        boost::program_options::options_description options("Options");
        boost::program_options::options_description hidden_options("Hidden options");
        
        options.add_options()
            ("help",  "show this help message")
            ("system", "select system-wide input method");
        hidden_options.add_options()
            ("input-method", value<std::string>(), "input method");

        desc.add(options).add(hidden_options);
        
        positional_options_description pd;
        pd.add("input-method", 1);

        store(command_line_parser(args.argc, args.argv).options(desc).positional(pd).run(), vm);
        notify(vm);

        if (vm.count("help") >= 1) {
            std::cout << options;
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
};

}