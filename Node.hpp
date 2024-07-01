#ifndef Node_hpp
#define Node_hpp
#include "User.hpp"
using namespace std;

template <class nodeEntry>
struct Node {
    // Data fields
    nodeEntry data;
    Node<nodeEntry> *next;
    
    // Constructors
    Node();
    Node(const nodeEntry &userData);
};

// Definitions

// Constructors
template <class nodeEntry>
Node<nodeEntry>::Node() {
    next = nullptr;
}

template <class nodeEntry>
Node<nodeEntry>::Node(const nodeEntry &userData) : data(userData), next(nullptr) {}
#endif /* Node_hpp */
