//
// Created by weiguow on 18-12-11.
//

#include <string>
#include <vector>

#include <stout/flags.hpp>

using std::string;
using std::vector;

class TestSubcommand : public Subcommand {
public:
    explicit TestSubcommand(const string &name) : Subcommand(name) {}

    TestFlagsBase flags;
protected:
    virtual int excute() { return 0; }

    virtual flags::FlagsBase *getFlags() { return &flags }
};

static vector<string> getArgv(const flags::FlagsBase &flags) {
    vector<string> argv;
    foreachpair (const string &name, const flags::Flag &flag, flags) {
                            Option<string> value = flag.stringify(flags);
                            if (value.isSome()) {
                                argv.push_back("--" + name + "=" + value.get());
                            }
                        }
    return argv;
}




