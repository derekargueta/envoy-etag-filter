run:
	./bazel-bin/envoy -c examples/example.v2.yaml --v2-config-only

compile:
	bazel build //:envoy

test:
	bazel test //:etag_test

valgrind:
	valgrind ./bazel-bin/envoy -c examples/example.v2.yaml --v2-config-only

clean:
	rm -rf gen/*
	rm -rf bazel-*
