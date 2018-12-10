//
// Created by weiguow on 18-11-19.
//
#include <iostream>
#include <list>
#include <set>
#include <map>

#include <process/subprocess.hpp>
#include <process/io.hpp>

using std::cout;
using std::endl;
using std::set;
using std::list;

using std::vector;
using std::string;
using std::map;

using process::subprocess;
using process::Subprocess;
using strings::trim;

int main(){
    string L1dcache;
    string L1icache;
    string L2cache;
    string L3cache;

    Try<Subprocess> cache = subprocess(
            "lscpu",
            Subprocess::FD(STDIN_FILENO),
            Subprocess::PIPE(),
            Subprocess::FD(STDIN_FILENO)
    );
    process::Future<string> ganied = process::io::read(cache.get().out().get());
    string string_test = ganied.get();

////    cout << string_test << endl;
//    cout << *string_test.begin() << endl;
//    cout << *string_test.end() << endl;
//
//    auto string1 = strings::split(string_test," ");
//    cout << string1.front() << endl;
    vector<string> lscpu = strings::tokenize(ganied.get(), "\n");
    for(int i=0;i<lscpu.size();i++){
//        cout << lscpu[i] << endl;
        vector<string> vec = strings::split(lscpu[i],":");
        if (vec.front() == "L1d cache") {

            L1dcache = strings::trim(vec.back());
            cout << L1dcache << endl;
        } else if (vec.front() == "L1i cache") {
            L1icache = vec.back();
        } else if (vec.front() == "L2 cache") {
            L2cache = vec.back();
        } else if (vec.front() == "L3 cache") {
            L3cache = vec.back();
        }

    }

//    for (vector<string>::iterator vec = lscpu.begin(); vec != lscpu.end(); vec++) {
//        cout << *vec << endl;
//        if (*vec == "L1d cache") {
//            cout << *(vec + 1) << endl;
//            L1dcache = *vec;
//        } else if (*vec == "L1i cache") {
//            cout << *vec << endl;
//            L1icache = *vec;
//        } else if (*vec == "L2 cache") {
//            L2cache = *vec;
//        } else if (*vec == "L3 cache") {
//            L3cache = *vec;
//        }
//
//    }
};

//    std::ifstream file("/proc/cpuinfo");
//    char mname;
//    unsigned int id;
//    std::string line;
//    while(std::getline(file,line)) {
////        cout << line << endl;
//
////        std::vector<std::string> tokens = strings::tokenize(line, ": ");
//         //tokens.back()返回的是每个属性的值,返回的东西不全,分割开之后返回的是名称的一部分
////         cout << tokens.front() << endl;
//
//        //分割完之后一个数据就是一个数组
//
//        vector<string> split = strings::split(line,":");
//        if(line.find("model name") == 0){
//            cout << split.back().data() << endl;
//        }
////        cout << split.front() << endl;
////        cout << split.back() << endl;
////        cout << split.data() << endl;
////          cout << split.size() << endl;  //每组元素的size
////          cout << split.capacity() << endl;  //vector容器能存放的东西多少
//
////          if(line.find("processor") == 0){
////              auto id = split.back();
////          }
//
////          vector<string> pairs = strings::pairs(line,":");
////          cout << pairs.front() << endl;
//
////
////        cout << tokens.front() << endl;
//
////        for(int i=0;i<tokens.size();i++){
////                    cout << tokens.front()<< endl;
////
////        }
//
//
//        //把tokens.back转换成int形式输出
////        Try<unsigned int> value = numify<unsigned int>(tokens.back());
//
////        cout <<id<< endl;
//
//    }
