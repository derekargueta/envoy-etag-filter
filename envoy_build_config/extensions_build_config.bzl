# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #

    "envoy.access_loggers.file":                        "//source/extensions/access_loggers/file:config",

    #
    # HTTP filters
    #

    "envoy.filters.http.router":                        "//source/extensions/filters/http/router:config",

    #
    # Network filters
    #

    "envoy.filters.network.http_connection_manager":    "//source/extensions/filters/network/http_connection_manager:config",
    "envoy.filters.network.tcp_proxy":                  "//source/extensions/filters/network/tcp_proxy:config",

    #
    # Transport sockets
    #

    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",

    # Http Upstreams (excepting envoy.upstreams.http.generic which is hard-coded into the build so not registered here)
    #
    "envoy.upstreams.http.http":                        "//source/extensions/upstreams/http/http:config",
    "envoy.upstreams.http.tcp":                         "//source/extensions/upstreams/http/tcp:config",
}

# These can be changed to ["//visibility:public"], for  downstream builds which
# need to directly reference Envoy extensions.
EXTENSION_CONFIG_VISIBILITY = ["//visibility:public"]
EXTENSION_PACKAGE_VISIBILITY = ["//visibility:public"]
CONTRIB_EXTENSION_PACKAGE_VISIBILITY = ["//:contrib_library"]
