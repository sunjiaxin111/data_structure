#include<stdio.h>

using namespace std;


// 在[low, high)中查找,返回<=elem的最大秩
int binary_search(int S[], int elem, int low, int high) {
    while (low < high) {
        int mid = low + ((high - low) >> 1);
        (elem < S[mid]) ? high = mid : low = mid + 1;
    }

    return low - 1;
}


int get_point_number(int S[], int a, int b, int size) {
    int low_index = binary_search(S, a, 0, size);
    int high_index = binary_search(S, b, low_index < 0 ? 0 : low_index, size);
    return high_index - low_index + (low_index >= 0 && S[low_index] == a ? 1 : 0);
}


void merge(int S[], int low, int high) {
    int mid = low + ((high - low) >> 1);
    int left = 0, right = mid + 1;

    int left_num = mid - low + 1;
    int temp_arr[left_num];
    for (int i = 0; i < left_num; i++) {
        temp_arr[i] = S[low + i];
    }

    while (left < left_num && right <= high) {
        if (temp_arr[left] <= S[right]) {
            S[low++] = temp_arr[left++];
        } else {
            S[low++] = S[right++];
        }
    }

    while (left < left_num) {
        S[low++] = temp_arr[left++];
    }
}


void merge_sort(int S[], int low, int high) {
    if (low < high) {
        int mid = low + ((high - low) >> 1);
        merge_sort(S, low, mid);
        merge_sort(S, mid + 1, high);
        merge(S, low, high);
    }
}


int main() {
    int size, query_num, a, b;
    scanf("%d%d", &size, &query_num);
    int S[size];
    int queries[query_num][2];
    for (int i = 0; i < size; i++) {
        scanf("%d", &(S[i]));
    }
    merge_sort(S, 0, size - 1);
    for (int i = 0; i < query_num; i++) {
        scanf("%d%d", &a, &b);
        queries[i][0] = a, queries[i][1] = b;
    }
    for (int i = 0; i < query_num; i++) {
        printf("%d\n", get_point_number(S, queries[i][0], queries[i][1], size));
    }
}