#pragma once

#include "enums.hpp"

#include <cstdint>
#include <string_view>

namespace profcat {

struct MetricDescriptor {
    std::uint32_t    id;
    std::string_view name;
    std::string_view display_name;
    std::string_view description;
    std::string_view track;

    Kind             kind;
    Unit             unit;
    Source           source;
    Stage            stage;
    Scope            scope;
    Clock            clock;
    Cost             cost;
    Stability        stability;

    bool             needs_root;
    bool             multiplexed;

    // Hint to UX layers: include this metric in the default selection when
    // a user opens a device for the first time. Keeps the starter preset
    // low-cost, broadly useful, and Stable. Downstream tools may still
    // intersect with their own supported-id list before applying.
    bool             default_enabled = false;
};

} // namespace profcat
