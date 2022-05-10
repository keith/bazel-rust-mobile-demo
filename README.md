# bazel-rust-mobile-demo

This is an example repository for how to setup a bazel build that uses
rust on iOS and Android.

## Usage

You can explore the code, which has some comments around the issues you
hit. You can also run each entry point to see them working.

For a standard `cc_binary` running on your host machine:

```sh
$ bazel run normal_binary
...
Ferris says hello!
Some value from rust: 42
```

For an `ios_application` (requires running on macOS with Xcode setup):

```sh
$ bazel run ios_app
...
com.example.iosapp: 25008
Ferris says hello!
Some value from rust: 42
```

For an `android_application` (requires the android SDK and an emulator
to be configured):

```sh
$ bazel mobile-install android_app --fat_apk_cpu=arm64-v8a --start_app
# View the result in the emulator, or view logs with 'adb logcat'
```

## Notes

- At the time of writing this setup was tested with bazel 5.1.1
- The key to targeting the right platforms until the iOS and Android
  rules natively support bazel platforms is the
  [`platform_mappings`](platform_mappings) file, and the `platform`
  rules in the [`BUILD`](BUILD) file
  ([docs](https://bazel.build/concepts/platforms-intro#platform-mappings))
- If you don't want to use a root `platform_mappings` file you can pass
  `--platform_mappings=path/to/platform_mappings`
- The `rules_rust` patch, and `android_armeabi` platform definition will
  change with bazel 6.x since
  https://github.com/bazelbuild/bazel/issues/14982 was fixed
- When testing Android, depending on your emulator or device you can
  pass whatever `--fat_apk_cpu` value you need
- When testing with iOS you can pass whatever `--ios_multi_cpus` value
  you need
- When using something like this in production you should checkout
  [cxx](https://github.com/dtolnay/cxx) which helps bridge between rust
  and C++
- This example doesn't include it but using
  [cargo-raze](https://github.com/google/cargo-raze/) works fine for
  rust dependencies from our testing
- When using `cargo-raze` with the arm64 iOS simulator you need [this
  patch](https://github.com/google/cargo-raze/pull/484) for some cases,
  hopefully it's in a release soon
- When debugging `platform_mappings` issues,
  `--toolchain_resolution_debug='.*'` is verbose but very useful

- When debugging toolchain issues with platforms, you likely need to

- toolchain resolution debug
- cargo raze
- android sdk setup

- supprot linux?
