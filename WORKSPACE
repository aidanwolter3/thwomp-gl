load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# GL Framework - Window management
http_archive(
    name = "glfw",
    build_file = "glfw.BUILD",
    strip_prefix = "glfw-3.3.2",
    urls = ["https://github.com/glfw/glfw/archive/3.3.2.zip"],
    sha256 = "33c6bfc422ca7002befbb39a7a60dc101d32c930ee58be532ffbcd52e9635812",
)

# GL Mathmatics - Matrices and stuff
http_archive(
    name = "glm",
    build_file = "glm.BUILD",
    strip_prefix = "glm-0.9.9.7",
    urls = ["https://github.com/g-truc/glm/archive/0.9.9.7.zip"],
    sha256 = "c5e167c042afd2d7ad642ace6b643863baeb33880781983563e1ab68a30d3e95",
)

# Image loader
new_git_repository(
    name = "stb",
    remote = "https://github.com/nothings/stb.git",
    build_file = "stb.BUILD",
    commit = "f54acd4e13430c5122cab4ca657705c84aa61b08",
)
