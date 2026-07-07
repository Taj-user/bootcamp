#include <vector>

struct FenwickTree {
        int n;
        std::vector<int> tree;

        FenwickTree(int n) : n(n), tree(n + 1) {}

        void update(int i, int delta) {
                while(i < n) {
                        tree[i] += delta;
                        i += (i & -i);
                }
        }

        int query(int i) {
                int sum = 0;
                while(i != 0) {
                        sum += tree[i];
                        i -= (i & -i);
                }
                return sum;
        }
};
