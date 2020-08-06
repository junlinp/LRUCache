/**
 * Copyright (c) 2020 junlinp.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.*
 */

#ifndef LRU_CACHE_LRU_MANAGER_HPP
#define LRU_CACHE_LRU_MANAGER_HPP
#include "type_RAII.hpp"
namespace LRUCache {

template <class Key, class Value>
class LRUManager {
  using WrapValue = TypeRAII<Value>;
  using Value_Ptr = std::shared_ptr<Value>;
  using WrapValue_Ptr = std::shared_ptr<Value>;

 public:
  LRUManager(const std::string cache_directory,
             const int max_cache_capacity = 32);

  Value_Ptr get(const Key& key) {
    // key not exist
    if (map_.find(key) == map_.end()) {
      auto ptr = GenerateInitValuePtr(key);
      InsertToLink(ptr);
      map_[key] = ptr;
      return ptr;
    } else {
      // key exist
      auto& weak_ptr = map_[key];
      if (weak_ptr.expired()) {
        // key not in momery
        auto ptr = LoadKeyFromFile(key);
        InsertToLink(ptr);
        map_[key] = ptr;
        return ptr;
      } else {
      }
    }
  }

 private:
  WrapValue_Ptr GenerateInitValuePtr(const Key& key);
  WrapValue_Ptr LoadKeyFromFile(key);
  void InsertToLink(WrapValue_Ptr& value);

  std::map<Key, std::weak_ptr<WrapValue_Ptr>> map_;
  std::deque<WrapValue_Ptr> link_;
};
}  // namespace LRUCache
#endif