#pragma once

#include "marine_chart/s52_core_headless/neutral_color.h"
#include "marine_chart/s52_core_headless/neutral_containers.h"
#include "marine_chart/s52_core_headless/neutral_geometry.h"
#include "marine_chart/s52_core_headless/neutral_image_metadata.h"
#include "marine_chart/s52_core_headless/neutral_string.h"

namespace marine_chart::s52_core_headless {

struct PaletteDefinition final {
    NeutralString name;
    NeutralString graphics_file_name;
    NeutralMap<NeutralString, NeutralColor> entries;

    [[nodiscard]] bool empty() const noexcept {
        return name.empty() || graphics_file_name.empty() || entries.empty();
    }

    bool operator==(const PaletteDefinition&) const noexcept = default;
};

struct PaletteCatalog final {
    NeutralMap<NeutralString, PaletteDefinition> palettes;

    [[nodiscard]] bool empty() const noexcept {
        return palettes.empty();
    }

    bool operator==(const PaletteCatalog&) const noexcept = default;
};

struct SymbolDefinition final {
    NeutralString rcid;
    NeutralString name;
    NeutralString description;
    NeutralRect source_rect;
    NeutralPoint pivot;
    NeutralString color_reference;

    [[nodiscard]] bool empty() const noexcept {
        return rcid.empty()
            || name.empty()
            || description.empty()
            || source_rect.is_empty()
            || color_reference.empty();
    }

    bool operator==(const SymbolDefinition&) const noexcept = default;
};

struct SymbolCatalog final {
    NeutralMap<NeutralString, SymbolDefinition> symbols;

    [[nodiscard]] bool empty() const noexcept {
        return symbols.empty();
    }

    bool operator==(const SymbolCatalog&) const noexcept = default;
};

struct LineStyleDefinition final {
    NeutralString name;
    NeutralString vector_source;

    [[nodiscard]] bool empty() const noexcept {
        return name.empty() || vector_source.empty();
    }

    bool operator==(const LineStyleDefinition&) const noexcept = default;
};

struct LineStyleCatalog final {
    NeutralMap<NeutralString, LineStyleDefinition> line_styles;

    [[nodiscard]] bool empty() const noexcept {
        return line_styles.empty();
    }

    bool operator==(const LineStyleCatalog&) const noexcept = default;
};

struct PatternDefinition final {
    NeutralString name;
    NeutralSize tile_size;
    NeutralString pattern_source;

    [[nodiscard]] bool empty() const noexcept {
        return name.empty() || tile_size.is_empty() || pattern_source.empty();
    }

    bool operator==(const PatternDefinition&) const noexcept = default;
};

struct PatternCatalog final {
    NeutralMap<NeutralString, PatternDefinition> patterns;

    [[nodiscard]] bool empty() const noexcept {
        return patterns.empty();
    }

    bool operator==(const PatternCatalog&) const noexcept = default;
};

struct AssetCatalogs final {
    PaletteCatalog palettes;
    SymbolCatalog symbols;
    LineStyleCatalog line_styles;
    PatternCatalog patterns;

    [[nodiscard]] bool empty() const noexcept {
        return palettes.empty()
            && symbols.empty()
            && line_styles.empty()
            && patterns.empty();
    }

    bool operator==(const AssetCatalogs&) const noexcept = default;
};

}  // namespace marine_chart::s52_core_headless
