// https://github.com/bazelbuild/rules_rust/issues/1271
#include <android/log.h>

extern void android_link_hack(void);

void call_link_hack(void) {
  android_link_hack();
  // Just to verify this is built targeting android for debugging
  __android_log_print(ANDROID_LOG_INFO, "RustDemo", "NDK link hack called");
}
