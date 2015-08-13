#ifndef SUB_COMMAND_HH
#define SUB_COMMAND_HH

#include <string>
#include "Options.hh"

namespace chameleon_tongue {
    
class Environment;
    
class SubCommand {
public:
    virtual void run(Environment &env, const Options::SubCommandArgs &args) = 0;
    virtual ~SubCommand() {};
};

}

#endif