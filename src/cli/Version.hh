#include "SubCommand.hh"
#include "SubCommandRegistory.hh"
#include <iostream>
#include "IMSettingsConfig.h"

namespace chameleon_tongue {

class Version: public SubCommand {
public:
    virtual void run(Environment &env, const Options::SubCommandArgs &args) override {
        std::cout << "im-settings version ";
        std::cout << IMSettings_VERSION_MAJOR;
        std::cout << ".";
        std::cout << IMSettings_VERSION_MINOR;
        std::cout << std::endl;
    }

    virtual std::string get_description() const override {
        return "show the version of this program";
    }
};
}