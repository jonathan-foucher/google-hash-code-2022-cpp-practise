#ifndef GOOGLE_HASH_CODE_2022_C___LINKEDLIST_H
#define GOOGLE_HASH_CODE_2022_C___LINKEDLIST_H

#include <iostream>
#include <optional>

template<class L>
struct node {
    node<L> *next;
    L data;
};

template<class L>
class LinkedList {
public:
    node<L> *head;
    node<L> *last;
    int size = 0;

    LinkedList<L>() {
        head = nullptr;
        last = nullptr;
    }

    void add(L data) {
        if (!head) {
            head = new node<L>;
            head->data = data;
            head->next = nullptr;
            last = head;
        } else {
            if (last == head) {
                last = new node<L>;
                last->data = data;
                last->next = nullptr;
                head->next = last;
            } else {
                auto *insdata = new node<L>;
                insdata->data = data;
                insdata->next = nullptr;
                last->next = insdata;
                last = insdata;
            }
        }
        size++;
    }

    void remove(L &data) {
        if (&(this->head->data) == &data) {
            this->head = this->head->next;
            size--;
            if(size == 0) {
                this->last = nullptr;
            }
            return;
        }

        node<L> *curr = this->head;
        for (int i = 0; i < size - 1; ++i) {
            if (&(curr->next->data) == &data) {
                if (i == size - 2) {
                    this->last = curr;
                }
                curr->next = curr->next->next;
                size--;
                return;
            }
            curr = curr->next;
        }
    }

    void remove(int index) {
        if (index >= size || index < 0) {
            return;
        }

        if (index == 0) {
            this->head = this->head->next;
            size--;
            if(size == 0) {
                this->last = nullptr;
            }
            return;
        }

        node<L> *curr = this->head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }

        if (index == size - 1) {
            this->last = curr;
        }
        curr->next = curr->next->next;
        size--;
    }

    L *get(int index) {
        node<L> *curr = this->head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return &(curr->data);
    }

    L *operator[](int index) {
        return get(index);
    }

    template<typename F>
    std::optional<L> find(F condition) {
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            if (condition(curr->data)) {
                return {curr->data};
            }
            curr = curr->next;
        }
        return std::nullopt;
    }

    template<typename F>
    bool some(F condition) {
        if (find(condition).has_value()) {
            return true;
        }
        return false;
    }

    template<typename F>
    bool every(F condition) {
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            if (!condition(curr->data)) {
                return false;
            }
            curr = curr->next;
        }
        return true;
    }

    template<typename F>
    LinkedList<L> filter(F condition) {
        LinkedList<L> filteredList;
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            if (condition(curr->data)) {
                filteredList.add(curr->data);
            }
            curr = curr->next;
        }
        return filteredList;
    }

    template<typename F>
    void forEach(F function) {
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            function(curr->data);
            curr = curr->next;
        }
    }

    template<typename G, typename F>
    LinkedList<G> map(F function) {
        LinkedList<G> filteredList;
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            filteredList.add(function(curr->data));
            curr = curr->next;
        }
        return filteredList;
    }
};

#endif //GOOGLE_HASH_CODE_2022_C___LINKEDLIST_H
