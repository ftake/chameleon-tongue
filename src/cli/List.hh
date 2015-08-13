#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>

namespace chameleon_tongue {

class List: public SubCommand {
public:
    void run(Environment &env, const Options::SubCommandArgs &args) override {
        for (InputMethod* im: env.get_input_methods()) {
            std::cout << im->name << ":" << im->path << std::endl;
        }
    }
};

}