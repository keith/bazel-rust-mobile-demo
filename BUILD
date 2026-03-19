load("@rules_android//rules:rules.bzl", "android_binary", "android_library")
load("@rules_apple//apple:ios.bzl", "ios_application")
load("@rules_apple//apple:macos.bzl", "macos_application")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "objc_library")
load("@rules_rust//rust:defs.bzl", "rust_library", "rust_static_library")

# Empty staticlib that provides the Rust allocator symbols needed when
# linking rust_library output into a C/C++ binary.
# If you have isolated rust code you could use only a single rust_static_library
# https://github.com/bazelbuild/rules_rust/issues/1238
rust_static_library(
    name = "rust_allocator_shim",
    srcs = ["allocator_shim.rs"],
    edition = "2021",
)

rust_library(
    name = "rust_lib",
    srcs = ["demo.rs"],
    edition = "2021",
    deps = [":rust_allocator_shim"],
)

cc_binary(
    name = "normal_binary",
    srcs = ["main.c"],
    deps = [":rust_lib"],
)

#=== iOS targets
objc_library(
    name = "ios_main",
    srcs = ["ios_main.m"],
    tags = ["manual"],  # Get transition from ios_application
    deps = [":rust_lib"],
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
    name = "jni_shim",  # TODO: This might be removable now
    srcs = ["android_link_hack.c"],  # Required because of https://github.com/bazelbuild/rules_rust/issues/1271
    linkopts = [
        "-llog",  # NDK logging library for __android_log_print
        "-lm",  # Required to avoid dlopen runtime failures unrelated to rust
        "-fuse-ld=lld",  # Work around https://github.com/bazelbuild/rules_rust/issues/1276, the default in newer NDK versions
    ],
    tags = ["manual"],  # Get transition from :android_app
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
    tags = ["manual"],  # Get transition from :android_app
    deps = [":jni_shim"],
)

android_binary(
    name = "android_app",
    custom_package = "com.example.androidapp",
    manifest = "AndroidManifest.xml",
    deps = [":android_main"],
)
