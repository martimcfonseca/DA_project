#ifndef DA_PROJECT_PARSER_H
#define DA_PROJECT_PARSER_H

#include <string>
#include "Input.h"
#include "Graph.h"

using namespace std;

class Node {
public:
    int id;
    enum class Type { SOURCE, SINK, SUBMISSION, REVIEWER } type;
    int primary;
    int secondary;

    bool operator==(const Node& o) const {
        return id == o.id && type == o.type;
    }

    void printNode() const{
        std::cout << id << ' ';
        switch (type) {
            case Type::SOURCE: std::cout << "SOURCE";break;
            case Type::SINK: std::cout << "SINK";break;
            case Type::SUBMISSION: std::cout << "SUBMISSION";break;
            case Type::REVIEWER: std::cout << "REVIEWER";break;
        }
        cout << ' ' << primary << ' ' << secondary <<std::endl;
    }
};

Input       parseFile(const std::string& filename);
Graph<Node> makeGraph(const Input& data);

#endif