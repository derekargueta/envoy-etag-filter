# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #

    "envoy.access_loggers.file":                        "//source/extensions/access_loggers/file:config",
    "envoy.access_loggers.http_grpc":                   "//source/extensions/access_loggers/grpc:http_config",

    #
    # HTTP filters
    #

    "envoy.filters.http.cache":                         "//source/extensions/filters/http/cache:config",
    "envoy.filters.http.lua":                           "//source/extensions/filters/http/lua:config",
    "envoy.filters.http.router":                        "//source/extensions/filters/http/router:config",

    #
    # Listener filters
    #

    "envoy.filters.listener.http_inspector":            "//source/extensions/filters/listener/http_inspector:config",

    #
    # Network filters
    #

    "envoy.filters.network.http_connection_manager":    "//source/extensions/filters/network/http_connection_manager:config",

    #
    # Resource monitors
    #

    "envoy.resource_monitors.fixed_heap":               "//source/extensions/resource_monitors/fixed_heap:config",
    "envoy.resource_monitors.injected_resource":        "//source/extensions/resource_monitors/injected_resource:config",

    #
    # Stat sinks
    #

    "envoy.stat_sinks.metrics_service":                 "//source/extensions/stat_sinks/metrics_service:config",
    "envoy.stat_sinks.statsd":                          "//source/extensions/stat_sinks/statsd:config",

    #
    # Transport sockets
    #

    "envoy.transport_sockets.alts":                     "//source/extensions/transport_sockets/alts:config",
    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",
    "envoy.transport_sockets.tap":                      "//source/extensions/transport_sockets/tap:config",
    "envoy.transport_sockets.quic":                     "//source/extensions/quic_listeners/quiche:quic_transport_socket_factory_lib",

    # Http Upstreams (excepting envoy.upstreams.http.generic which is hard-coded into the build so not registered here)
    "envoy.upstreams.http.http":                     "//source/extensions/upstreams/http/http:config",
    "envoy.upstreams.http.tcp":                     "//source/extensions/upstreams/http/tcp:config",

    #
    # CacheFilter plugins
    #

    "envoy.filters.http.cache.simple_http_cache":       "//source/extensions/filters/http/cache/simple_http_cache:simple_http_cache_lib",


}
