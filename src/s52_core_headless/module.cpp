#include "marine_chart/s52_core_headless/module.h"

namespace marine_chart::s52_core_headless {

ModuleInfo describe_module() noexcept {
    return {
        make_neutral_string("s52_core_headless"),
        make_neutral_string("Zero-wx S-52 portrayal core module boundary"),
        make_neutral_color(24, 64, 128),
        make_neutral_rect(10, 20, 640, 480),
        {
            make_neutral_string("headless"),
            make_neutral_string("zero-wx")
        },
        {
            {
                make_neutral_string("render-path"),
                make_neutral_string("rhi")
            },
            {
                make_neutral_string("role"),
                make_neutral_string("portrayal-core")
            }
        }
    };
}

}  // namespace marine_chart::s52_core_headless
