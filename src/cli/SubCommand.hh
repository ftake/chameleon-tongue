#ifndef SUB_COMMAND_HH
#define SUB_COMMAND_HH

#include <string>
#include "Options.hh"

namespace chameleon_tongue {
    
class Environment;
    
class SubCommand {
protected:
    boost::program_options::options_description options;
    boost::program_options::options_description hidden_options;
    boost::program_options::positional_options_description positional_options;

    void parse_and_store_args(boost::program_options::variables_map &vm, const Options::SubCommandArgs &args) {
        using namespace boost::program_options;

        options_description all_options;
        all_options.add(options).add(hidden_options);
        store(command_line_parser(args.argc, args.argv)
            .options(all_options)
            .positional(positional_options).run(), vm);
        notify(vm);
    }

public:
    SubCommand(): options("Options"), hidden_options("Hidden Options") {};

    virtual void run(Environment &env, const Options::SubCommandArgs &args) = 0;
    virtual void print_help(std::ostream &out) const {
        out << get_description() << std::endl;
        print_usage(out);
        if (this->options.options().size() > 0) {
           out << std::endl;
           out << this->options;
        }
        return;
    }

    virtual std::string get_description() const = 0;
    virtual void print_usage(std::ostream &out) const { /* do nothing */ };
    virtual ~SubCommand() {};
};

}

#endif