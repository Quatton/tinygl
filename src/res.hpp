#pragma once

#include <map>

template <class T> class Res {

public:
  unsigned int current_id = 0;

  unsigned int add(T item) {
    items[current_id] = item;
    return current_id++;
  }

  T get(unsigned int id) { return items[id]; }

  void remove(unsigned int id) { items.erase(id); }

  void clear() { items.clear(); }

  std::map<unsigned int, T> items;
};