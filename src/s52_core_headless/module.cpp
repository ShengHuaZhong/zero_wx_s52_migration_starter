#include "marine_chart/s52_core_headless/module.h"

namespace marine_chart::s52_core_headless {

ModuleInfo describe_module() noexcept {
    return {
        make_neutral_string("s52_core_headless"),
        make_neutral_string("Zero-wx S-52 portrayal core module boundary"),
        make_neutral_color(24, 64, 128)
    };
}

}  // namespace marine_chart::s52_core_headless
