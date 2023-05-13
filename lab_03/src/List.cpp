#include <iostream>

template<class T>
class Node {

private:
    T value;
    Node<T> *next;
    Node<T> *prev;

public:
    Node(T value) {
        this->value = value;
        this->prev = nullptr;
        this->next = nullptr;
    }

    ~Node() {
        delete this;
    }

    void set_value (T value) {
        this->value = value;
    }

    T get_value () {
        return this->value;
    }

    void set_next(Node<T> *next) {
        this->next = next;
    }

    Node<T> *get_next() {
        return this->next;
    }

    void set_prev(Node<T> *prev) {
        this->prev = prev;
    }

    Node<T> *get_prev() {
        return this->prev;
    }
};

template<class T>
class List {
private:
    Node<T> *root;
public:
    List() {
        this->root = nullptr;
    }

    List(T value) {
        this->root = new Node<T>(value);
    }

    Node<T> *get_root() {
        return this->root;
    }

    void add_node(Node<T> *node) {
        Node<T> *last = this->root;
        if (last == nullptr) {
            this->root = node;
            return;
        }
        while (last->get_next() != nullptr)
            last = last->get_next();
        node->set_prev(last);
        last->set_next(node);
    }

    void add_node(T value) {
        Node<T> *last = this->root;
        if (last == nullptr) {
            this->root = new Node<T>(value);
            return;
        }
        while (last->get_next() != nullptr)
            last = last->get_next();
        Node<T> *node = new Node<T>(value);
        node->set_prev(last);
        last->set_next(node);
    }

    void DeleteLinkedList()
    {
        Node <T> *now = this->root, *prev = this->root;
        while (now != NULL)
        {
            prev = now;
            now = now->get_next();
            free(prev);
        }
    }
};

