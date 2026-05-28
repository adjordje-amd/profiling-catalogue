#include "profcat/catalog.hpp"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace {

struct Args {
    std::string filter_kind;
    std::string filter_stage;
    std::string filter_substr;
    bool        long_form{false};
    bool        show_help{false};
};

void print_help(const char* prog) {
    std::cout <<
        "Usage: " << prog << " [options]\n"
        "  --kind <k>        filter by kind (counter|gauge|event|span|sample|derived)\n"
        "  --stage <s>       filter by stage (cpu|memory|interconnect|submission|gpu|device-telemetry|apu-fabric)\n"
        "  --grep <text>     case-sensitive substring filter on name/description\n"
        "  --long            show description column\n"
        "  --help            this message\n";
}

bool parse_args(int argc, char** argv, Args& a) {
    for (int i = 1; i < argc; ++i) {
        std::string_view s = argv[i];
        if (s == "--help" || s == "-h") { a.show_help = true; return true; }
        if (s == "--long") { a.long_form = true; continue; }
        if (s == "--kind"  && i + 1 < argc) { a.filter_kind   = argv[++i]; continue; }
        if (s == "--stage" && i + 1 < argc) { a.filter_stage  = argv[++i]; continue; }
        if (s == "--grep"  && i + 1 < argc) { a.filter_substr = argv[++i]; continue; }
        std::cerr << "unknown arg: " << s << "\n";
        return false;
    }
    return true;
}

std::size_t terminal_width() {
    if (auto* env = std::getenv("COLUMNS")) {
        try { return std::stoul(env); } catch (...) {}
    }
    return 120;
}

std::string truncate(std::string_view s, std::size_t w) {
    if (s.size() <= w) return std::string{s};
    if (w <= 1) return std::string(w, '.');
    return std::string{s.substr(0, w - 1)} + "…";
}

} // namespace

int main(int argc, char** argv) {
    Args args;
    if (!parse_args(argc, argv, args)) return 2;
    if (args.show_help) { print_help(argv[0]); return 0; }

    std::vector<profcat::MetricDescriptor> rows;
    rows.reserve(profcat::catalog.size());

    for (auto const& d : profcat::catalog) {
        if (!args.filter_kind.empty()
            && args.filter_kind != profcat::to_string(d.kind)) continue;
        if (!args.filter_stage.empty()
            && args.filter_stage != profcat::to_string(d.stage)) continue;
        if (!args.filter_substr.empty()
            && d.name.find(args.filter_substr) == std::string_view::npos
            && d.description.find(args.filter_substr) == std::string_view::npos) continue;
        rows.push_back(d);
    }

    std::ranges::sort(rows, {}, &profcat::MetricDescriptor::name);

    const std::size_t cols = terminal_width();
    const std::size_t name_w  = 36;
    const std::size_t kind_w  = 8;
    const std::size_t track_w = 34;
    const std::size_t desc_w  = (cols > name_w + kind_w + track_w + 6)
                              ? cols - name_w - kind_w - track_w - 6
                              : 40;

    std::cout
        << std::left
        << std::setw(static_cast<int>(name_w))  << "NAME"      << "  "
        << std::setw(static_cast<int>(kind_w))  << "KIND"      << "  "
        << std::setw(static_cast<int>(track_w)) << "TRACK"     << "  "
        << "DESCRIPTION\n";
    std::cout << std::string(cols, '-') << "\n";

    for (auto const& d : rows) {
        std::cout
            << std::left
            << std::setw(static_cast<int>(name_w))  << truncate(d.name, name_w)   << "  "
            << std::setw(static_cast<int>(kind_w))  << profcat::to_string(d.kind) << "  "
            << std::setw(static_cast<int>(track_w)) << truncate(d.track, track_w) << "  ";
        if (args.long_form) {
            std::cout << d.description;
        } else {
            std::cout << truncate(d.description, desc_w);
        }
        std::cout << "\n";
    }

    std::cout << "\n"
              << rows.size() << " of " << profcat::catalog.size()
              << " metrics shown.\n";
    return 0;
}
