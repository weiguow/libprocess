//
// Created by weiguow on 18-11-6.
//

#ifndef LIBPROCESS_START_FLAGS_H
#define LIBPROCESS_START_FLAGS_H

#include <map>
#include <string>

#include <gmock/gmock.h>

#include <stout/duration.hpp>
#include <stout/flags.hpp>
#include <stout/foreach.hpp>
#include <stout/gtest.hpp>
#include <stout/json.hpp>
#include <stout/none.hpp>
#include <stout/nothing.hpp>
#include <stout/option.hpp>
#include <stout/os.hpp>
#include <stout/path.hpp>
#include <stout/some.hpp>
#include <stout/utils.hpp>
#include <stout/os/write.hpp>
#include <stout/tests/utils.hpp>

#include <process/process.hpp>

using flags::Flag;
using flags::FlagsBase;
using flags::Warnings;

using std::cout;
using std::endl;
using std::string;
using std::map;

using utils::arraySize;

class TestFlagsBase : public virtual FlagsBase {
public:
    TestFlagsBase() {
        add(&TestFlagsBase::name,
            "name",
            "Set name",
            "weiguow");

        add(&TestFlagsBase::age,
            "age",
            "Set age",
            23);

        add(&TestFlagsBase::id,
            "id",
            "Set id",
            1);

    }
    string name;
    int age;
    int id;
};

#endif //LIBPROCESS_START_FLAGS_H
