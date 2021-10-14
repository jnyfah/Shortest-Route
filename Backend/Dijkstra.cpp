#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <optional>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <cmath>
#include <tuple>
#include <set>


class CSVReader {
public:
    CSVReader(std::string inputFileName) {
        using namespace std::string_literals;
        std::ifstream file(inputFileName);
        std::string line;

        if (!file.is_open()) {
            throw std::invalid_argument("Unknown Input given; The filename \"" + inputFileName + "\" does not exist");
        }

        while (std::getline(file, line)) {
            m_csv_data.emplace_back();

            std::istringstream rowStream(line);
            std::string row;
            while (std::getline(rowStream, row, ',')) {
                m_csv_data.back().push_back(std::move(row));
            }
            if (!line.empty() and line.back() == ',') {
                m_csv_data.back().emplace_back();
            }

            if (m_csv_data.size() > 1) {
                auto beforeLastRowSize = std::prev(m_csv_data.end())->size();
                auto lastRowSize = std::prev(m_csv_data.end(), 2)->size();
                if (beforeLastRowSize != lastRowSize) {

                    std::cerr << "Row number: " + std::to_string(m_csv_data.size()) + " with length " +
                              std::to_string(beforeLastRowSize) + " has a different length than earlier row with length " +
                              std::to_string(lastRowSize);
                    throw std::invalid_argument("Row number: " + std::to_string(m_csv_data.size()) + " has a different length than earlier rows");
                }
            }
        }
    }

    int getTotalRowCount() const {
        return m_csv_data.size();
    }

    int getTotalColCount() const {
        return m_csv_data.empty() ? 0 : m_csv_data.back().size();
    }

    const std::vector<std::vector<std::string>>& getDataAsTable() const& {
        return m_csv_data;
    }

private:
    std::vector<std::vector<std::string>> m_csv_data;
};



struct OutdegreeGraphNode {
    int nodeId;
    float cost;
};




class AdjacencyList {
public:
    const std::vector<OutdegreeGraphNode>& getOutboundNodes(int nodeId) const {
        return m_adj_list.at(nodeId);
    }

    void connectNode(int nodeIdA, int nodeIdB, float cost) {
        assertNodeExists(nodeIdA);
        assertNodeExists(nodeIdB);
        m_adj_list[nodeIdA].push_back({nodeIdB, cost});
        m_adj_list[nodeIdB].push_back({nodeIdA, cost});
    }

    int addOrGetNode(std::string nodeName) {
        auto nextId = lastIdGenerated + 1;
        if (auto [iter, inserted] = m_node_to_id.insert({nodeName, nextId}); inserted) {
            m_id_to_node[nextId] = nodeName;
            lastIdGenerated++;
            return nextId;
        } else {
            return iter->second;
        }
    }

    std::optional<int> getNodeId(std::string nodeName) const {
        if (auto iter = m_node_to_id.find(nodeName); iter != m_node_to_id.end()) {
            return iter->second;
        }
        return std::nullopt;
    }


    std::optional<std::string> getNodeName(int id) const {
        if (auto iter = m_id_to_node.find(id); iter != m_id_to_node.end()) {
            return iter->second;
        }
        return std::nullopt;
    }

    void assertNodeExists(int nodeId) const {
        if (m_id_to_node.find(nodeId) == m_id_to_node.end()) {
            throw std::invalid_argument("city Id:" + std::to_string(nodeId) + " does not exist");
        }
    }

    int size() const {
        return m_adj_list.size();
    }

    const std::unordered_map<int, std::string>& getNodeIdLookup() const {
        return m_id_to_node;
    }

    const std::unordered_map<std::string, int>& getNodeNameLookup() const {
        return m_node_to_id;
    }

private:
    std::unordered_map<int, std::string> m_id_to_node;
    std::unordered_map<std::string, int> m_node_to_id;
    int lastIdGenerated = 0;

    std::unordered_map<int, std::vector<OutdegreeGraphNode>> m_adj_list;
};


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





class MileageChartCSVToAdjacencyListCreator
{
public:
    AdjacencyList create(std::vector<std::vector<std::string>>& csvTable) {
        AdjacencyList adjacencyList;

        for(auto row = 1u; row < csvTable.size(); row++) {
            auto rowNodeId = adjacencyList.addOrGetNode(csvTable[row][0]);
            for(auto col = 1u; col < csvTable[row].size(); col++) {
                if(!csvTable[row][col].empty())  {
                    auto colNodeId = adjacencyList.addOrGetNode(csvTable[0][col]);
                    auto cost = std::stof(csvTable[row][col]);
                    adjacencyList.connectNode(rowNodeId, colNodeId, cost);
                }
            }
        }

        return adjacencyList;
    }
};



int main() try {
    CSVReader csv("distance-km.csv");
    std::vector<std::vector<std::string>> m_csv = csv.getDataAsTable();

    MileageChartCSVToAdjacencyListCreator chart;
    AdjacencyList adjList = chart.create(m_csv);

    std::string cityA = "Aba";
    std::string cityB = "Bauchi";

    auto nodeIdA = adjList.getNodeId(cityA).value();
    auto nodeIdB = adjList.getNodeId(cityB).value();

    DijsktraShortestPath dijkstra(adjList, nodeIdA, nodeIdB);
    auto [minDistance, paths] = dijkstra.computePath();
    if (!paths.empty()) {
        std::cout << "Distance between " << std::quoted(cityA) << " and " << std::quoted(cityB) << " is " << minDistance << "km\n";
        std::cout << "The paths to follow are: \n";
        for (auto iter = paths.begin(); iter != paths.end(); std::advance(iter, 1)) {
            auto nextCityId = std::next(iter) != paths.end() ? std::next(iter)->nodeId : nodeIdB;
            auto [currCityId, distance] = *iter;
            std::cout << "\t" << adjList.getNodeName(currCityId).value()
                      << "   to   " 
                      << adjList.getNodeName(nextCityId).value() 
                      << " is " << distance << "\n";
        }
    } else {
        std::cout << "Unfortunately, there is no road between " << std::quoted(cityA) << " and " << std::quoted(cityB) << "\n";
    }

} catch (std::exception& e) {
    std::cerr << "[FATAL exception]: " << e.what() << "\n";
}
