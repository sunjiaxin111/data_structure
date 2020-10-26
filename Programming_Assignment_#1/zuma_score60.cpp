#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

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

    for (int i = 0; i < insert_times; i++) {
        int idx = idxs[i];
        char c = insert_cs[i];
        int left_idx = idx - 1, right_idx = idx;
        while (left_idx >=0 && s[left_idx] == c) left_idx--;
        while (right_idx < s.size() && s[right_idx] == c) right_idx++;
        if (right_idx - left_idx >= 3) {
            while (left_idx >= 0 && right_idx < s.size() && s[left_idx] == s[right_idx]) {
                char temp_c = s[left_idx];
                bool flag = false;
                while (left_idx >=0 && s[left_idx] == temp_c) {
                    left_idx--;
                    flag = true;
                }
                while (right_idx < s.size() && s[right_idx] == temp_c) {
                    right_idx++;
                    flag = true;
                }
                if (!flag) break;
            }
            s.erase(left_idx + 1, right_idx - left_idx - 1);
        } else {
            s.insert(idx, 1, c);
        }
        cout << (s.size() == 0 ? "-" : s) << endl;
    }
}