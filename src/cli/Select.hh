#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>

namespace chameleon_tongue {

class Select: public SubCommand {
public:
    void run(Environment &env, const Options::SubCommandArgs &args) override {
        if (args.argc != 2) {
            throw std::logic_error("\"select\" requres 1 argument");
        }
        
        std::vector<InputMethod*> ims = env.get_input_methods();
        for (InputMethod *im: ims) {
            if (im->name == args.argv[1]) {
                env.select_input_method(im);
                return;
            }
        }
        
        throw std::logic_error(std::string(args.argv[1]) + " is not available");
    }
};

}