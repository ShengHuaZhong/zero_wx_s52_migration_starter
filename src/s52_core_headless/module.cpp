#include "marine_chart/s52_core_headless/module.h"

namespace marine_chart::s52_core_headless {

ModuleInfo describe_module() noexcept {
    return {
        "s52_core_headless",
        "Zero-wx S-52 portrayal core module boundary"
    };
}

}  // namespace marine_chart::s52_core_headless
