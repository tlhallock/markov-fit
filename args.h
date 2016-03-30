
#ifndef ARGS_H_
#define ARGS_H_

class Args
{
 private:
  int n;
  double *probs;
  double *lambdas;
  
 public:
  Args(int n);
  Args(const char *filename);
  ~Args();

  bool feasible() const;
  void normalize();
  void randomize(double wait);

  int get_size() const { return n; }
  double get_prob(int i, int j) const { return probs[n * i + j]; }
  double get_lambda(int i) const { return lambdas[i]; }
  double* get_distro(int i) const { return &probs[i * n]; }
  
  void write(const char *filename);
  void writeMatlab(const char *filename);
};



#endif
