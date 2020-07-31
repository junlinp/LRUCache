/**
 * Copyright (c) 2020 junlinp.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.*
 */

#ifndef LRU_CACHE_TYPE_RAII_HPP
#define LRU_CACHE_TYPE_RAII_HPP
#include <fstream>
#include <string>
#include <type_traits>

#include "cereal/archives/binary.hpp"
#include "cereal/cereal.hpp"
namespace LRUCache {

template <class T>
struct BasicTypeWrap {
  BasicTypeWrap() : value_() {}
  BasicTypeWrap(const T& value) : value_(value) {}
  BasicTypeWrap(T&& value) : value_(std::move(value)) {}

  template <class Archive>
  void serialize(Archive& ar) {
    ar(value_);
  }
  T value_;
};
/**
 * It will save to path when no one use the variable
 */
template <class T, class StoreValue = typename std::conditional<
                       std::is_scalar<T>::value, BasicTypeWrap<T>, T>::type>
class TypeRAII : public StoreValue {
 public:
  TypeRAII(const std::string& cache_path)
      : cache_path_(cache_path), StoreValue(){};
  TypeRAII(const std::string& cache_path, const T& init_value)
      : cache_path_(cache_path), StoreValue(init_value){};
  TypeRAII(const std::string& cache_path, T&& init_value)
      : cache_path_(cache_path), StoreValue(std::move(init_value)){};
  virtual ~TypeRAII() { Save(); }

  bool Load() {
    std::ifstream ifs(cache_path_, std::ios::binary);
    if (!ifs.is_open()) {
      return false;
    }
    {
      cereal::BinaryInputArchive archive(ifs);
      archive(*static_cast<StoreValue*>(this));
    }
    return true;
  };
  bool Save() {
    std::ofstream ofs(cache_path_, std::ios::binary);
    if (!ofs.is_open()) {
      return false;
    }
    {
      cereal::BinaryOutputArchive archive(ofs);
      archive(*static_cast<StoreValue*>(this));
    }
    return true;
  };

 private:
  std::string cache_path_;
};
}  // namespace LRUCache
#endif  // LRU_CACHE_TYPE_RAII_HPP