cc_library(
    name = "base",
    hdrs = [
        "object.h",
        "program.h",
        "shader.h",
        "window.h",
    ],
    srcs = [
        "program.cc",
        "shader.cc",
        "window.cc",
    ],
    deps = [
        "//glad",
        "@glm//:glm",
        "@glfw//:glfw",
    ],
)

cc_binary(
    name = "thwomp",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":base",
    ],
)
