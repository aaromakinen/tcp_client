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

Output 1 seems to have the highest frequency with somthing like 12.5Hz, output
2 with 4Hz and output 3 with 2Hz aplitudes are from 0 to 5 and output 3 have
only 0.0 or 5.0 for output 1 and 2 these can be changed with udp command. The
frequencies are not necessarily accurate since there is an option to modify
some glitch probability as seen by checking all possibilities to send udp
commands, so there might be some "glitches" to make this not compleately
accurate I disassemblied the server binary in ghidra and since it was
unstripped I noticed function names which contained sine, triangle and square
so those are the "shapes" that the output values plot. Output plotting sine
wave, output 2 triangles (with x-axis) and output 3 squares (with x-axis).

## Problems
The udp command for changing frequency for output 1 (or 2) doesn't seem to have
affect even though the server confirms that the frequency has been changed. I
was unable to figure out the way to have these frequencies actually changed.
More studying of the disassembly could reveal the reason and mechanism to
achieve this but due to time constraints I'll not look into this more deeply.
