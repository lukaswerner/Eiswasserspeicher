#include "Simulator.h"

#include <iostream>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include "Logger.h"

using namespace std;

Simulator::Simulator(const char* config_file) : config(config_file), 
        reservoir(&config) {
    controlServer = new ControlServer(&config, this, ioService);
    Logger::init(&config);
    ioService.run();
    controlServer->run();
}

void Simulator::run() {
    Logger::info("Simulator started");
    // int seconds = config->getStep() * 60;
    // boost::posix_time::seconds sleepTime(seconds);
    boost::posix_time::seconds sleepTime(1);
    while (true) {
        boost::this_thread::sleep(sleepTime);
        reservoir.step();
    }
}

void Simulator::command(string cmd) {
    if (cmd == "#ON") {
        reservoir.enablePumps();
    } else if (cmd == "OFF") {
        reservoir.disablePumps();
    }
}