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
};

} // namespace profcat
