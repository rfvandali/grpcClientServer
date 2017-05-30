#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "helloworld.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {

    std::string message;

    std::cout << "Please type the string you'd like to send, followed by enter:";
    std::getline (std::cin, message);

    reply->set_message(message);
    return Status::OK;
  }

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
    
    int number;

    std::cout << "Please type the number you'd like to send, followed by enter:";
    std::cin >> number;

  while(!std::cin){
    // user didn't input a number
    std::cin.clear(); // reset failbit
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    std::cout << "The input was not numeric, please type the number you'd like to send, followed by enter:";
    std::cin >> number;
  }

    reply->set_message(std::to_string(number));
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}