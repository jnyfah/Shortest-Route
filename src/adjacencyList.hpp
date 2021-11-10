/*
* Shortest Route
*
* Author: Chukwu Jennifer
* Email: Jnyfaah@gmail.com
* Project Date: Nov, 2021
*/


#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP


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


#include "../utils/json.hpp"

nlohmann::json jsonData;





/*
*
* Class csvReader 
* reads csv file by line and converts it to a 2D table
* input: CSV file
* returns a 2D vector with csv data
*
*/


class CSVReader {
public:
    CSVReader(std::string inputFileName) {
        using namespace std::string_literals;
        std::ifstream file(inputFileName);
        std::string line;

        if (!file.is_open()) {
            throw std::invalid_argument("Unknown Input given; The filename " + inputFileName + " does not exist");
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






/*
*
* Class AdjacencyList 
* implements Ajacency List by connecting appropriate nodes
* input: data
* returns a 2D vector with data
*
*/

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




/*
*
* Class MileageChartCSVToAdjacencyListCreator
* converts 2D table to Adjacency List
* input: 2D vector
* returns Adjacency List
*
*/

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



#endif