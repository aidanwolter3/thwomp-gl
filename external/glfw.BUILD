package(default_visibility = ["//visibility:public"],)

cc_library(
    name = "glfw",

    # These srcs and hdrs may need to be updated when GLFW is updated.
    srcs = glob([
        "src/context.c",
        "src/egl_context.c",
        "src/egl_context.h",
        "src/glfw_config.h",
        "src/glx_context.c",
        "src/glx_context.h",
        "src/init.c",
        "src/input.c",
        "src/internal.h",
        "src/linux_joystick.c",
        "src/linux_joystick.h",
        "src/mappings.c",
        "src/mappings.h",
        "src/monitor.c",
        "src/osmesa_context.c",
        "src/osmesa_context.h",
        "src/posix_thread.c",
        "src/posix_thread.h",
        "src/posix_time.c",
        "src/posix_time.h",
        "src/posix_tls.c",
        "src/posix_tls.h",
        "src/vulkan.c",
        "src/window.c",
        "src/x11_init.c",
        "src/x11_monitor.c",
        "src/x11_platform.h",
        "src/x11_window.c",
        "src/xkb_unicode.c",
        "src/xkb_unicode.h",
    ]),
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
    ],

    copts = [
        "-I/usr/include",
    ],
    linkopts = [
        # Note:  This is a bit of a HACK to build & link against whatever
        # version of X11 is installed on the system. Ideally, X11 would also
        # be built with bazel to ensure consistency.
        "-lX11",
        "-lXrandr",
        "-lXinerama",
        "-ldl",
        "-lXcursor",
        "-pthread",
    ],

    defines = [
        "_GLFW_X11",
        "_GLFW_GLX",
        "_GLFW_USE_OPENGL",
    ],
)
