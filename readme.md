# Embedded Linux Homework Task

## Preparation

Load the Docker image you have received:
```
docker load < fsw-linux-homework.tar.gz
```

Run it:
```
docker run -p 4000:4000/udp -p 4001:4001 -p 4002:4002 -p 4003:4003 fsw-linux-homework
```

The Docker image contains a server application that exposes three TCP ports
(4001, 4002, 4003) and produces data on them. Additionally, the server operates
a "control channel" by listening for messages on UDP port 4000 and reacting to
them.


## Task 1

Your first task is to write a program that reads data from all three TCP ports
and prints it to standard output. The program must be written in C, and the
executable must be named `client1`.

The program must output a line every 100 milliseconds. Each line should be
a JSON object with four key-value pairs: `timestamp`, `out1`, `out2`, and
`out3`. Do not aggregate objects into an array. Do not print anything else to
STDOUT.

The values for `out1`, `out2`, and `out3` should be the strings received from
server ports 4001, 4002, and 4003, respectively. The timestamp should represent
the number of milliseconds since the Unix epoch.

If no value is received from a server port within a given 100ms period, the
value for that port should be `"--"`.

Should your program receive multiple values from a port within a 100ms window,
there's no need to aggregate these values. Simply print the most recent value
received from the port in that 100ms period.

Example output:


```
{"timestamp": 1709286246830, "out1": "-4.8", "out2": "8.0", "out3": "--"}
{"timestamp": 1709286246930, "out1": "-4.0", "out2": "--",  "out3": "1.0"}
{"timestamp": 1709286247030, "out1": "-2.9", "out2": "1.2", "out3": "--"}
{"timestamp": 1709286247130, "out1": "-1.5", "out2": "--",  "out3": "--"}
...
{"timestamp": 1709286257730, "out1": "5.0",  "out2": "--",  "out3": "2.5"}
{"timestamp": 1709286257830, "out1": "4.8",  "out2": "5.0", "out3": "--"}
{"timestamp": 1709286257930, "out1": "4.0",  "out2": "--",  "out3": "--"}

```

What are the frequencies, amplitues and shapes you see on the server outputs?
Answer these questions in your `readme.md`.


## Task 2

Your second task is to write a program that controls the server's behavior:

* When the value on the output 3 of the server becomes greater than or equal 3.0:
    * Set the frequency of server output 1 to 1Hz.
    * Set the amplitude of server output 1 to 8000.

* When the value on the output 3 becomes lower than 3.0:
    * Set the frequency of server output 1 to 2Hz.
    * Set the amplitude of server output 1 to 4000.

Additionally, this second program should retain the same functionality as the
first one, which is to print values read from the server to the standard
output. However, there is one modification: it should operate using 20ms time
windows instead of 100ms ones.

The program must be written in C, and the executable must be named `client2`.


## Control Protocol

The control protocol adheres to the following specifications:

* The protocol is binary.
* Messages are structured into fields.
* Each field has a width of 16 bits.
* Field should be interpreted as unsigned integers.
* The byte order is Big-Endian.
* The first field in each message specifies the "operation".

* Supported operations are:
    * `1` - read
    * `2` - write

* Each read message consists of three fields: operation, object, and property.
* Each write message consists of four fields: operation, object, property, and value.

While the server does not send any response to the messages received from a
client, it does output information to standard output.


## Submission Instructions

Publish your solution on GitHub or a similar platform. This will allow us to
obtain it using `git clone`. Do not use the name "ICEYE" anywhere in the
repository.

Your submission should include a build system enabling us to compile your
programs with `make client1` and `make client2`. Both programs must be
compatible with x86_64 Linux systems, and they must not depend on any
third-party libraries, other than the standard C library.

If you make any auxiliary tools to support your solution, please include them
in your repository as well. Third party dependencies are allowed here, provided
they are built or executed from source code, and integrated into your build system.
You can make reasonable assumptions though. Your build system doesn't need to
build from source the standard POSIX tools, or other programs commonly installed on
GNU/Linux :)

Please provide a complete commit history, so that we can see how you arrived at
the final solution.

Please also provide a `readme.md` file. Document your design decisions, and
explain how your solution works. How do you know the solution is correct?

The solution must be submitted within seven working days of receiving the
instructions. If there are mediating circumstances that cause a delay, please
contact us and inform us in advance.

If you have any questions about the nature of the task, feel free to contact
us. 

Don’t hesitate to send us your results even if you don’t manage to finish
the task in its full scope.

Have fun coding and good luck! 

