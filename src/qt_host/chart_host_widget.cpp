#include "marine_chart/chart_qt_host/chart_host_widget.h"

#include <QColor>
#include <rhi/qrhi.h>

#include <algorithm>
#include <optional>

namespace marine_chart::chart_qt_host {

namespace {

QColor make_preview_color(const marine_chart::chart_runtime::RuntimeColor& color) {
    return QColor(
        std::min(255, 32 + static_cast<int>(color.red) * 3 / 4),
        std::min(255, 40 + static_cast<int>(color.green) * 3 / 4),
        std::min(255, 56 + static_cast<int>(color.blue) * 3 / 4),
        color.alpha);
}

std::optional<marine_chart::chart_runtime::RuntimeColor> select_preview_color(
    const marine_chart::chart_runtime::RuntimeRenderFrame& render_frame) {
    for(const auto& area_command : render_frame.area_commands) {
        if(area_command.fill_color.has_value()) {
            return area_command.fill_color;
        }

        if(area_command.pattern_color.has_value()) {
            return area_command.pattern_color;
        }
    }

    if(!render_frame.point_commands.empty()) {
        return render_frame.point_commands.front().tint_color;
    }

    if(!render_frame.line_commands.empty()) {
        return render_frame.line_commands.front().stroke_color;
    }

    if(!render_frame.text_commands.empty()) {
        return render_frame.text_commands.front().text_color;
    }

    return std::nullopt;
}

QColor resolve_clear_color(
    const std::optional<marine_chart::chart_runtime::OpenChartResult>& open_chart_result) {
    if(!open_chart_result.has_value()) {
        return QColor(15, 23, 32);
    }

    if(const auto preview_color = select_preview_color(open_chart_result->render_frame); preview_color.has_value()) {
        return make_preview_color(*preview_color);
    }

    return QColor(42, 111, 151);
}

}  // namespace

ChartHostWidget::ChartHostWidget(QWidget* parent)
    : QRhiWidget(parent) {
    setObjectName("chart-host-widget");
    setMinimumSize(320, 240);
#if defined(Q_OS_WIN)
    setApi(Api::Direct3D11);
#endif
}

void ChartHostWidget::set_open_chart_result(marine_chart::chart_runtime::OpenChartResult result) {
    open_chart_result_ = std::move(result);
    update();
}

void ChartHostWidget::clear_chart() noexcept {
    open_chart_result_.reset();
    update();
}

bool ChartHostWidget::has_chart() const noexcept {
    return open_chart_result_.has_value();
}

std::size_t ChartHostWidget::current_command_count() const noexcept {
    return open_chart_result_.has_value() ? open_chart_result_->render_frame.command_count() : 0;
}

const marine_chart::chart_runtime::RuntimeRenderFrame* ChartHostWidget::current_render_frame() const noexcept {
    return open_chart_result_.has_value() ? &open_chart_result_->render_frame : nullptr;
}

void ChartHostWidget::render(QRhiCommandBuffer* cb) {
    cb->beginPass(renderTarget(), resolve_clear_color(open_chart_result_), {1.0f, 0}, nullptr);
    cb->endPass();
}

}  // namespace marine_chart::chart_qt_host
