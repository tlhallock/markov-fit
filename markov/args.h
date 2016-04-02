
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

  Args& operator=(const Args& other);

  bool feasible() const;
  void normalize();
  void randomize(double wait);

  int get_size() const { return n; }
  double get_prob(int i, int j) const { return probs[n * i + j]; }
  void set_prob(int i, int j, double val) const { probs[n * i + j] = val; }

  double get_lambda(int i) const { return lambdas[i]; }
  void set_lambda(int i, double val) {lambdas[i] = val; }
  double* get_distro(int i) const { return &probs[i * n]; }
  
  void write(const char *filename);
  void writeMatlab(const char *filename);

};



#endif
