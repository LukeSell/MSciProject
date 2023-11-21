#include <gui/Menu.hpp>
#include <gui/Button.hpp>
#include <gui/Application.hpp>
#include <mh/TabuSearch.hpp>
#include <mh/IteratedLocalSearch.hpp>
#include <mh/GeneticAlgorithm.hpp>
#include <mh/MemeticAlgorithm.hpp>
#include <Logger.hpp>
#include <opp/TravellingSalesmanProblem.hpp>
#include <gui/TravellingSalesmanProblemDisplay.hpp>

gui::Menu::Menu() : Screen{} {

  using Tsp = opp::TravellingSalesmanProblem;
  using Ts = mh::TabuSearch;
  using Ils = mh::IteratedLocalSearch;
  using Ga = mh::GeneticAlgorithm;
  using Ma = mh::MemeticAlgorithm;

  auto d = new TravellingSalesmanProblemDisplay{};
  auto a = &Application::getInstance();

  addComponents({

    d,

    new Button(1300, 190, [a, d]{a->killThreads(); d->newTsp();}, "New Problem"),

    new Button(1300, 290, [a, d]{
      a->addThread(
      [](Tsp tsp) {
        return Ts{tsp}.findOptimal();
      },
      d->getTsp());
    }, "Tabu Search"),

    new Button(1300, 390, [a, d]{
      a->addThread(
      [](Tsp tsp) {
        return Ils{tsp}.findOptimal();
      },
      d->getTsp());
    }, "Iterated Local Search"),

    new Button(1300, 490, [a, d]{
      a->addThread(
      [](Tsp tsp) {
        return Ga{tsp}.findOptimal();
      },
      d->getTsp());
    }, "Genetic Algorithm"),

    new Button(1300, 590, [a, d]{
      a->addThread(
      [](Tsp tsp) {
        return Ma{tsp}.findOptimal();
      },
      d->getTsp());
    }, "Memetic Algorithm"),

    new Button(1300, 690, [a]{
      a->addBenchmark(
      []{
        Logger{"benchmark/"}.benchmarkAll();
      });
    }, "Benchmark"),

    new Button(1300, 790, [a]{a->setRunning(false);}, "Quit")

  });
}
