#include <Report.h>

#include <easylogging++.h>
#include <fmt/core.h>

Report::Report(unsigned long long from, unsigned long long to) {
  unsigned long long size = (from>>1);
  v.reserve(std::log(to/from)/std::log(2) + 3);
  for (; size <= to; size <<=1) {
    if (VLOG_IS_ON(2)) LOG(INFO) << "size = " << size;
    v.emplace_back(size);
  }
  v.emplace_back((size>>2)*3);
}

YAML::Emitter& operator<< (YAML::Emitter& em, const Report &rep) {
  long long counter = 0;
  auto lambda = [&em](const std::tuple<long long, long long, long long> &it) {
    em << YAML::BeginMap;

    em << YAML::Key << "experiment" << YAML::Value << YAML::BeginMap;

    em << YAML::Key << "number" << YAML::Value << std::get<0>(it);
    em << YAML::Key << "input_data" << YAML::Value << YAML::BeginMap;
    em << YAML::Key << "buffer_size" << YAML::Value << fmt::format("{}mb", (((double)std::get<1>(it))/1048576));
    em << YAML::EndMap;

    em << YAML::Key << "results" << YAML::Value << YAML::BeginMap;
    em << YAML::Key << "duration" << YAML::Value << (std::to_string(std::get<2>(it)) + "ns");
    em << YAML::EndMap;

    em << YAML::EndMap;

    em << YAML::EndMap;
  };
  em << YAML::BeginMap;

  const char *arr[] = {"right", "reverse", "random"};

  
  for (int i = 0; i < 3; i++) {
    em << YAML::Key << "investigation";
    em << YAML::Value << YAML::BeginMap;
    em << YAML::Key << "travel_variant" << YAML::Value << arr[i];
    em << YAML::Key << "experiments" << YAML::Value << YAML::BeginSeq;
    counter = 0;
    for (const auto& it : rep.v) {
      long long time;
      switch (i) {
        case 0: time = it.getRight(); break;
        case 1: time = it.getReverse(); break;
        case 2: time = it.getRandom(); break;
      }
      lambda(std::make_tuple(counter++, it.getLen(), time));
    }
    em << YAML::EndSeq;
    em << YAML::EndMap;
  }
  em << YAML::EndMap;
  return em;
}
