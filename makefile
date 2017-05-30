HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CPPFLAGS += -I/usr/local/include -pthread
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
           -lgrpc++_reflection \
           -lprotobuf -lpthread -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
           -lprotobuf -lpthread -ldl
endif

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`



all: greeter_client greeter_server

greeter_client: helloworld.pb.o helloworld.grpc.pb.o greeter_client.o
	g++ $^ $(LDFLAGS) -o $@

greeter_server: helloworld.pb.o helloworld.grpc.pb.o greeter_server.o
	g++ $^ $(LDFLAGS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h greeter_client greeter_server greeter_async_client greeter_async_client2 greeter_async_server
