## Introduction
This project is to listen tcp ports where data is being sent by known
server program. Server program also has control channel that is managed by
sending commands by udp

## Implementation
Program is quite simple and code self explanatory but roughly the flow goes
from initializing the tcp and udp sockets to main loop. We keep the sockets
open during the execution since there should be no concurrent users for the
server. Main loop reads the package from tcp sockets with frequency that is
defined by the caller and in case our parsed value for out3 (port 4003)
indicates other mode to be used, we send udp command to modify the server
behaviour.

Output 1 seems to have the highest frequency without modifying

## Problems

