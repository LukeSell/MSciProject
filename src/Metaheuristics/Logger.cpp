#include <Logger.hpp>
#include <algorithm>
#include <opp/TravellingSalesmanProblem.hpp>
#include <mh/TabuSearch.hpp>
#include <mh/IteratedLocalSearch.hpp>
#include <mh/GeneticAlgorithm.hpp>
#include <mh/MemeticAlgorithm.hpp>

void Logger::log(const opp::Solution& s) {
  file << "Order:\n";
  for (const auto& c : s.order) {
    file << "City " << c.name << "\n";
  }
  file << "\nCost: " << s.cost << "\n" << std::endl;
}

void Logger::log(const std::vector<Result>& w) {
  int minCost = 99999;
  int avgCost = 0;
  int maxCost = 0;
  int minTime = 99999;
  int avgTime = 0;
  int maxTime = 0;

  // Calculate minimum, average and maximum values overall
  for (const auto& r : w) {
    avgCost += r.avgCost;
    minCost = std::min(minCost, r.minCost);
    maxCost = std::max(maxCost, r.maxCost);
    avgTime += r.avgTime;
    minTime = std::min(minTime, r.minTime);
    maxTime = std::max(maxTime, r.maxTime);
  }

  // Log benchmarking data for cost
  file << "Min Cost: " << minCost
       << "p | Avg Cost: " << avgCost / totalRuns
       << "p | Max Cost: " << maxCost << "p\n";

  // Log benchmarking data for time
  file << "Min Time: " << minTime
       << "ms | Avg Time: " << avgTime / totalRuns
       << "ms | Max Time: " << maxTime << "ms\n" << std::endl;
}

Result Logger::benchmark(const mh::Metaheuristic& m) {
  int minCost = 99999;
  int avgCost = 0;
  int maxCost = 0;
  int minTime = 99999;
  int avgTime = 0;
  int maxTime = 0;

  // Calculate minimum, average and maximum values for problem
  for (int i = 0; i < nRuns; ++i) {
    auto t = std::chrono::high_resolution_clock::now();
    auto c = m.findOptimal().cost;
    auto d = std::chrono::duration_cast <
             std::chrono::duration<int, std::milli>> (
               std::chrono::high_resolution_clock::now() - t).count();
    avgCost += c;
    minCost = std::min(minCost, c);
    maxCost = std::max(maxCost, c);
    avgTime += d;
    minTime = std::min(minTime, d);
    maxTime = std::max(maxTime, d);
  }

  return {minCost, avgCost, maxCost, minTime, avgTime, maxTime};
}

void Logger::benchmarkAll() {
  std::vector<const char*> m{
    "Tabu Search",
    "Iterated Local Search",
    "Genetic Algorithm",
    "Memetic Algorithm"};
  std::vector<std::vector<Result>> v(m.size());

  // Benchmarks each metaheuristic on a number of generated problems
  for (int i = 0; i < nProblems; ++i) {
    opp::TravellingSalesmanProblem tsp{};
    v[0].push_back(benchmark(mh::TabuSearch{tsp}));
    v[1].push_back(benchmark(mh::IteratedLocalSearch{tsp}));
    v[2].push_back(benchmark(mh::GeneticAlgorithm{tsp}));
    v[3].push_back(benchmark(mh::MemeticAlgorithm{tsp}));
  }

  // Logs the benchmarking data
  for (Uint32 i = 0; i < m.size(); ++i) {
    file << m[i] << "\n";
    log(v[i]);
  }
}
