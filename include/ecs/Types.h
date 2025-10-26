#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <memory>
#include <queue>
#include <set>
#include <typeinfo>
#include <unordered_map>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
