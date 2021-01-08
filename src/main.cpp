#include <iostream>
#include <chrono>
#include <iterator>
//#include <ranges>

#include <cstring>
#include <cstdlib>
#include <cmath>

#include <yaml-cpp/yaml.h>

//#define ELPP_DISABLE_TRACE_LOGS
//#define ELPP_DISABLE_DEBUG_LOGS
#include <easylogging++.h>


#include <Report.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
	START_EASYLOGGINGPP(argc, argv);
	int L1 = 32768, L3 = 131072;//1048576*8;
	try {
		L1 = std::stoi(std::getenv("L1"));
	} catch(...) {
	}
	try {
		L3 = std::stoi(std::getenv("L3"));
	} catch(...) {
	}

  Report rep(L1, L3);
  YAML::Emitter out;
  out << rep;
  std::cout << out.c_str() << std::endl;
	return 0;
}
