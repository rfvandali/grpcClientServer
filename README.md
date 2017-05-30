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

You will then be prompted to type a string and then a number (specifically an int) in the terminal where the greeter_server was executed.
The string and number should then be received by the client and printed to screen.

Design Decision:
================
* The string and number could have been hardcoded into the greeter_server.cc file, or alternatively could have been read from a txt file in a directory in the repository. I thought it would be a bit more interactive and dynamic if the string and number could be entered at the command line.
* There are numerous ways we might want our system to behave upon received the number input. The way it has been defined here:
    - An input starting with a non numerical character is rejected and re-prompted for input
    - Any numbers seperated by a non numeric character (i.e. a '.' or abcde...etc) are ignored and the initial numeric portion accepted


This application does not implement a solution to send a file.
