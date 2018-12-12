//
// Created by weiguow on 18-12-11.
//

#ifndef LIBPROCESS_START_FLAGS_TESTS_MINE_H
#define LIBPROCESS_START_FLAGS_TESTS_MINE_H

#include <stout/flags/flags.hpp>
#include <stout/os.hpp>
#include <stout/utils.hpp>

#include <error.h>

using flags::Flag;
using flags::FlagsBase;
using flags::Warnings;
using flags::Warning;

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::cin;

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
#endif //LIBPROCESS_START_FLAGS_TESTS_MINE_H
