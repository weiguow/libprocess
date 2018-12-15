//
// Created by weiguow on 18-12-10.
//
#include <stout/flags/flags.hpp>
#include <stout/os.hpp>
#include <stout/utils.hpp>

#include <unistd.h>

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

extern char *optarg;  //保存选项参数
extern int optind;    //记录下一个检索位置
extern int opterr;    //是否将错误信息输出到stderr
extern int optopt;    //不在选项字符串optstring中的选项 for example nmp:help
extern int getopt(int argc, char * const argv[], const char *optstring)__THROW;

class TestFlagsBase : public virtual FlagsBase {
public:
    string n;
    int m;
    bool p;

    TestFlagsBase() {
        add(&TestFlagsBase::n,
            "name1",
            "Set name1",
            "ben folds");

        /*
         * Add  : 第一个参数m是简写
         *        第二个name2是全称  flags.load进来的参数是
         *        第三个是对这个命令的解释
         *        第四个是默认值
         * */
        add(&TestFlagsBase::m,
            "name2",
            "Set name2",
            23);

        add(&TestFlagsBase::p,
            "name3",
            "Set name3",
            false);
    }
};

/*
 * 为一个参数设置两个变量*/
//class TestFlags : public virtual FlagsBase {
//public:
//    TestFlags() {
//        add(&TestFlags::name1,
//                "name1",
//                Some("alias1"),
//                "Also set name1");
//
//        add(&TestFlags::name2,
//            "name2",
//            Some("alias2"),
//            "Also set name2",
//            true);
//
//        add(&TestFlags::name3,
//                "name3",
//                Some("alias3"),
//                "Also set name3",
//                "value8");
//    }
//
//    Option<string> name1;
//    bool name2;
//    string name3;
//};

static int PRS(int argc, char* argv[])
{
    TestFlagsBase flags;

    flags.setUsageMessage("THIS IS DOCUMENTATION");
    flags.usage();

    char ch;

    while ((ch = getopt(argc, argv, "n:m:p::help")) != -1) {
        switch (ch) {
            case 'n':
                printf("The argument of -n is %s\n\n", optarg);
                break;
            case 'm':
                printf("The argument of -m is %s\n\n", optarg);
                break;
            case 'p':
                printf("The argument of -p is %s\n\n", optarg);
                break;
//            case 'd':
//                *opts |= OPTION_D;
//                break;
//            case 'e':
//                *opts |= OPTION_E;
//                break;
//            case 'f':
//                *opts |= OPTION_F;
//                printf("-f optarg=%s\n", optarg);
//                break;
//            case 'g':
//                *opts |= OPTION_G;
//                printf("-g optarg=%s\n", optarg);
//                break;
            case 'h':
//                *opts |= OPTION_H;
                cout << flags.usage() << endl;
                break;
            default:
//                cout << "0" << endl;
////                fprintf(stderr,
////                        "our: %s: invalid option -- '%c'\n",
////                        programe_name, optopt);
////                exit(1);
                cout << "0" << endl;
                break;
        }
    }

    return 0;
}

int main(int argc,char** argv) {

    TestFlagsBase flags;

    Try<Warnings> load = flags.load("CHAMELEON",argc,argv);

    if(argc <= 1 ){
        cout << flags.usage() << endl;
    } else {
        if(load.isError()){
            cout << "PLEASE INPUT THE RIGHT TYPE" << endl;
            cout << flags.usage() << endl;
        } else{
            if( argv[1] = "--help"){
                cout << flags.usage() << endl;
            } else {
                cout << flags.n << endl;
                cout << flags.m << endl;
                cout << flags.p << endl;
            }
        }

    }



//    TestFlags flags2;

//    int retval,opts,i;
//
//    for(int i= 0;i<argc;i++){
//        printf("%s ", argv[i]);
//    }
//    retval = PRS(argc, argv);
//    retval = PRS(argc,argv,&opts);
//    if (retval < 0) {
//        exit(1);
//    }
//    printf("\n");
    /**
     * KEY AND VALUE
     * */
//    const map<string, Option<string>> values = {
//            {"name1", Some("billy joe1")},
//            {"name1", Some("43")},
//            {"name3", Some("false")}
//    };
//
//    flags.load(values);
//
//    cout << flags.n << endl;
//    cout << flags.m<< endl;

//    cout << flags.usage() << endl;

/**
 * ENVIORMENT
 * */
//    os::setenv("FLAGSTEST_name1", "billy joel_2");
//    os::setenv("FLAGSTEST_name2", "");
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

//    cout << flags.usage("--name1") << endl;
//
//    cout << flags.usage() << endl;
//
//    Try<Warnings> load = flags.load("FLAGSTEST_", arraySize(argv), argv);
//
//    cout << flags.name1 << endl;
//    cout << flags.name2 << endl;
//    cout << flags.name3 << endl;
}