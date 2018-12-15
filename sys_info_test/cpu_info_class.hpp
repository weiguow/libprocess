//
// Created by weiguow on 18-11-19.
//

#ifndef LIBPROCESS_START_CPU_INFO_H
#define LIBPROCESS_START_CPU_INFO_H

#include <fstream>
#include <sstream>
#include <iostream>

#include <error.h>
#include <list>
#include <string>
#include <vector>

#include <sstream>

#include <stout/option.hpp>
#include <stout/try.hpp>
#include <stout/numify.hpp>
#include <stout/os/int_fd.hpp>

#include <process/io.hpp>
#include <process/future.hpp>
#include <process/subprocess.hpp>

#include <cpuinfo_pro.pb.h>


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::list;
using std::istringstream;
using std::ostream;

using strings::tokenize;

using process::subprocess;
using process::Subprocess;


/**
 * 定义struct CPU,数据结构
 */
class cpu_collector {

private:

public:


    vector<AllCpuInfo> get_cpu_info() {

        SingleCpuInfo sci;
        vector<SingleCpuInfo> result_sci;

        AllCpuInfo aci;
        vector<AllCpuInfo> result_aci;

        std::ifstream file("/proc/cpuinfo");

        if (!file.is_open()) {
            cout << "Failed to open /proc/cpuinfo" << endl;
        }

        Option<string> cpuID;
        Option<string> coreID;
        Option<string> physicalID;
        Option<string> cpucores;
        Option<string> modelname;
        Option<string> cpuMHz;
        Option<string> L1dcache;
        Option<string> L1icache;
        Option<string> L2cache;
        Option<string> L3cache;

        std::string line;
        while (std::getline(file, line)) {

            std::vector<std::string> split = strings::split(line, ":");
            if (line.find("processor") == 0) {
                cpuID = split.back().data();
            } else if (line.find("physical id") == 0) {
                physicalID = split.back().data();
            } else if (line.find("core id") == 0) {
                coreID = split.back().data();
            } else if (line.find("cpu cores") == 0) {
                cpucores = split.back().data();
            } else if (line.find("model name") == 0) {
                modelname = split.back().data();
            } else if (line.find("cpu MHz") == 0) {
                cpuMHz = split.back().data();
            }

            Try<Subprocess> cache = subprocess(
                    "lscpu",
                    Subprocess::FD(STDIN_FILENO),
                    Subprocess::PIPE(),
                    Subprocess::FD(STDIN_FILENO)
            );
            process::Future<string> ganied = process::io::read(cache.get().out().get());
            vector<string> lscpu = strings::split(ganied.get(), "\n");
            for (int i = 0; i < lscpu.size(); i++) {
                vector<string> vec = strings::split(lscpu[i], ":");
                if (vec.front() == "L1d cache") {
                    L1dcache = strings::trim(vec.back());
                } else if (vec.front() == "L1i cache") {
                    L1icache = strings::trim(vec.back());
                } else if (vec.front() == "L2 cache") {
                    L2cache = strings::trim(vec.back());
                } else if (vec.front() == "L3 cache") {
                    L3cache = strings::trim(vec.back());
                }
            }

            //finally create a CPU if we have all the information.
            if (cpuID.isSome() && coreID.isSome() && physicalID.isSome() && cpucores.isSome() &&
                modelname.isSome() && cpuMHz.isSome() && L1dcache.isSome() && L2cache.isSome() &&
                L1dcache.isSome() && L3cache.isSome()) {


                aci.add_sci()->set_cpuid(cpuID.get());
                aci.add_sci()->set_coreid(coreID.get());
                aci.add_sci()->set_physicalid(physicalID.get());
                aci.add_sci()->set_cpucores(cpucores.get());
                aci.add_sci()->set_modelname(modelname.get());
                aci.add_sci()->set_cpumhz(cpuMHz.get());
                aci.add_sci()->set_l1dcache(L1dcache.get());
                aci.add_sci()->set_l1icache(L1icache.get());
                aci.add_sci()->set_l2cache(L2cache.get());
                aci.add_sci()->set_l3cache(L3cache.get());

                result_aci.push_back(aci);


                cpuID = None();
                coreID = None();
                physicalID = None();
                cpucores = None();
                modelname = None();
                cpuMHz = None();
                L1dcache = None();
                L1icache = None();
                L2cache = None();
                L3cache = None();
            }
        }

//        for(auto i = result_aci.begin();i!=result_aci.end();i++){
//            cout << i.operator*().sci(). << endl;
//        }
    }

//    inline std::ostream &operator<<(std::ostream &stream, const AllCpuInfo &allCpuInfo) {
//        return stream << "CPU (cpu ID:" << cpu.cpuid() << ", "
//                      << "core ID:" << cpu.coreid() << ", "
//                      << "physical ID:" << cpu.physicalid() << ", "
//                      << "cpu cores:" << cpu.cpucores() << ", "
//                      << "model name:" << cpu.modelname() << ", "
//                      << "cpu MHz:" << cpu.cpumhz() << ", "
//                      << "L1d cache:" << cpu.l1dcache() << ", "
//                      << "L1i cache:" << cpu.l1icache() << ", "
//                      << "L2 cache:" << cpu.l2cache() << ", "
//                      << "L3 cache:" << cpu.l3cache()<< ")";
//    }

};


#endif //LIBPROCESS_START_CPU_INFO_H

