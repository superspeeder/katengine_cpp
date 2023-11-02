#include "window.hpp"

namespace kat::os {
    WindowSystem::WindowSystem() {
        glfwInit();
        int monitorCount;
        auto **monitors = glfwGetMonitors(&monitorCount);
        m_Monitors.resize(monitorCount);
        m_Monitors.assign(monitors, monitors + monitorCount);
    }
    WindowSystem::~WindowSystem() { glfwTerminate(); }
    std::optional<GLFWmonitor *> WindowSystem::try_get_monitor(unsigned int monitorIndex) const {
        if (monitorIndex < m_Monitors.size())
            return m_Monitors[monitorIndex];
        return std::nullopt;
    }

    GLFWmonitor *WindowSystem::get_monitor_or(unsigned int monitorIndex, GLFWmonitor *other) const {
        return try_get_monitor(monitorIndex).value_or(other);
    }
    GLFWmonitor *WindowSystem::get_monitor_or_primary(unsigned int monitorIndex) const { return get_monitor_or(monitorIndex, m_Monitors[0]); }
    GLFWmonitor *WindowSystem::get_monitor_or_last(unsigned int monitorIndex) const {
        return get_monitor_or(monitorIndex, m_Monitors[monitorIndex - 1]);
    }
} // namespace kat::os