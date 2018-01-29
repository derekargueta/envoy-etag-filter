package(default_visibility = ["//visibility:public"])

load(
	"@envoy//bazel:envoy_build_system.bzl",
	"envoy_cc_binary",
	"envoy_cc_library",
	"envoy_cc_test",
    "envoy_proto_library",
)

envoy_cc_binary(
	name = "envoy",
	repository = "@envoy",
	deps = [
		":etag_config",
		"@envoy//source/exe:envoy_main_entry_lib",
	],
)

envoy_cc_library(
    name = "etag_lib",
    srcs = ["etag.cc"],
    hdrs = ["etag.h"],
    repository = "@envoy",
    deps = [
        "@envoy//source/exe:envoy_common_lib",
    ],
    external_deps = ["abseil_strings"],
)

envoy_cc_library(
    name = "etag_config",
    srcs = ["etag_config.cc"],
    hdrs = ["etag_config.h"],
    repository = "@envoy",
    deps = [
        ":etag_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)
