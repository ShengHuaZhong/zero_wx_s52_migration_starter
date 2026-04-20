#pragma once

#include "marine_chart/chart_runtime/open_chart.h"

#include <QWidget>

#include <optional>

namespace marine_chart::chart_qt_host {

class ChartHostWidget final : public QWidget {
public:
    explicit ChartHostWidget(QWidget* parent = nullptr);

    void set_open_chart_result(marine_chart::chart_runtime::OpenChartResult result);
    void clear_chart() noexcept;

    [[nodiscard]] bool has_chart() const noexcept;
    [[nodiscard]] std::size_t current_command_count() const noexcept;
    [[nodiscard]] const marine_chart::chart_runtime::RuntimeRenderFrame* current_render_frame() const noexcept;

private:
    std::optional<marine_chart::chart_runtime::OpenChartResult> open_chart_result_;
};

}  // namespace marine_chart::chart_qt_host
