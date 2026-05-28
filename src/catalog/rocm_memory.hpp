#pragma once

#include "profcat/descriptor.hpp"

#include <array>

namespace profcat::rocm_memory {

inline constexpr std::array descriptors = {
    MetricDescriptor{
        .id           = 0x1201,
        .name         = "rocm.copy.h2d",
        .display_name = "Host-to-Device Copy",
        .description  = "Span per host-to-device memory copy. Payload: size, src/dst agent, SDMA engine id.",
        .track        = "GPU {agent_id} / SDMA",
        .kind         = Kind::Span,
        .unit         = Unit::Bytes,
        .source       = Source::RocprofilerSdk,
        .stage        = Stage::Interconnect,
        .scope        = Scope::Queue,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Low,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
    MetricDescriptor{
        .id           = 0x1202,
        .name         = "rocm.copy.d2h",
        .display_name = "Device-to-Host Copy",
        .description  = "Span per device-to-host memory copy. Inverse of H2D.",
        .track        = "GPU {agent_id} / SDMA",
        .kind         = Kind::Span,
        .unit         = Unit::Bytes,
        .source       = Source::RocprofilerSdk,
        .stage        = Stage::Interconnect,
        .scope        = Scope::Queue,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Low,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
    MetricDescriptor{
        .id           = 0x1203,
        .name         = "rocm.copy.d2d",
        .display_name = "Device-to-Device Copy",
        .description  = "Span per device-to-device copy (P2P over xGMI or PCIe). Payload identifies src/dst agent and link.",
        .track        = "GPU {agent_id} / SDMA",
        .kind         = Kind::Span,
        .unit         = Unit::Bytes,
        .source       = Source::RocprofilerSdk,
        .stage        = Stage::Interconnect,
        .scope        = Scope::Queue,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Low,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
};

} // namespace profcat::rocm_memory
