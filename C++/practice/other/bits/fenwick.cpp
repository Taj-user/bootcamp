#include <iostream>
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

int main(void) {
        FenwickTree tree(8);
        tree.update(1, 3);
        tree.update(2, 2);
        tree.update(3, 1);
        tree.update(4, 5);
        tree.update(5, 4);
        tree.update(6, 2);
        tree.update(7, 3);
        tree.update(8, 1);
        std::cout << tree.query(3) << "\n";
        std::cout << tree.query(6) << "\n";
        tree.update(3, 2);
        std::cout << tree.query(3) << "\n";
        return 0;
}
