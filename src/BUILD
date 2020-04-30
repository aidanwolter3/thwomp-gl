cc_library(
    name = "base",
    hdrs = [
        "window.h",
    ],
    srcs = [
        "window.cc",
    ],
    deps = [
        "//glad",
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
