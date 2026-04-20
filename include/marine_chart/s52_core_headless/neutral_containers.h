#pragma once

#include <map>
#include <optional>
#include <unordered_map>
#include <vector>

namespace marine_chart::s52_core_headless {

template <typename T>
using NeutralVector = std::vector<T>;

template <typename Key, typename Value, typename Compare = std::less<Key>>
using NeutralMap = std::map<Key, Value, Compare>;

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
using NeutralHashMap = std::unordered_map<Key, Value, Hash, KeyEqual>;

template <typename T>
using NeutralOptional = std::optional<T>;

}  // namespace marine_chart::s52_core_headless
