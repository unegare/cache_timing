#include <Experiment.h>

#include <chrono>
#include <easylogging++.h>

long long* Experiment::createAnArray() {
  long long *arr = new long long[len>>3];
  long long counter{1}, oldcounter{1};
  while (counter < (len>>6)*0.99) {
    for (long long j{0}; j < (len>>6); j++) {
      arr[(j<<3)] = 0;
    }
    for (long long j, i{0}; i < (len>>6); i++) {
      j = (((unsigned long long)rand()) % (len>>6)) << 3;
      while(arr[j] != 0) {
        if (VLOG_IS_ON(9)) LOG(TRACE) << "{" << j << ", " << arr[j] << "} ";
        j += 8;
        if (j >= (len>>3)) {
          j -= (len>>3);
        }
      }
      if (VLOG_IS_ON(9)) LOG(TRACE) << j << " : " << (i<<3) << std::endl;
      arr[j] = (i<<3);
    }

    counter = 1;
    for(long long t{arr[0]}; t != 0; counter++) {
      t = arr[t];
    }
    if (counter > oldcounter) {
      oldcounter = counter;
      if (VLOG_IS_ON(9)) LOG(TRACE) << "counter = " << counter << std::endl;
    }
  }
  for (long long i{1}; i < (len>>3); i++) {
    if (i % 8) {
      arr[i] = rand();
    }
  }
  return arr;
}

void Experiment::doIt(long long *arr) {
  long long temp{0}, temp2{0};
  try {
    std::chrono::time_point<std::chrono::high_resolution_clock> t1, t2;
    t1 = std::chrono::high_resolution_clock::now();
    for (int j, i{1024}; i > 0; i--) {
      for(j = 0; j < (len>>6); j++) {
        temp+= arr[(j<<3)];
      }
    }
    t2 = std::chrono::high_resolution_clock::now();
    right = std::chrono::duration_cast<std::chrono::nanoseconds>((t2-t1)/(1024*(len>>6))).count();
//    LOG(INFO) << (t2 - t1).count();

    t1 = std::chrono::high_resolution_clock::now();
    for (int j, i{1024}; i > 0; i--) {
      for(j = (len>>6) -1; j >= 0; j--) {
        temp+= arr[(j<<3)];
      }
    }
    t2 = std::chrono::high_resolution_clock::now();
    reverse = std::chrono::duration_cast<std::chrono::nanoseconds>((t2-t1)/(1024*(len>>6))).count();
//    LOG(INFO) << (t2 - t1).count();

    t1 = std::chrono::high_resolution_clock::now();
    for (int j, i{1024}; i > 0; i--) {
      temp = 0;
      for(j = (len>>6); j > 0; j--) {
//    			LOG(TRACE) << temp << " ";
        temp = arr[temp];
      }
//    		LOG(TRACE) << std::endl;
    }
    t2 = std::chrono::high_resolution_clock::now();
    random = std::chrono::duration_cast<std::chrono::nanoseconds>((t2-t1)/(1024*(len>>6))).count();
//    LOG(INFO) << (t2 - t1).count();

    delete[] arr;
//    LOG(INFO) << "right " << right << "reverse " << reverse << " random " << random << std::endl;
  } catch(...) {
    delete[] arr;
    throw;
  }
}

Experiment::Experiment(long long _len): len{_len} {
  doIt(createAnArray());
}
long long Experiment::getRight() const {
  return right;
}
long long Experiment::getReverse() const {
  return reverse;
}
long long Experiment::getRandom() const {
  return random;
}
long long Experiment::getLen() const {
  return len;
}
