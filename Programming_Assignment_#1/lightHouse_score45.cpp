#include <stdio.h>

template <typename T>
class ListNode {
public:
    // 成员
    T data;
    ListNode<T>* pred;
    ListNode<T>* succ;
    // 构造函数
    ListNode<T>() {};
    ListNode<T>(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL) : data(e), pred(p), succ(s) {};
    // 操作接口
    ListNode<T>* insertAsPred(T const& e) {
        ListNode<T>* t = new ListNode<T>(e, pred, this);
        pred->succ = t; pred = t;
        return t;
    };
    ListNode<T>* insertAsSucc(T const& e) {
        ListNode<T>* t = new ListNode<T>(e, this, succ);
        succ->pred = t; succ = t;
        return t;
    };
};

template <typename T>
class List {
private:
    int size_;
    long inverse_cnt_;
    ListNode<T>* header;
    ListNode<T>* trailer;
public:
    List<T>() {
        size_ = 0;
        inverse_cnt_ = 0;
        header = new ListNode<T>();
        trailer = new ListNode<T>();
    };
    ListNode<T>* insertAsFirst(T const& e) {
        size_++;
        ListNode<T>* t = new ListNode<T>(e, header, trailer);
        header->succ = t; trailer->pred = t;
        return t;
    };
    ListNode<T>* insertBefore(ListNode<T>* p, T const& e) {
        size_++;
        return p->insertAsPred(e);
    };
    ListNode<T>* insertAfter(ListNode<T>* p, T const& e) {
        size_++;
        return p->insertAsSucc(e);
    };
    template <typename Compare>
    ListNode<T>* searchBefore(ListNode<T>* p, T const& e, Compare comp) { // 从p开始往前找到一个最后一个>e的节点
        while (p != header && comp(p->data, e)) {
            inverse_cnt_++;
            p = p->pred;
        }
        return p;
    };
    template <typename Compare>
    void insertSort(Compare comp) {
        inverse_cnt_ = 0;
        ListNode<T>* p = header->succ;
        while (p != trailer) {
            ListNode<T>* next_p = p->succ;
            ListNode<T>* insert_p = searchBefore(p->pred, p->data, comp);
            if (insert_p != p->pred) {
                // remove p
                next_p->pred = p->pred;
                p->pred->succ = next_p;
                // insert p
                p->succ = insert_p->succ;
                p->pred = insert_p;
                insert_p->succ->pred = p;
                insert_p->succ = p;
            }
            p = next_p;
        }
    };
    long get_inverse_cnt() {
        return inverse_cnt_;
    };
};

class Coordinate {
public:
    int x_;
    int y_;
    Coordinate() {};
    Coordinate(int x, int y) : x_(x), y_(y) {};
};

bool greaterX(const Coordinate& A, const Coordinate& B) {
    return A.x_ > B.x_;
}

bool greaterY(const Coordinate& A, const Coordinate& B) {
    return A.y_ > B.y_;
}

int main() {
    long N;
    scanf("%d", &N);
    int x, y;
    List<Coordinate>* list = new List<Coordinate>();
    ListNode<Coordinate>* p;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &x, &y);
        if (i == 0) {
            p = list->insertAsFirst(Coordinate(x, y));
        } else {
            p = list->insertAfter(p, Coordinate(x, y));
        }
    }

    list->insertSort(greaterX);
    list->insertSort(greaterY);
    long total_cnt = N * (N - 1) / 2;
    printf("%d", (total_cnt - list->get_inverse_cnt()));
}