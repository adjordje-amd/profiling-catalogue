#pragma once

#include <cstdint>

namespace profcat {

enum class Kind : std::uint8_t {
    Counter,
    Gauge,
    Event,
    Span,
    Sample,
    Derived
};

enum class Unit : std::uint8_t {
    Count,
    Bytes,
    Cycles,
    Nanoseconds,
    Ratio,
    Percent,
    Hertz,
    Watt,
    Celsius,
    Millivolt,
    None
};

enum class Source : std::uint8_t {
    RocprofilerSdk,
    AmdSmi,
    PerfEvent,
    KfdEvents,
    Sampler,
    ProcFs,
    Derived
};

enum class Stage : std::uint8_t {
    Cpu,
    Memory,
    Interconnect,
    Submission,
    Gpu,
    DeviceTelemetry,
    ApuFabric
};

enum class Scope : std::uint8_t {
    System,
    Process,
    Thread,
    Agent,
    Queue,
    Dispatch,
    Region
};

enum class Clock : std::uint8_t {
    CpuTsc,
    GpuClock,
    Monotonic,
    Wall
};

enum class Cost : std::uint8_t {
    Free,
    Low,
    Medium,
    High
};

enum class Stability : std::uint8_t {
    Stable,
    Experimental,
    Deprecated
};

constexpr const char* to_string(Kind k) noexcept {
    switch (k) {
        case Kind::Counter: return "counter";
        case Kind::Gauge:   return "gauge";
        case Kind::Event:   return "event";
        case Kind::Span:    return "span";
        case Kind::Sample:  return "sample";
        case Kind::Derived: return "derived";
    }
    return "?";
}

constexpr const char* to_string(Unit u) noexcept {
    switch (u) {
        case Unit::Count:       return "count";
        case Unit::Bytes:       return "bytes";
        case Unit::Cycles:      return "cycles";
        case Unit::Nanoseconds: return "ns";
        case Unit::Ratio:       return "ratio";
        case Unit::Percent:     return "%";
        case Unit::Hertz:       return "Hz";
        case Unit::Watt:        return "W";
        case Unit::Celsius:     return "C";
        case Unit::Millivolt:   return "mV";
        case Unit::None:        return "-";
    }
    return "?";
}

constexpr const char* to_string(Source s) noexcept {
    switch (s) {
        case Source::RocprofilerSdk: return "rocprofiler-sdk";
        case Source::AmdSmi:         return "amd-smi";
        case Source::PerfEvent:      return "perf_event";
        case Source::KfdEvents:      return "kfd";
        case Source::Sampler:        return "sampler";
        case Source::ProcFs:         return "procfs";
        case Source::Derived:        return "derived";
    }
    return "?";
}

constexpr const char* to_string(Stage s) noexcept {
    switch (s) {
        case Stage::Cpu:             return "cpu";
        case Stage::Memory:          return "memory";
        case Stage::Interconnect:    return "interconnect";
        case Stage::Submission:      return "submission";
        case Stage::Gpu:             return "gpu";
        case Stage::DeviceTelemetry: return "device-telemetry";
        case Stage::ApuFabric:       return "apu-fabric";
    }
    return "?";
}

} // namespace profcat
