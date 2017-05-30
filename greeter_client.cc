#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include "helloworld.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::SendRequest;
using helloworld::StringReply;
using helloworld::NumberReply;
using helloworld::Greeter;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub (Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back from the server.
  std::string SendString() {
    // Data we are sending to the server.
    SendRequest request;
    
    // Container for the data we expect from the server.
    StringReply reply;

    // Context for the client.
    ClientContext context;

    // The actual RPC.
    Status status = stub ->SendString(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  int SendNumber() {
    // Follows the same pattern as SendString.
    SendRequest request;
    NumberReply reply;
    ClientContext context;

    Status status = stub ->SendNumber(&context, request, &reply);
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
  
  std::string stringReply = greeter.SendString();
  std::cout << "The following string was received by the client: " << stringReply << std::endl;
  
  int numReply = greeter.SendNumber();
  std::cout << "The following number was received by the client: " << numReply << std::endl;

  return 0;
}