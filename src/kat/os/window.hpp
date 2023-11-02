#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace kat::os {

    // You probably don't want to pick this manually, you should depend on the color depth provided by a monitor.
    struct ColorDepth {
        unsigned int red = 8, green = 8, blue = 8;

        // These are more flexible.. but if you are changing them you probably are making a mistake in your logic.
        unsigned int alpha = 8;
        unsigned int depth = 24;
        unsigned int stencil = 8;
    };

    struct VideoMode {
        glm::uvec2 size;
        ColorDepth color_depth;
        unsigned int refresh_rate;

        static VideoMode from(const GLFWvidmode *vidmode);
    };

    namespace wm {
        struct Windowed {
            glm::uvec2 size{800, 600};
            std::optional<glm::ivec2> position;
            bool decorated = true;
        };

        struct FullscreenWindowed {
            unsigned int monitor = 0;
        };

        struct FullscreenExclusive {
            unsigned int monitor = 0;
            std::optional<VideoMode> video_mode;
        };
    } // namespace wm

    using WindowMode = std::variant<wm::Windowed>;

    struct Monitor {
        GLFWmonitor* handle;

        VideoMode get_video_mode();
    };

    class WindowSystem {
        std::vector<GLFWmonitor *> monitors;

      public:
        WindowSystem();
        ~WindowSystem();

        [[nodiscard]] std::optional<GLFWmonitor *> try_get_monitor(unsigned int monitorIndex) const;
        [[nodiscard]] GLFWmonitor *get_monitor_or(unsigned int monitorIndex, GLFWmonitor *other) const;
        [[nodiscard]] GLFWmonitor *get_monitor_or_primary(unsigned int monitorIndex) const;
        [[nodiscard]] GLFWmonitor *get_monitor_or_last(unsigned int monitorIndex) const;
    };

    struct WindowProperties {
        std::string title = "Window";
        WindowMode windowMode = wm::Windowed({800, 600});
        bool resizable = false;
        bool visible = true;
        // decorated is in wm::Windowed as it has no effect outside windowed mode.
        bool auto_iconify = true;
        bool floating = false;
        bool maximized = false;
        bool center_cursor = true;
        bool transparent_framebuffer = false;
        bool focus_on_show = true;
        bool scale_to_monitor = false;
    };

    class Window {
        GLFWwindow* window;

      public:
    };

} // namespace kat::os
