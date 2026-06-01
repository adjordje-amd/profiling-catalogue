# profiling-catalogue

A header-only, `constexpr` catalog of GPU/CPU profiler metrics.

## The idea

Profiler front-ends, probe layers, and UX tools all need to agree on *what
metrics exist* and *what each one means* before any data is collected. This
library is that single source of truth: every metric is a `constexpr`
`MetricDescriptor` carrying its identity (id, name, description, track) plus a
fixed set of classification dimensions:

- **Kind** - counter, gauge, event, span, sample, derived
- **Unit** - bytes, cycles, ns, %, W, C, ...
- **Source** - rocprofiler-sdk, amd-smi, perf_event, kfd, sampler, procfs, derived
- **Stage / Scope / Clock / Cost / Stability**
- **Capability** - hardware feature a metric depends on (PCIe, XGMI, NIC, ...),
  which lets a probe layer turn a static descriptor into a per-device
  Supported/Unsupported verdict.

The whole catalog is assembled at compile time from per-domain adapters
(`rocm_api`, `rocm_dispatch`, `rocm_memory`, `gpu_pmc`, `gpu_smi`,
`cpu_samples`, `proc_metrics`, `derived`) into one `constexpr` array.
`static_assert`s enforce that every metric has the required fields and that all
ids are unique - so a malformed or duplicated metric is a build error, not a
runtime surprise. It currently describes 68 metrics.

Because it is header-only and has no runtime dependencies, downstream tools
consume the catalog directly and pay zero cost beyond what they read.

## Requirements

- A C++20 compiler (`consteval`, `<ranges>`)
- CMake >= 3.20

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces the example CLI at `build/profcat-list`.

## Run the example

`profcat-list` prints the catalog as a table and exercises the public API
(iteration, filtering, `to_string` on the enums):

```sh
./build/profcat-list                 # list all metrics
./build/profcat-list --long          # include the full description column
./build/profcat-list --kind counter  # filter by kind
./build/profcat-list --stage gpu     # filter by pipeline stage
./build/profcat-list --grep xgmi     # substring match on name/description
./build/profcat-list --help          # all options
```

## Use as a library

The catalog is exposed as the CMake INTERFACE target `profcat::profcat`
(via `add_subdirectory` or `FetchContent`):

```cpp
#include "profcat/catalog.hpp"

for (auto const& d : profcat::catalog) {
    // d.name, d.kind, d.stage, d.requires_capability, ...
}
```
