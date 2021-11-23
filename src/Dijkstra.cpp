/*
* Shortest Route
*
* Author: Chukwu Jennifer
* Email: Jnyfaah@gmail.com
* Project Date: Nov, 2021
*/

#include "adjacencyList.hpp"
#include <emscripten/bind.h>
#include <vector>


/*
*
* Class DijkstraShortestPath
* finds shortest part between two cities using adjacency list
* input: two cities
* returns shortest paths betwen inputs and cost
*
*/

class DijsktraShortestPath {
public:
    DijsktraShortestPath(const AdjacencyList& adjacencyList, int nodeIdA, int nodeIdB)
        : m_adjacencyList(adjacencyList), m_nodeIdA(nodeIdA), m_nodeIdB(nodeIdB) {}

    std::tuple<float, std::vector<OutdegreeGraphNode>> computePath() {
        std::vector<OutdegreeGraphNode> result;

        auto [minCost, _] = computeCost();
        auto node = m_nodeIdB;
        int i = 0;
        for (auto iter = m_predecessors.find(node); iter != m_predecessors.end(); iter = m_predecessors.find(node)) {
            result.push_back({iter->second, m_minCosts[node] - m_minCosts[iter->second]});
            node = iter->second;
            if (i++ > 10000) {
                throw std::logic_error("WTF");
            }
        }
        std::reverse(result.begin(), result.end());
        return {minCost, result};
    }

    std::tuple<float, bool> computeCost() {
        m_minCosts.clear();
        m_predecessors.clear();

        constexpr auto Infinity = std::numeric_limits<float>::max();
        for (auto& [nodeId, _] : m_adjacencyList.getNodeIdLookup()) {
            m_minCosts[nodeId] = Infinity;
        }

        const auto cmp = [this](int nodeIdA, int nodeIdB){ return m_minCosts.at(nodeIdA) > m_minCosts.at(nodeIdB); };
        std::priority_queue<int, std::vector<int>, decltype(cmp)> priorityQueue(cmp);

        m_minCosts[m_nodeIdA] = 0.0;
        priorityQueue.push(m_nodeIdA);

        while(!priorityQueue.empty()) {
            auto currentNodeId = priorityQueue.top();
            priorityQueue.pop();
            auto currentNodeIdTotalCost = m_minCosts[currentNodeId];

            for (auto [nodeId, cost] : m_adjacencyList.getOutboundNodes(currentNodeId)) {
                auto nodeIdTotalCost = m_minCosts.at(nodeId);
                if (cost < 0) {
                    throw std::invalid_argument("Negative costs are not allowed");
                }
                if (nodeIdTotalCost > currentNodeIdTotalCost + cost) {
                    m_minCosts[nodeId] = currentNodeIdTotalCost + cost;
                    m_predecessors[nodeId] = currentNodeId;
                    priorityQueue.push(nodeId);
                }
            }
            if (currentNodeId == m_nodeIdB) {
                break;
            }
        }

        if (auto minCost = m_minCosts[m_nodeIdB]; minCost != Infinity) {
            return {minCost, true};
        }
        return {Infinity, false};
    }


private:
    const AdjacencyList& m_adjacencyList;
    const int m_nodeIdA;
    const int m_nodeIdB;

    std::unordered_map<int, float> m_minCosts;
    std::unordered_map<int, int> m_predecessors;
};



std::vector<std::string> Dijkstra(std::string cityA , std::string cityB) {
      std::vector<std::string>result;
try {
    CSVReader csv("../utils/distance-km.csv");
    std::vector<std::vector<std::string>> m_csv = csv.getDataAsTable();

    MileageChartCSVToAdjacencyListCreator chart;
    AdjacencyList adjList = chart.create(m_csv);

    auto nodeIdA = adjList.getNodeId(cityA).value();
    auto nodeIdB = adjList.getNodeId(cityB).value();

    DijsktraShortestPath dijkstra(adjList, nodeIdA, nodeIdB);
    auto [minDistance, paths] = dijkstra.computePath();
    if (!paths.empty()) {
        
        result.push_back(std::to_string(minDistance));
        result.push_back(cityA);

        for (auto iter = paths.begin(); iter != paths.end(); std::advance(iter, 1)) {
            auto nextCityId = std::next(iter) != paths.end() ? std::next(iter)->nodeId : nodeIdB;
            auto [currCityId, distance] = *iter;
            result.push_back(adjList.getNodeName(nextCityId).value());
        
        }
    } else {
        std::string res ("Unfortunately, there is no road between " + cityA + " and " +cityB );
        result.push_back(res);
    }

} catch (std::exception& e) {
    result.push_back(e.what());
 
  }
  return result;
}


EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("Dijkstra", &Dijkstra);

  // register bindings for std::vector<int> and std::map<int, std::string>.
  emscripten::register_vector<std::string>("vector<std::string>");
}


