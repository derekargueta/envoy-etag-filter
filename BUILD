package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
	"envoy_cc_binary",
    "envoy_cc_extension",
	"envoy_cc_library",
	"envoy_cc_test",
    # "envoy_extension_package",
    "envoy_proto_library",
)

# envoy_extension_package()

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
        "@envoy//source/common/http:headers_lib",
        "@envoy//source/common/common:enum_to_int",
        "@envoy//source/extensions/filters/http/common:pass_through_filter_lib",
    ],
)

envoy_cc_extension(
    name = "etag_config",
    srcs = ["etag_config.cc"],
    hdrs = ["etag_config.h"],
    repository = "@envoy",
    # category = "envoy.filters.http",
    # security_posture = "requires_trusted_downstream_and_upstream",
    # status = "alpha",
    deps = [
        ":etag_lib",
        ":pkg_cc_proto",
        "@envoy//source/extensions/filters/http/common:factory_base_lib",
    ],
)

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

api_proto_package()
