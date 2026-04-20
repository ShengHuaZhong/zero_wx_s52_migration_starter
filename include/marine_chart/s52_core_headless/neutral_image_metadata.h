#pragma once

#include "marine_chart/s52_core_headless/neutral_geometry.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

enum class ImagePixelFormat {
    rgba8,
    gray8
};

struct NeutralImageMetadata final {
    NeutralString resource_name;
    NeutralString source_path;
    NeutralSize pixel_size;
    ImagePixelFormat pixel_format{ImagePixelFormat::rgba8};
    bool has_alpha{true};

    [[nodiscard]] constexpr bool is_empty() const noexcept {
        return pixel_size.is_empty();
    }

    constexpr bool operator==(const NeutralImageMetadata&) const noexcept = default;
};

[[nodiscard]] inline NeutralImageMetadata make_neutral_image_metadata(
    NeutralStringView resource_name,
    NeutralStringView source_path,
    std::int32_t width,
    std::int32_t height,
    ImagePixelFormat pixel_format = ImagePixelFormat::rgba8,
    bool has_alpha = true) {
    return NeutralImageMetadata{
        make_neutral_string(resource_name),
        make_neutral_string(source_path),
        make_neutral_size(width, height),
        pixel_format,
        has_alpha
    };
}

}  // namespace marine_chart::s52_core_headless
