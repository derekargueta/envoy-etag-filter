Envoy Etag Filter
===================

- [ ] add unit tests

### Build
First follow the [setup instructions](https://github.com/envoyproxy/envoy/tree/master/bazel#building-envoy-with-bazel) in Envoy to install dependencies.
Then instead of building `//source/exe:envoy-static`, do
```
$ bazel build //:envoy
```


### Usage
There currently are no supported configuration options so usage is quite simple:
```
http_filters:
  - name: etag
  - name: envoy.router
```

### TODO
- Support weak matching (`ETag: W/"0815"`)
- Support range - For GET and HEAD methods, used in combination with an Range header, it can guarantee that the new ranges requested comes from the same resource than the previous one. If it doesn't match, then a 416 (Range Not Satisfiable) response is returned.
- Support generating Etags on the fly using a configuratble hash algorithm


### Resources
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Match
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-None-Match
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/ETag
- https://tools.ietf.org/html/rfc7232#section-2.3
- https://tools.ietf.org/html/rfc7232#section-3.1
- https://tools.ietf.org/html/rfc7232#section-3.2

