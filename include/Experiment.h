#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

class Experiment {
  long long right;
  long long reverse;
  long long random;
  long long len;

  long long* createAnArray();
  void doIt(long long *arr); 

public:
  Experiment(long long _len);
  long long getRight() const;
  long long getReverse() const;
  long long getRandom() const;
  long long getLen() const;
};

#endif
