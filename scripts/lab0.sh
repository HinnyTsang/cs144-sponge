#!/bin/bash

# Run the webget
./apps/webget cs144.keithw.org /hello &

# Run test for the webget
make check_webget

# Run test for lab 0
make check_lab0