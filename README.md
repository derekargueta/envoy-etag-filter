Envoy Etag Filter
===================

TODO
- Support list of etags
- Support `ETag: W/"0815"`
- Support range - For GET and HEAD methods, used in combination with an Range header, it can guarantee that the new ranges requested comes from the same resource than the previous one. If it doesn't match, then a 416 (Range Not Satisfiable) response is returned.


Resources
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-Match
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/If-None-Match
- https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/ETag
- https://tools.ietf.org/html/rfc7232#section-2.3
- https://tools.ietf.org/html/rfc7232#section-3.1
- https://tools.ietf.org/html/rfc7232#section-3.2

