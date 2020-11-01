#include <stdio.h>
typedef long long ll;
#define MAX_SIZE 4000000

class Coordinate {
public:
    ll x_;
    ll y_;
    Coordinate() {};
    Coordinate(ll x, ll y) : x_(x), y_(y) {};
};
Coordinate S[MAX_SIZE];
Coordinate temp_arr[MAX_SIZE];

template <typename Compare>
void merge(Coordinate S[], int low, int high, Compare comp, ll& inverse_cnt) {
    int mid = low + ((high - low) >> 1);
    int left = 0, right = mid + 1;

    int left_num = mid - low + 1;
    for (int i = 0; i < left_num; i++) {
        temp_arr[i] = S[low + i];
    }

    while (left < left_num && right <= high) {
        if (comp(S[right], temp_arr[left])) {
            S[low++] = temp_arr[left++];
        } else {
            S[low++] = S[right++];
            inverse_cnt += left_num - left;
        }
    }

    while (left < left_num) {
        S[low++] = temp_arr[left++];
    }
}

template <typename Compare>
void merge_sort(Coordinate S[], int low, int high, Compare comp, ll& inverse_cnt) {
    if (low < high) {
        int mid = low + ((high - low) >> 1);
        merge_sort(S, low, mid, comp, inverse_cnt);
        merge_sort(S, mid + 1, high, comp, inverse_cnt);
        merge(S, low, high, comp, inverse_cnt);
    }
}


bool greaterX(const Coordinate& A, const Coordinate& B) {
    return A.x_ > B.x_;
}

bool greaterY(const Coordinate& A, const Coordinate& B) {
    return A.y_ > B.y_;
}

int main() {
    int N;
    scanf("%d", &N);
    ll x, y;

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &x, &y);
        S[i] = Coordinate(x, y);
    }

    ll inverse_cnt;
    merge_sort(S, 0, N - 1, greaterX, inverse_cnt);
    inverse_cnt = 0;
    merge_sort(S, 0, N - 1, greaterY, inverse_cnt);

    ll total_cnt = (long long)N * ((long long)N - 1) / 2;
    printf("%lld", (total_cnt - inverse_cnt));
}