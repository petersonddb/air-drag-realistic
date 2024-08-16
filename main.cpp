#include <fstream>
#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#define FILE_NAME_DATA "drag.dat"

using json = nlohmann::json;

struct params {
  double P, p, C, A, m, v0, n, h, time_step, t;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(params, P, p, C, A, m, v0, n, h, time_step,
                                   t)

struct data {
  std::vector<double> t, v;
};

void load_params(params &p, std::string file_name);
void calculate(data &d, const params &p);
void store_data(const data &d, std::string file_name);

int main(int argc, char **argv) {
  params p;
  data d;

  load_params(p, argv[1]);
  calculate(d, p);
  store_data(d, FILE_NAME_DATA);
}

void load_params(params &p, std::string file_name) {
  std::ifstream file(file_name);
  json read_json{json::parse(file)};
  read_json.get_to(p);
}

void calculate(data &d, const params &p) {
  int n = p.t / p.time_step;
  std::vector<double> t(n);
  std::vector<double> v(n);

  t[0] = 0;
  v[0] = p.v0;
  for (int i = 0; i < n - 1; i++) {
    t[i + 1] = t[i] + p.time_step;
    v[i + 1] = v[i] + (p.P / (p.m * v[i]) - (-9.8 * sin(9.9e-2)) -
                       (p.n * p.A * v[i]) / (p.m * p.h) -
                       (p.C * p.p * p.A * v[i] * v[i]) / (2 * p.m)) *
                          p.time_step;
  }

  d.t = t;
  d.v = v;
}

void store_data(const data &d, std::string file_name) {
  std::ofstream file(file_name);
  int n = d.t.size();

  for (int i = 0; i < n; i++) {
    file << d.t[i] << " " << d.v[i] << std::endl;
  }
}
