#pragma once
#include <iostream>

template <typename T>
class Node
{
private:
    int idx;
    T info;

public:
    Node(int _idx, const T& _info) : idx{ _idx }, info{ _info } {}
    Node() : idx(), info() {}

    T getInfo() const { return info; };
    int getIdx() const { return idx; };

    void setInfo(T _info) { info = _info; };
    void setIdx(int _idx) { idx = _idx; };
    
    template <typename U>
    friend bool operator==(const Node<U>& left, const Node<U>& right);

    template <typename U>
    friend bool operator<(const Node<U>& left, const Node<U>& right);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Node<U>& n);

    Node<T>& operator=(const Node<T>& other) {
        if (this != &other) 
        {
            idx = other.idx;
            info = other.info;
        }
        return *this;
    }
};

template <typename U>
bool operator==(const Node<U>& left, const Node<U>& right) {
    return (left.idx == right.idx) && (left.info == right.info);
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Node<U>& n)
{
    os << "Node: [ " << n.idx << " ] with info " << "{ " << n.info << " }";
    return os;
}

template <typename U>
bool operator<(const Node<U>& left, const Node<U>& right) {
    return (left.idx < right.idx);
}
