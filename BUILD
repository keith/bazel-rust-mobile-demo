load("@build_bazel_rules_apple//apple:ios.bzl", "ios_application")
load("@build_bazel_rules_apple//apple:macos.bzl", "macos_application")
load("@rules_rust//rust:defs.bzl", "rust_library")

# Ideally this wouldn't be required https://github.com/bazelbuild/rules_rust/issues/1238
cc_library(
    name = "alloc",
    srcs = ["alloc.cc"],
)

rust_library(
    name = "rust_lib",
    srcs = ["demo.rs"],
    edition = "2018",
    deps = [":alloc"],
)

cc_binary(
    name = "normal_binary",
    srcs = ["main.c"],
    deps = [":rust_lib"],
)

#=== iOS targets
# This being required is a bug in objc_library, ideally 'ios_main' could depend directly on 'rust_lib'
cc_library(
    name = "shim",
    deps = [":rust_lib"],
)

objc_library(
    name = "ios_main",
    srcs = ["ios_main.m"],
    deps = [":shim"],
)

ios_application(
    name = "ios_app",
    bundle_id = "com.example.iosapp",
    families = ["iphone"],
    infoplists = ["Info.plist"],
    minimum_os_version = "13.0",
    deps = [":ios_main"],
)

macos_application(
    name = "macos_app",
    bundle_id = "com.example.macosapp",
    infoplists = ["Info.plist"],
    minimum_os_version = "10.15",
    deps = [":ios_main"],
)

#==== Android targets
cc_library(
    name = "jni_shim",
    srcs = ["android_link_hack.c"],  # Required because of https://github.com/bazelbuild/rules_rust/issues/1271
    linkopts = [
        "-lm",  # Required to avoid dlopen runtime failures unrelated to rust
        "-fuse-ld=lld",  # Work around https://github.com/bazelbuild/rules_rust/issues/1276, the default in newer NDK versions
    ],
    deps = [":rust_lib"],
    alwayslink = True,  # Required since JNI symbols appear to be unused
)

android_library(
    name = "android_main",
    srcs = [
        "AndroidMain.java",
        "JniShim.java",
    ],
    custom_package = "com.example.androidapp",
    manifest = "AndroidManifest.xml",
    resource_files = ["res/layout/android_main.xml"],
    deps = [":jni_shim"],
)

android_binary(
    name = "android_app",
    custom_package = "com.example.androidapp",
    manifest = "AndroidManifest.xml",
    deps = [":android_main"],
)

#==== Platform definitions that are used in the 'platform_mappings' file
platform(
    name = "android_aarch64",
    constraint_values = [
        "@platforms//cpu:aarch64",
        "@platforms//os:android",
    ],
)

platform(
    name = "android_armeabi",
    constraint_values = [
        "@platforms//cpu:armv7",
        "@platforms//os:android",
    ],
)

platform(
    name = "android_x86",
    constraint_values = [
        "@platforms//cpu:x86_32",
        "@platforms//os:android",
    ],
)

platform(
    name = "android_x86_64",
    constraint_values = [
        "@platforms//cpu:x86_64",
        "@platforms//os:android",
    ],
)

platform(
    name = "macos_x86_64",
    constraint_values = [
        "@platforms//cpu:x86_64",
        "@platforms//os:macos",
    ],
)

platform(
    name = "macos_arm64",
    constraint_values = [
        "@platforms//cpu:arm64",
        "@platforms//os:macos",
    ],
)

platform(
    name = "ios_x86_64",
    constraint_values = [
        "@platforms//cpu:x86_64",
        "@platforms//os:ios",
        "@build_bazel_apple_support//constraints:simulator",
    ],
)

platform(
    name = "ios_sim_arm64",
    constraint_values = [
        "@platforms//cpu:arm64",
        "@platforms//os:ios",
        "@build_bazel_apple_support//constraints:simulator",
    ],
)

platform(
    name = "ios_arm64",
    constraint_values = [
        "@platforms//cpu:arm64",
        "@platforms//os:ios",
        "@build_bazel_apple_support//constraints:device",
    ],
)
