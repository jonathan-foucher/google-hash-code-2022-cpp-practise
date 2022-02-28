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

    void remove(L *data) {
        if (&(this->head->data) == data) {
            this->head = this->head->next;
            size--;
            if (size == 0) {
                this->last = nullptr;
            }
            return;
        }

        node<L> *curr = this->head;
        for (int i = 0; i < size - 1; ++i) {
            if (&(curr->next->data) == data) {
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
            if (size == 0) {
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

    L *pop(int index) {
        if (index >= size || index < 0) {
            return nullptr;
        }

        if (index == 0) {
            L *poppedElement = &(this->head->data);
            this->head = this->head->next;
            size--;
            if (size == 0) {
                this->last = nullptr;
            }
            return poppedElement;
        }

        node<L> *curr = this->head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }

        if (index == size - 1) {
            this->last = curr;
        }
        L *poppedElement = &(curr->next->data);
        curr->next = curr->next->next;
        size--;
        return poppedElement;
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
    std::optional<L*> find(F condition) {
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            if (condition(curr->data)) {
                return {&curr->data};
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

    template<typename F>
    void forEachAddr(F function) {
        node<L> *curr = this->head;
        for (int i = 0; i < size; ++i) {
            function(&curr->data);
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

    template<typename F>
    LinkedList<L> sort(F sortCondition) {
        if (size <= 1) {
            return *this;
        }

        int middle = size / 2;
        LinkedList<L> left;
        LinkedList<L> right;
        node<L> *curr = this->head;

        for (int i = 0; i < middle; ++i) {
            left.add(curr->data);
            curr = curr->next;
        }

        for (int i = middle; i < size; ++i) {
            right.add(curr->data);
            curr = curr->next;
        }

        LinkedList<L> leftSorted = left.sort(sortCondition);
        LinkedList<L> rightSorted = right.sort(sortCondition);

        return merge(sortCondition, &leftSorted, &rightSorted);
    }

    LinkedList<L> makeCopy() {
        LinkedList<L> copy;
        node<L> *curr = this->head;
        for (int i = 0; i < size; i++) {
            copy.add(curr->data);
            curr = curr->next;
        }
        return copy;
    }

private:
    template<typename F>
    LinkedList<L> merge(F sortCondition, LinkedList<L> *left, LinkedList<L> *right) {
        LinkedList<L> mergedList;
        int leftIndex = 0;
        int rightIndex = 0;
        node<L> *leftCurr = left->head;
        node<L> *rightCurr = right->head;

        while (leftIndex < left->size && rightIndex < right->size) {
            if (sortCondition(leftCurr->data, rightCurr->data)) {
                mergedList.add(leftCurr->data);
                leftCurr = leftCurr->next;
                leftIndex++;
            } else {
                mergedList.add(rightCurr->data);
                rightCurr = rightCurr->next;
                rightIndex++;
            }
        }

        while (leftIndex < left->size) {
            mergedList.add(leftCurr->data);
            leftCurr = leftCurr->next;
            leftIndex++;
        }

        while (rightIndex < right->size) {
            mergedList.add(rightCurr->data);
            rightCurr = rightCurr->next;
            rightIndex++;
        }

        return mergedList;
    }
};

#endif //GOOGLE_HASH_CODE_2022_C___LINKEDLIST_H
