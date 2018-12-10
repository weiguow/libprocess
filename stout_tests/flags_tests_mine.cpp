//
// Created by weiguow on 18-12-10.
//
#include <stout/flags/flags.hpp>
#include <stout/os.hpp>
#include <stout/utils.hpp>

using flags::Flag;
using flags::FlagsBase;
using flags::Warnings;

using std::string;
using std::cout;
using std::endl;
using std::map;

using utils::arraySize;


class TestFlagsBase : public virtual FlagsBase {
public:
    string name1;
    int name2;
    bool name3;

    TestFlagsBase() {
        add(&TestFlagsBase::name1,
            "name1",
            "Set name1",
            "ben folds");

        add(&TestFlagsBase::name2,
            "name2",
            "Set name2",
            42);

        add(&TestFlagsBase::name3,
            "name3",
            "Set name3",
            false);
    }
};

class TestFlags : public virtual FlagsBase {
public:
    TestFlags() {
        add(&TestFlags::name1,
                "name1",
                Some("alias1"),
                "Also set name1");

        add(&TestFlags::name2,
            "name2",
            Some("alias2"),
            "Also set name2",
            true);

        add(
                &TestFlags::name3,
                "name3",
                Some("alias3"),
                "Also set name3",
                "value8");
    }

    Option<string> name1;
    bool name2;
    string name3;
};

int main() {
    TestFlagsBase flags;

    TestFlags flags2;

    /**
     * KEY AND VALUE
     * */
//    const map<string, Option<string>> values = {
//            {"name1", Some("billy joe1")},
//            {"name2", Some("43")},
//            {"name3", Some("false")}
//    };
//
//    flags.load(values);
//
//    cout << flags.name1 << endl;
//    cout << flags.name2 << endl;
//    cout << flags.name3 << endl;
//
//
//    cout << endl;


/**
 * ENVIORMENT
 * */
//    cout << "ENVIORMENT TEST" << endl;
//    os::setenv("FLAGSTEST_name1", "billy joel_2");
//    os::setenv("FLAGSTEST_name2", "432");
//    os::setenv("FLAGSTEST_no-name3", "");
//
//    Try<Warnings> load = flags.load("FLAGSTEST_");
//
//    cout << flags.name1 << endl;
//    cout << flags.name2 << endl;
//    cout << flags.name3 << endl;

/**
 * PATH ENVIORMENT
 * */
    const char* argv[] = {
            "/path/to/program",
            "--name1=billy joel",
            "--name2=43",
            "--no-name3"
    };

    Try<Warnings> load = flags.load("FLAGSTEST_", arraySize(argv), argv);

    cout << flags.name1 << endl;
    cout << flags.name2 << endl;
    cout << flags.name3 << endl;
}