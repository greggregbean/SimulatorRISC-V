#ifndef CACHE_H_
#define CACHE_H_

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <functional>

#include "constants.hpp"

template <typename T, typename KeyT = uint64_t>
class Cache {
private:
    int min_counter = 0;
    std::unordered_map<KeyT, std::list<T>> counter_list;

    int max_size;
    int curr_size = 0;
    
    std::list<T> cache;

    using it_list = typename std::list<T>::iterator; 
    struct hash_elem_t {
        it_list cache_iter;
        it_list counter_iter;
        int     counter;
        hash_elem_t(it_list cache_it, it_list counter_it): 
                                 cache_iter(cache_it),
                                 counter_iter(counter_it),
                                 counter(1){}
        hash_elem_t():           counter(0){}
    };
    std::unordered_map<KeyT, hash_elem_t> hash;

public:
    Cache(int m_size = DEFAULT_CACHE_SIZE): max_size(m_size) {}

private:
    bool is_cache_full() const {
        return curr_size == max_size;
    }

    void update_elem_place(KeyT key) {
        assert(!cache.empty() && "cache us empty");
        assert(hash.find(key) != hash.end() && "hash has't this key");

        auto& hash_counter = hash[key].counter;
        counter_list[hash_counter].erase(hash[key].counter_iter);
        hash_counter++;
        counter_list[hash_counter].push_front(key);
        hash[key].counter_iter = counter_list[hash_counter].begin();

        if(counter_list[min_counter].empty()) {
            min_counter++;
        }
    }

public:
    T lookup_update(T list_elem) {
        assert(max_size >= 0 && "max_size is neg");
        assert(curr_size >= 0 && "curr_size is neg");

        KeyT key = list_elem; //in this hash: key = value
        auto hit = hash.find(key);
        if(hit == hash.end()) {
            if(is_cache_full()) {
                KeyT erase_key = counter_list[min_counter].back();
                cache.erase(hash[erase_key].cache_iter);
                hash.erase(erase_key);
                counter_list[min_counter].pop_back();
            }
            else {
                curr_size++;
            }

            min_counter = 1;
            counter_list[min_counter].push_front(key);
            cache.push_front(key);
            hash_elem_t hash_elem(cache.begin(), counter_list[min_counter].begin());
            hash[key] = hash_elem;
        }
        else {
            update_elem_place(key);
            return key;
        }
        assert(max_size >= 0 && "max_size is neg");
        assert(curr_size >= 0 && "curr_size is neg");

        return 0;
    }

};

#endif // #define CACHE_H_