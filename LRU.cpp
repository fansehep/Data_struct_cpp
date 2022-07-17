#include <list>
#include <iostream>
#include <sys/time.h>
#include <string>
#include <map>
#include <chrono>
#include <unordered_map>

template <typename key, typename value>
class LRU_Cache {
  public:
    LRU_Cache(int size) : size_(size) {}
    auto Get(key k) -> key { 
      auto ReturnIterator = map_.find(k);
      if (ReturnIterator == map_.end()) {
        return value();
      }
      list_.erase(map_[k]);
      list_.push_front((*map_[k]));
      map_[k] = list_.begin();
      return (*list_.begin());
    }
    auto Put(key k, value v) -> void {
      auto ReturnIterator = map_.find(k);
      if (ReturnIterator != map_.end()) [[unlikely]] {
        list_.erase(map_[k]);
        list_.push_front(v);
        map_[k] = list_.begin();
      } else {
        if (list_.size() >= size_) [[unlikely]] {
          auto lastiterator = list_.back();
          map_.erase(lastiterator);
          list_.pop_back();
          list_.push_front(v);
          map_.insert({k, list_.begin()});
        } else {
          list_.push_front(v);
          map_.insert({k, list_.begin()});
        }
      }
    }
  private:
    std::list<value> list_;
    std::unordered_map<key, typename std::list<value>::iterator> map_;
    int size_;
};



void LRU_Test() {
  LRU_Cache<std::string, std::string> t_cache(100000);
  t_cache.Put("123", "123");
  t_cache.Put("3123", "123");
  std::string t_string = "t_Ad\n";
  t_string.reserve(100);
  struct timeval t_timeval{};
  gettimeofday(&t_timeval, nullptr);
  auto t_now = t_timeval.tv_sec * 1000000L +
               t_timeval.tv_usec;
  printf("insert test start! : %ld\n", t_now);
  for (auto i = 0; i < 50000; i++) {
    t_string += i;
    t_cache.Put(t_string, t_string);
  }
  gettimeofday(&t_timeval, nullptr);
  auto t_nowdate = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("end! : %ld\n", t_now);
  printf("cost : %ld\n", t_nowdate - t_now);
  gettimeofday(&t_timeval, nullptr);
  t_now = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("get test start!");
  t_string = "t_Ad\n";
  for (auto i = 0; i < 50000; i++) {
    t_string += i;
    t_cache.Get(t_string);
  }
  gettimeofday(&t_timeval, nullptr);
  t_nowdate = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("get test end!\ncost : %ld\n", t_nowdate - t_now);
}

void MAP_Test() {
  std::unordered_map<std::string, std::string> t_cache;
  std::string t_string = "t_Ad\n";
  t_string.reserve(100);
  struct timeval t_timeval{};
  gettimeofday(&t_timeval, nullptr);
  auto t_now = t_timeval.tv_sec * 1000000L +
               t_timeval.tv_usec;
  printf("insert start! : %ld\n", t_now);
  for (auto i = 0; i < 50000; i++) {
    t_string += i;
    t_cache.insert({t_string, t_string});
  }
  gettimeofday(&t_timeval, nullptr);
  auto t_nowdate = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("end! : %ld\n", t_now);
  printf("cost : %ld\n", t_nowdate - t_now);
  gettimeofday(&t_timeval, nullptr);
  t_now = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("get test start!\n");
  t_string = "t_Ad\n";
  for (auto i = 0; i < 50000; i++) {
    t_string += i;
    auto iter = t_cache[t_string];
  }
  gettimeofday(&t_timeval, nullptr);
  t_nowdate = t_timeval.tv_sec * 1000000L +
          t_timeval.tv_usec;
  printf("get test end!\ncode : %ld\n", t_nowdate - t_now);
}

auto main() -> int {
  LRU_Test();
  printf("\n");
  MAP_Test();
  return 0;
}
