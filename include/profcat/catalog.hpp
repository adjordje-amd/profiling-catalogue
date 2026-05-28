#pragma once

#include "descriptor.hpp"

#include "../../src/catalog/cpu_samples.hpp"
#include "../../src/catalog/derived.hpp"
#include "../../src/catalog/gpu_pmc.hpp"
#include "../../src/catalog/gpu_smi.hpp"
#include "../../src/catalog/proc_metrics.hpp"
#include "../../src/catalog/rocm_api.hpp"
#include "../../src/catalog/rocm_dispatch.hpp"
#include "../../src/catalog/rocm_memory.hpp"

#include <algorithm>
#include <array>
#include <cstddef>

namespace profcat {

consteval std::size_t total_count() {
    return rocm_api::descriptors.size()
         + rocm_dispatch::descriptors.size()
         + rocm_memory::descriptors.size()
         + gpu_pmc::descriptors.size()
         + gpu_smi::descriptors.size()
         + cpu_samples::descriptors.size()
         + proc_metrics::descriptors.size()
         + derived::descriptors.size();
}

consteval auto build_catalog() {
    std::array<MetricDescriptor, total_count()> out{};
    std::size_t i = 0;
    auto append = [&](auto const& src) {
        for (auto const& d : src) out[i++] = d;
    };
    append(rocm_api::descriptors);
    append(rocm_dispatch::descriptors);
    append(rocm_memory::descriptors);
    append(gpu_pmc::descriptors);
    append(gpu_smi::descriptors);
    append(cpu_samples::descriptors);
    append(proc_metrics::descriptors);
    append(derived::descriptors);
    return out;
}

inline constexpr auto catalog = build_catalog();

consteval bool all_have_required_fields() {
    return std::ranges::all_of(catalog, [](MetricDescriptor const& d) {
        return !d.name.empty()
            && !d.description.empty()
            && !d.track.empty();
    });
}

consteval bool all_ids_unique() {
    std::array<std::uint32_t, catalog.size()> ids{};
    for (std::size_t i = 0; i < catalog.size(); ++i) ids[i] = catalog[i].id;
    std::ranges::sort(ids);
    return std::ranges::adjacent_find(ids) == ids.end();
}

static_assert(all_have_required_fields(),
              "Every metric needs name, description and track");
static_assert(all_ids_unique(),
              "Metric ids must be unique across all adapters");

} // namespace profcat
