run:
	./bazel-bin/envoy -c examples/example.v2.yaml

compile:
	bazel build //:envoy

test:
	bazel test //:etag_test

valgrind:
	valgrind ./bazel-bin/envoy -c examples/example.v2.yaml

clean:
	rm -rf gen/*
	bazel clean --expunge
