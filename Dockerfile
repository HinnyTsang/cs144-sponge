FROM ubuntu:18.04

# Install dev tools
RUN apt update && apt install g++-8 -y && \
    cp /usr/bin/g++-8 /usr/bin/g++

RUN apt install clang-tidy-7 -y && \
    apt install clang-format-7 -y && \
    cp /usr/bin/clang-tidy-7 /usr/bin/clang-tidy && \
    cp /usr/bin/clang-format-7 /usr/bin/clang-format

RUN apt install cmake -y && \
    apt install libpcap-dev -y

# Install connection tools
RUN apt install iptables -y && \
    apt install mininet -y && \
    apt install tcpdump -y && \
    apt install telnet -y && \
    apt install wireshark -y && \
    apt install socat -y && \
    apt install netcat-openbsd -y

RUN apt install coreutils -y && \
    apt install doxygen -y &&\
    apt install graphviz -y
