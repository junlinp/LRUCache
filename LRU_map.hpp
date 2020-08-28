/**
 * Copyright (c) 2020 junlinp.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.*
 */

#ifndef LRU_MAP_HPP
#define LRU_MAP_HPP
#include <set>
#include <string>

#include "LRU_manager.hpp"
#include "type_RAII.hpp"

namespace LRUCache {

template <class Key, class Value>
class LRUMap {
 public:
  LRUMap(const std::string cache_dir = ".")
      : key_tracker_(), manager_(cache_dir) {}

  using value_type = TypeRAII<Value>;

 private:
  std::set<Key> key_tracker_;
  LRUManager<Key, Value> manager_;
};

}  // namespace LRUCache
#endif