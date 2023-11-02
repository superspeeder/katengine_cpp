#include "window.hpp"

namespace kat::os {
    WindowSystem::WindowSystem() {
        glfwInit();
        int monitorCount;
        auto **monitors = glfwGetMonitors(&monitorCount);
        monitors.resize(monitorCount);
        monitors.assign(monitors, monitors + monitorCount);
    }
    WindowSystem::~WindowSystem() { glfwTerminate(); }
    std::optional<GLFWmonitor *> WindowSystem::try_get_monitor(unsigned int monitorIndex) const {
        if (monitorIndex < monitors.size())
            return monitors[monitorIndex];
        return std::nullopt;
    }

    GLFWmonitor *WindowSystem::get_monitor_or(unsigned int monitorIndex, GLFWmonitor *other) const {
        return try_get_monitor(monitorIndex).value_or(other);
    }
    GLFWmonitor *WindowSystem::get_monitor_or_primary(unsigned int monitorIndex) const { return get_monitor_or(monitorIndex, monitors[0]); }
    GLFWmonitor *WindowSystem::get_monitor_or_last(unsigned int monitorIndex) const {
        return get_monitor_or(monitorIndex, monitors[monitorIndex - 1]);
    }

    VideoMode Monitor::get_video_mode() {
        const auto* vm = glfwGetVideoMode(handle);
        return VideoMode::from(vm);
    }

    VideoMode VideoMode::from(const GLFWvidmode *vidmode) {
        return {
                {
                        static_cast<unsigned int>(vidmode->width),
                        static_cast<unsigned int>(vidmode->height),
                }, {
                        static_cast<unsigned int>(vidmode->redBits),
                        static_cast<unsigned int>(vidmode->greenBits),
                        static_cast<unsigned int>(vidmode->blueBits),
                },
                static_cast<unsigned int>(vidmode->refreshRate),
        }
    }
} // namespace kat::os