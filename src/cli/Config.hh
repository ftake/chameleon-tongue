#include "SubCommand.hh"
#include "Environment.hh"
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

namespace chameleon_tongue {

class Config: public SubCommand {
public:
    Config() {
        using namespace boost::program_options;

        options.add_options()
            ("help,h",  "show this help message")
            ("get", "get the value of the specified config")
            ("set", "set the value of the specified config")
            ("list,l", "list all config variables")
            ("system", "set system wide config (used with --set)");
        hidden_options.add_options()
            ("key", value<std::string>(), "key")
            ("value", value<std::string>(), "value");
                 
        positional_options.add("key", 1);
        positional_options.add("value", 1);
    }

    void run(Environment &env, const Options::SubCommandArgs &args) override {
        using namespace boost::program_options;
        boost::program_options::variables_map vm;
        
        parse_and_store_args(vm, args);

        bool has_get = vm.count("get") >= 1;
        bool has_set = vm.count("set") >= 1;
        auto has_system = vm.count("system") >= 1;
        
        if (vm.count("help") >= 1) {
            print_help(std::cout);
            return;
        }
        
        if (vm.count("list") >= 1) {
            env.list_config();
            return;
        }
        
        // --set or --get
        if ((has_get && has_set) || (!has_get && !has_set)) {
            throw std::logic_error("only either of --get or --set can be specified");
        }

        if (vm.count("key") == 0) {
            throw std::logic_error("key is not specified");
        }
        
        auto key = vm["key"].as<std::string>();

        if (has_get) {
            std::cout << env.get_config_val(key) << std::endl;
        } else if (has_set) {
            if (vm.count("value") == 0) {
                throw std::logic_error("value is not specified");
            }
            auto value = vm["value"].as<std::string>();
            env.set_config_val(key, value, has_system);
        }
    }

    virtual std::string get_description() const override {
        return "set or get value of configuration specified by 'key'";
    }

    virtual void print_usage(std::ostream &out) const override {
        out << "Usage:" << std::endl;
        out << "  im-settings config --set key value" << std::endl;
        out << "  im-settings config --get key" << std::endl;
    }
};

}