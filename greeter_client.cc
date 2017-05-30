#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "helloworld.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::HelloReplyAgain;
using helloworld::Greeter;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub (Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello() {
    // Data we are sending to the server.
    HelloRequest request;
    
    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub ->SayHello(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  int SayHelloAgain() {
    // Follows the same pattern as SayHello.
    HelloRequest request;
    HelloReplyAgain reply;
    ClientContext context;

    // Here we can the stub's newly available method we just added.
    Status status = stub ->SayHelloAgain(&context, request, &reply);
    if (status.ok()) {
      return reply.number();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl
                << "RPC failed"
                << std::endl;
      return 0;
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub ;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  
  std::string stringReply = greeter.SayHello();
  std::cout << "The following string was received by the client: " << stringReply << std::endl;
  
  int numReply = greeter.SayHelloAgain();
  std::cout << "The following number was received by the client: " << numReply << std::endl;

  return 0;
}