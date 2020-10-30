#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

#define MAX_LEN 200000000
#define UP 100000000

char res[MAX_LEN];
int idx = 0;

template <typename T>
struct ListNode { //列表节点模板类（以双向链表形式实现）
// 成员
   T data; ListNode<T>* pred; ListNode<T>* succ; //数值、前驱、后继
// 构造函数
   ListNode() {} //针对header和trailer的构造
   ListNode ( T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL )
      : data ( e ), pred ( p ), succ ( s ) {} //默认构造器
// 操作接口
   ListNode<T>* insertAsPred ( T const& e ); //紧靠当前节点之前插入新节点
   ListNode<T>* insertAsSucc ( T const& e ); //紧随当前节点之后插入新节点
};

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred( T const& e ) {
    ListNode<T>* node = new ListNode<T>(e, pred, this);
    pred->succ = node; pred = node;
    return node;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc( T const& e ) {
    ListNode<T>* node = new ListNode<T>(e, this, succ);
    succ->pred = node; succ=node;
    return node;
}

template <typename T>
class List {
private:
    int size_;
    ListNode<T>* header;
    ListNode<T>* trailer;
    void init();
public:
    List() { init(); }
    int size() const { return size_; }
    ListNode<T>* insertBefore(ListNode<T>* p, T const& e);
    void zuma(int idx, T const& e);
    ListNode<T>* index(int r);
    ListNode<T>* remove(ListNode<T>* p);
    void show();
};

template <typename T>
void List<T>::init() {
    header = new ListNode<T>();
    trailer = new ListNode<T>();
    header->succ = trailer;
    trailer->pred = header;
    size_ = 0;
}

template <typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T>* p, T const& e) {
    size_++;
    return p->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::index(int r) {
    ListNode<T>* res = header;
    while (0 < r--) {
        res = res->succ;
    }

    return res;
}

template <typename T>
ListNode<T>* List<T>::remove(ListNode<T>* p) {
    ListNode<T>* res = p->succ;
    p->pred->succ = res;
    res->pred = p->pred;
    delete p;
    size_--;
    
    return res;
}


template <typename T>
void List<T>::zuma(int idx, T const& e) {
    ListNode<T>* t = insertBefore(index(idx + 1), e);
    while (t != trailer) {
        int cnt = 1;
        T d = t->data;
        // 往右遍历
        ListNode<T>* rt = t;
        while (rt->succ->data == d) {
            rt = rt->succ;
            cnt++;
        }
        // 往左遍历
        while (t->pred->data == d) {
            t = t->pred;
            cnt++;
        }
        if (cnt >= 3) {
            while (0 < cnt--) {
                t = remove(t);
            }
        } else {
            break;
        }
    }
}

template <typename T>
void List<T>::show() {
    if (size_ == 0) {
        res[idx++] = '-';
        res[idx++] = '\n';
    } else {
        ListNode<T>* t = header->succ;
        while (t != trailer) {
            res[idx++] = t->data;
            t = t->succ;
        }
        res[idx++] = '\n';
    }

    if (idx >= UP) {
        res[idx++] = '\0';
        printf("%s", res);
        idx = 0;
    }
}


int main() {
    string s;
    getline(cin, s); // 遇到换行时终止输入,行中的空格也会被读入
    int insert_times;
    scanf("%d", &insert_times);

    int idxs[insert_times];
    char insert_cs[insert_times];

    for (int i = 0; i < insert_times; i++) {
        scanf("%d %c", &(idxs[i]), &(insert_cs[i]));
    }

    List<char>* lc = new List<char>();
    for (int i = 0; i < s.length(); i++) {
        lc->insertBefore(lc->index(lc->size() + 1), s[i]);
    }

    for (int i = 0; i < insert_times; i++) {
        lc->zuma(idxs[i], insert_cs[i]);
        lc->show();
    }
    res[idx++] = '\0';
    printf("%s", res);
}