#include <vector>

struct FenwickTree {
        int n;
        std::vector<int> tree;

        FenwickTree(int n);
        void update(int i, int delta);
        int query(int i);
};
