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


using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::istringstream;

using strings::tokenize;

using process::subprocess;
using process::Subprocess;

namespace weiguo_proc {

    struct CPU {
        CPU(string _cpuID, string _coreID, string _physicalID, string _cpucores, string _modelname,
            string _cpuMHz, string _L1dcache, string _L1icache, string _L2cache, string _L3cache)
                : cpuID(_cpuID), coreID(_coreID), physicalID(_physicalID), cpucores(_cpucores), modelname(_modelname),
                  cpuMHz(_cpuMHz), L1dcache(_L1dcache), L1icache(_L1icache), L2cache(_L2cache), L3cache(_L3cache) {}

        // These are non-const because we need the default assignment operator.
        string cpuID; // "processor"
        string coreID; // "core id"
        string physicalID; // "physical id"
        string cpucores;  // "cpu cores"
        string modelname;  //"model name"
        string cpuMHz;  //"cpu MHz"
        string L1dcache;  //"L1dcache"
        string L1icache;  //"L1icache"
        string L2cache;  //"L2cache"
        string L3cache;  //"L3cache"
    };

    inline std::ostream &operator<<(std::ostream &stream, const CPU &cpu) {
        return stream << "CPU (id:" << cpu.cpuID << ", "
                      << "core ID:" << cpu.coreID << ", "
                      << "physical ID:" << cpu.physicalID << ", "
                      << "cpu cores:" << cpu.cpucores << ", "
                      << "model name:" << cpu.modelname << ", "
                      << "cpu MHz:" << cpu.cpuMHz << ", "
                      << "L1d cache:" << cpu.L1dcache << ", "
                      << "L1i cache:" << cpu.L1icache << ", "
                      << "L2 cache:" << cpu.L2cache << ", "
                      << "L3 cache:" << cpu.L3cache << ")";
    }

// Reads from /proc/cpuinfo and returns a list of CPUs.
    inline Try<std::list<CPU>> cpus() {

        //gain the information of cpu
        std::list<CPU> results;

        std::ifstream file("/proc/cpuinfo");


        if (!file.is_open()) {
            return Error("Failed to open /proc/cpuinfo");
        }

        // Placeholders as we parse the file.
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
            if (line.find("processor") == 0 ||
                line.find("physical id") == 0 ||
                line.find("core id") == 0 ||
                line.find("cpu cores") == 0 ||
                line.find("model name") == 0 ||
                line.find("cpu MHz") == 0) {

                /* split delimiter according to what
                 * as I use the ": ",it delimit space and the :
                 * */
                std::vector<std::string> split = strings::split(line, ":");


                if (split.size() < 2) {
                    return Error("Unexpected format in /proc/cpuinfo: " +
                                 stringify(split));
                }

                /*.get方法和isSome是Option封装的信息
                   Now save the value.
                   */
                if (line.find("processor") == 0) {
                    if (cpuID.isSome()) {  //char的默认值是false
                        // The physical id and core id are not present in this case.
                        results.push_back(CPU(cpuID.get(), 0, 0, 0, 0, 0, 0, 0, 0, 0));
                    }
                    cpuID = split.back().data();
                } else if (line.find("physical id") == 0) {
                    if (physicalID.isSome()) {
                        return Error("Unexpected physical ID in /proc/cpuinfo");
                    }
                    physicalID = split.back().data();
                } else if (line.find("core id") == 0) {
                    if (coreID.isSome()) {
                        return Error("Unexpected core ID in /proc/cpuinfo");
                    }
                    coreID = split.back().data();
                } else if (line.find("cpu cores") == 0) {
                    if (cpucores.isSome()) {
                        return Error("Unexpected cpu cores in /proc/cpuinfo");
                    }
                    cpucores = split.back().data();
                } else if (line.find("model name") == 0) {
                    if (modelname.isSome()) {
                        return Error("Unexpected model name in /proc/cpuinfo");
                    }
                    modelname = split.back().data();
                } else if (line.find("cpu MHz") == 0) {
                    if (cpuMHz.isSome()) {
                        return Error("Unexpected cpu MHz in /proc/cpuinfo");
                    }
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
                    vector<string> vec = strings::split(lscpu[i],":");
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
                    modelname.isSome() && cpuMHz.isSome() && L1dcache.isSome() && L2cache.isSome() && L1dcache.isSome()
                    && L3cache.isSome()) {
                    results.push_back(CPU(cpuID.get(), coreID.get(), physicalID.get(), cpucores.get(), modelname.get(),
                                          cpuMHz.get(), L1dcache.get(), L1icache.get(), L2cache.get(), L3cache.get()));
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
        }
        // Add the last processor if the physical id and core id were not present.
        if (cpuID.isSome()) {
            // The physical id and core id are not present.
            results.push_back(CPU(cpuID.get(), 0, 0, 0, 0, 0, 0, 0, 0, 0));
        }
        if (file.fail() && !file.eof()) {
            return Error("Failed to read /proc/cpuinfo");
        }
        return results;
    }
}

#endif //LIBPROCESS_START_CPU_INFO_H

