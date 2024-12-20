#pragma once

#include <string>
#include <vector>

class Node {
private:
    inline static int nextId = 0;

public:
    std::string name;
    const int id;
    Node *parent;
    std::vector<Node *> children;

    Node() : id(nextId++), parent(nullptr) {
    }
};
