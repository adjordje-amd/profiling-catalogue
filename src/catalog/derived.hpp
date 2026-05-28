#pragma once

#include "profcat/descriptor.hpp"

#include <array>

namespace profcat::derived {

inline constexpr std::array descriptors = {
    MetricDescriptor{
        .id           = 0x6001,
        .name         = "rocm.gpu.derived.valu_utilization",
        .display_name = "VALU Utilization",
        .description  = "Ratio VALU_INSTS / (VALU_INSTS + SALU_INSTS). Indicates how vector-dense a kernel runs.",
        .track        = "GPU {agent_id} / Derived",
        .kind         = Kind::Derived,
        .unit         = Unit::Ratio,
        .source       = Source::Derived,
        .stage        = Stage::Gpu,
        .scope        = Scope::Dispatch,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Free,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
    MetricDescriptor{
        .id           = 0x6002,
        .name         = "rocm.gpu.derived.l2_hit_rate",
        .display_name = "L2 Cache Hit Rate",
        .description  = "TCC_HIT / (TCC_HIT + TCC_MISS). Useful sanity check before optimizing memory layouts.",
        .track        = "GPU {agent_id} / Derived",
        .kind         = Kind::Derived,
        .unit         = Unit::Ratio,
        .source       = Source::Derived,
        .stage        = Stage::Gpu,
        .scope        = Scope::Dispatch,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Free,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
    MetricDescriptor{
        .id           = 0x6003,
        .name         = "rocm.gpu.derived.sq_utilization",
        .display_name = "SQ Utilization",
        .description  = "SQ_BUSY_CYCLES / GRBM_GUI_ACTIVE. Tells how often the shader sequencer had work to issue.",
        .track        = "GPU {agent_id} / Derived",
        .kind         = Kind::Derived,
        .unit         = Unit::Ratio,
        .source       = Source::Derived,
        .stage        = Stage::Gpu,
        .scope        = Scope::Dispatch,
        .clock        = Clock::GpuClock,
        .cost         = Cost::Free,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
    MetricDescriptor{
        .id           = 0x6004,
        .name         = "cpu.derived.ipc",
        .display_name = "CPU IPC",
        .description  = "Instructions per cycle = INSTRUCTIONS / CYCLES.",
        .track        = "Thread {tid} / Derived",
        .kind         = Kind::Derived,
        .unit         = Unit::Ratio,
        .source       = Source::Derived,
        .stage        = Stage::Cpu,
        .scope        = Scope::Thread,
        .clock        = Clock::CpuTsc,
        .cost         = Cost::Free,
        .stability    = Stability::Stable,
        .needs_root   = false,
        .multiplexed  = false,
    },
};

} // namespace profcat::derived
