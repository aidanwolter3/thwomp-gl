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
        "@glad",
        "@glfw",
        "@glm",
    ],
)

cc_library(
    name = "objects",
    hdrs = [
        "thwomp.h",
    ],
    srcs = [
        "thwomp.cc",
    ],
    deps = [
        ":base",
        "@glad",
        "@stb",
    ],
)

cc_binary(
    name = "thwomp",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":base",
        ":objects",
        "@glad",
    ],
    data = [
        "fragment.glsl",
        "vertex.glsl",
    ],
)
