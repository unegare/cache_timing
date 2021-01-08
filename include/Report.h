#ifndef REPORT_H_
#define REPORT_H_

#include <vector>
#include <yaml-cpp/yaml.h>

#include <Experiment.h>

class Report {
  std::vector<Experiment> v;
public:
  Report(unsigned long long from, unsigned long long to);
  friend YAML::Emitter& operator<< (YAML::Emitter& em, const Report &rep);
};

#endif
