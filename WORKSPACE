load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_rust",
    patches = ["//:rules_rust.patch"],  # Remove if you're using bazel 6.x
    sha256 = "edb87c0d2ba70823fe3df7862676d695599314a4634b9758bd55f0e8f19c2751",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_rust/releases/download/0.4.0/rules_rust-v0.4.0.tar.gz",
        "https://github.com/bazelbuild/rules_rust/releases/download/0.4.0/rules_rust-v0.4.0.tar.gz",
    ],
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies", "rust_register_toolchains")

rules_rust_dependencies()

rust_register_toolchains(
    extra_target_triples = [
        "aarch64-apple-ios-sim",
        "aarch64-apple-ios",
        "aarch64-linux-android",
        "armv7-linux-androideabi",
        "i686-linux-android",
        "x86_64-apple-ios",
        "x86_64-linux-android",
    ],
)

http_archive(
    name = "build_bazel_rules_apple",
    sha256 = "a5f00fd89eff67291f6cd3efdc8fad30f4727e6ebb90718f3f05bbf3c3dd5ed7",
    url = "https://github.com/bazelbuild/rules_apple/releases/download/0.33.0/rules_apple.0.33.0.tar.gz",
)

load(
    "@build_bazel_rules_apple//apple:repositories.bzl",
    "apple_rules_dependencies",
)

apple_rules_dependencies()

load(
    "@build_bazel_rules_swift//swift:repositories.bzl",
    "swift_rules_dependencies",
)

swift_rules_dependencies()

load(
    "@build_bazel_rules_swift//swift:extras.bzl",
    "swift_rules_extra_dependencies",
)

swift_rules_extra_dependencies()

load(
    "@build_bazel_apple_support//lib:repositories.bzl",
    "apple_support_dependencies",
)

apple_support_dependencies()

android_sdk_repository(name = "androidsdk")

android_ndk_repository(name = "androidndk", api_level=21)
