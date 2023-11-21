#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <mh/Metaheuristic.hpp>
#include <opp/Solution.hpp>

/** Represents the result of a benchmark.
 *
 * \author Luke Sell
 */

struct Result {

  // The costs of the optimal solutions found by the metaheuristic
  int minCost;
  int avgCost;
  int maxCost;

  // The times taken by the metaheuristic
  int minTime;
  int avgTime;
  int maxTime;

};

/** Handles logging results and benchmarks to files.
 *
 * Also calculates benchmarking data for logging.
 *
 * \author Luke Sell
 */

class Logger {

 public:

  Logger(const Logger&) = delete;

  Logger& operator=(const Logger&) = delete;

  /** Creates and opens logging file with uniquely identifiable name.
   *
   * The combination of the current thread id and the current time produces an uniquely identifiable name.
   *
   * \param f Is the sub directory to be used.
   */

  Logger(const char* f) : file{
    std::string{
      f
      + std::to_string(
      std::hash<std::thread::id>{}(
        std::this_thread::get_id()))
      + std::to_string(
        std::chrono::system_clock::to_time_t(
          std::chrono::system_clock::now()))
      + ".log"}} {}

  ~Logger() {
    file.close();
  }

  /** Logs the optimal solutions returned by metaheuristics.
   *
   * \param s Is the solution to be logged.
   */

  void log(const opp::Solution& s);

  /** Logs the benchmarking data.
   *
   * \param w Is the benchmarking data to be logged.
   */

  void log(const std::vector<Result>& w);

  /** Benchmarks the metaheuristic and calculates benchmarking data.
   *
   * \param m Is the metaheuristic to be benchmarked.
   *
   * \return The benchmarking data.
   */

  Result benchmark(const mh::Metaheuristic& m);

  /** Benchmarks all metaheuristics and logs the results.
   */

  void benchmarkAll();

 private:

  /** The number of generated problems to use in the benchmarking process.
   */

  const int nProblems = 5;

  /** The number of times to run the metaheuristic on a problem
   * to produce necessary data to calculate minimum, average and maximum values.
   */

  const int nRuns = 3;

  /** The total number of runs for each metaheuristic during the benchmarking process.
   */

  const int totalRuns = nProblems * nRuns;

  /** The file being logged to.
   */

  std::ofstream file;

};

#endif // BENCHMARK_HPP_INCLUDED
