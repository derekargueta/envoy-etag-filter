Envoy Etag Filter
===================

TODO
- Support list of etags
- Support asterisk etag
- Support `ETag: W/"0815"`
- Support range - For GET and HEAD methods, used in combination with an Range header, it can guarantee that the new ranges requested comes from the same resource than the previous one. If it doesn't match, then a 416 (Range Not Satisfiable) response is returned.