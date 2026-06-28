#include <functional>
#include <list>
#include <utility>
#include <vector>

template<typename K, typename V>
class HashMap {
        public:
                HashMap()
                        : bucket(16)
                        , m_size(0)
                {}

                void insert(K key, V value) {
                        std::hash<K> hasher;
                        size_t index = hasher(key) % bucket.size();
                        for(auto& [k, v] : bucket[index]) {
                                if(k == key) {
                                        v = value;
                                        return;
                                }
                        }
                        bucket[index].push_back({key, value});
                        m_size++;
                }

                V& operator[](const K& key) {
                        std::hash<K> hasher;
                        size_t index = hasher(key) % bucket.size();
                        for(auto& [k, v] : bucket[index]) {
                                if(key == k) return v;
                        }
                        bucket[index].push_back({key, V{}});
                        return bucket[index].back().second;
                }

                const V& operator[](const K& key) const {
                        std::hash<K> hasher;
                        size_t index = hasher(key) % bucket.size();
                        for(auto& [k, v] : bucket[index]) {
                                if(key == k) return v;
                        }
                        bucket[index].push_back({key, V{}});
                        return bucket[index].back().second;
                }

                void remove(const K& key) {
                        std::hash<K> hasher;
                        size_t index = hasher(key) % bucket.size();
                        for(auto it = bucket[index].begin(); it != bucket[index].end(); it++) {
                                if(it->first == key) {
                                        bucket[index].erase(it);
                                        m_size--;
                                        return;
                                }
                        }
                }

                size_t size() const {
                        return m_size;
                }

                bool empty() const {
                        return m_size == 0;
                }

        private:
                std::vector<std::list<std::pair<K, V>>> bucket;
                size_t m_size;
};
