FROM ubuntu:18.04

# Install dev tools
RUN apt update && apt install g++-8 -y

RUN apt install clang-tidy-7 -y && \
    apt install clang-format-7 -y

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
