# bazel-rust-mobile-demo

This is an example repository for how to setup a bazel build that uses
rust on iOS and Android. I also did [a talk](https://www.youtube.com/watch?v=e2ID05dpJzo)
on this at bazelcon.

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
$ bazel mobile-install android_app
# View the result in the emulator, or view logs with 'adb logcat'
```

## Notes

- At the time of writing this setup was tested with bazel 9.0.1
- When testing Android, depending on your emulator or device you can
  pass whatever `--android_platforms` value you need
- When testing with iOS you can pass whatever `--ios_multi_cpus` value
  you need
- When using something like this in production you should checkout
  [cxx](https://github.com/dtolnay/cxx) which helps bridge between rust
  and C++
- This example doesn't include rust dependency management, but
  [`crate_universe` in
  `rules_rust`](https://bazelbuild.github.io/rules_rust/crate_universe_bzlmod.html)
  can be used with this.
- When debugging which C++ compiler is being used
  `--toolchain_resolution_debug='.*'` is verbose but very useful
- If you find any other interesting gotchas when setting this up please
  submit an issue or PR here so we can document them for the community!
