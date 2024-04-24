#include <opp/TravellingSalesmanProblem.hpp>
#include <algorithm>
#include <cmath>

using opp::TravellingSalesmanProblem;
using opp::Solution;
using opp::Move;

TravellingSalesmanProblem::TravellingSalesmanProblem()
  :
  sz{42}, trmMax{14},
  distanceMatrix(sz, std::vector<int>(sz)), optimal{std::vector<City>(sz)} {

  // Generate initial solution
  std::uniform_int_distribution<int> udx{boundingBox.x, boundingBox.x + boundingBox.w};
  std::uniform_int_distribution<int> udy{boundingBox.y, boundingBox.y + boundingBox.h};
  for (Uint32 i = 0; i < optimal.order.size(); ++i) {
    optimal.order[i] = {i, {udx(rng), udy(rng)}};
  }

  // Calculate distances between cities
  for (Uint32 i = 0; i < optimal.order.size() - 1; ++i) {
    for (Uint32 j = i + 1; j < optimal.order.size(); ++j) {
      distanceMatrix[i][j] = sqrt(pow(optimal.order[i].location.x
                                      - optimal.order[j].location.x, 2) +
                                  pow(optimal.order[i].location.y
                                      - optimal.order[j].location.y, 2)); // Euclidean
      distanceMatrix[j][i] = distanceMatrix[i][j]; // Symmetric
    }
  }
}

Move TravellingSalesmanProblem::generateMove(const Solution& s) const {
  std::uniform_int_distribution<int> ud{0, sz - 1};
  int x, y;

  // Generate move from neighbourhood
  do {
    x = ud(rng);
    y = ud(rng);
  } while (x == y);

  // Deterministic ordering
  if (x > y) {
    std::swap(x, y);
  }

  return {s.order[y].name, x, s.order[x].name, y};
}

Solution TravellingSalesmanProblem::neighbour(const Solution& s, const Move& m) const {
  auto t = s;

  // Apply move to solution
  t.order[m.indexA] = s.order[m.indexB];
  t.order[m.indexB] = s.order[m.indexA];
  t.moveMade = m;

  // Calculate updated cost of solution efficiently

  // Handle left edge of B
  t.cost -= distanceMatrix[m.cityA][s.order[m.indexB - 1].name];
  t.cost += distanceMatrix[m.cityB][t.order[m.indexB - 1].name];

  // Handle right edge of B, with potential for last element
  if (m.indexB != sz - 1) {
    t.cost -= distanceMatrix[m.cityA][s.order[m.indexB + 1].name];
    t.cost += distanceMatrix[m.cityB][t.order[m.indexB + 1].name];
  } else {
    t.cost -= distanceMatrix[m.cityA][s.order[0].name];
    t.cost += distanceMatrix[m.cityB][t.order[0].name];
  }

  // Handle left edge of A, with potential for first element
  if (m.indexA != 0) {
    t.cost -= distanceMatrix[m.cityB][s.order[m.indexA - 1].name];
    t.cost += distanceMatrix[m.cityA][t.order[m.indexA - 1].name];
  } else {
    t.cost -= distanceMatrix[m.cityB][s.order[s.order.size() - 1].name];
    t.cost += distanceMatrix[m.cityA][t.order[t.order.size() - 1].name];
  }

  // Handle right edge of A
  t.cost -= distanceMatrix[m.cityB][s.order[m.indexA + 1].name];
  t.cost += distanceMatrix[m.cityA][t.order[m.indexA + 1].name];

  return t;
}

Solution TravellingSalesmanProblem::randomSolution() const {
  auto t = optimal;
  std::shuffle(t.order.begin(), t.order.end(), rng);
  t.cost = cost(t);
  return t;
}

Solution TravellingSalesmanProblem::select(const std::vector<Solution>& p) const {
  std::uniform_int_distribution<Uint64> ud{0, p.size() - 1};
  auto optimalS = p[ud(rng)];

  // Hold Tournament
  for (int i = 0; i < trmMax - 1; ++i) {
    auto t = p[ud(rng)];
    if (t.cost < optimalS.cost) {
      optimalS = t;
    }
  }

  return optimalS;
}

void TravellingSalesmanProblem::copyPreserved(
  const std::deque<bool>& b,
  const Solution& pA, const Solution& pB,
  Solution& cA, Solution& cB,
  std::deque<City>& vA, std::deque<City>& vB
) const {
  for (Uint32 i = 0; i < b.size(); ++i) {
    if (b[i]) {
      cA.order[i] = pA.order[i];
      vB.push_back(pB.order[i]);
    } else {
      cB.order[i] = pB.order[i];
      vA.push_back(pA.order[i]);
    }
  }
}

void TravellingSalesmanProblem::reorder(const Solution& p,
                                        std::deque<City>& v, std::deque<City>& w) const {
  for (const auto& city : p.order) {
    if (std::find(v.begin(), v.end(), city) != v.end()) {
      w.push_back(city);
    }
  }
}

void TravellingSalesmanProblem::copyChanged(
  const std::deque<bool>& b,
  Solution& cA, Solution& cB,
  std::deque<City>& wA, std::deque<City>& wB
) const {
  for (Uint32 i = 0; i < b.size(); ++i) {
    if (b[i]) {
      cB.order[i] = wB[0];
      wB.pop_front();
    } else {
      cA.order[i] = wA[0];
      wA.pop_front();
    }
  }
}

std::pair<Solution, Solution> TravellingSalesmanProblem::crossover(
  const Solution& pA,
  const Solution& pB) const {
  auto cA = pA;
  auto cB = pB;
  std::deque<City> vA, vB, wA, wB;
  std::deque<bool> b(pA.order.size());
  std::uniform_int_distribution<int> ud{0, 1};

  // Generate random bit string
  std::generate(b.begin(), b.end(), [&ud] {
    return !!ud(rng);
  });

  // Perform Crossover
  copyPreserved(b, pA, pB, cA, cB, vA, vB);
  reorder(pA, vB, wB);
  reorder(pB, vA, wA);
  copyChanged(b, cA, cB, wA, wB);

  // Update cost of solutions
  cA.cost = cost(cA);
  cB.cost = cost(cB);

  return {cA, cB};
}

int TravellingSalesmanProblem::cost(const Solution& s) const {
  int c = 0;

  // Calculate cost of solution
  for (Uint32 i = 0; i < s.order.size() - 1; ++i) {
    c += distanceMatrix[s.order[i].name][s.order[i + 1].name];
  }
  c += distanceMatrix[s.order[s.order.size() - 1].name][s.order[0].name];

  return c;
}

thread_local std::random_device TravellingSalesmanProblem::rd{};

thread_local std::mt19937 TravellingSalesmanProblem::rng{rd()};
