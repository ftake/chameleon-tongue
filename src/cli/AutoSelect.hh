#include "SubCommand.hh"

namespace chameleon_tongue {

class AutoSelect : public SubCommand {
public:
    void run(Environment &env, const Options::SubCommandArgs &args) override;
    AutoSelect() {}

    virtual std::string get_description() const override;
};

}