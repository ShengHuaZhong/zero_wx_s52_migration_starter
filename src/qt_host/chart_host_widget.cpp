#include "marine_chart/chart_qt_host/chart_host_widget.h"

namespace marine_chart::chart_qt_host {

ChartHostWidget::ChartHostWidget(QWidget* parent)
    : QWidget(parent) {
    setObjectName("chart-host-widget");
    setMinimumSize(320, 240);
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

}  // namespace marine_chart::chart_qt_host
