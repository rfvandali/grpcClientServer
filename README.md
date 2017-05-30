# grpcClientServer
Client/Server repository for gRPC protocol

Environment:
============
Running on Linux (Ubuntu) using protobuf version 3 or newer.
See grpc website for more info on setting up the environment: http://www.grpc.io/docs/

How to use:
===========
$ make
$ ./greeter_server
$ ./greeter_client (in a seperate terminal window)

You will then be prompted to type a string and then number in the terminal where the greeter_server was executed.
The string and number should then be received by the client.

Design Decision:
================
The string and number could have been hardcoded into the greeter_server.cc file, or alternatively could have been read from a txt file in a directory in the repository. I thought it would be a bit more interactive and dynamic if the string and number could be entered at the command line.

Yet to implement a solution to send a file.
