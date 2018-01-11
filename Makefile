compile:
	bazel build //:envoy

test:
	bazel test //:etag_test

static-check:
	cppcheck --enable=all --language=c++ --std=c++14 --std=c++11 etag*

valgrind:
	valgrind ./bazel-bin/envoy -c examples/example.v2.yaml --v2-config-only

clean:
	rm -rf gen/*
	rm -rf bazel-*
