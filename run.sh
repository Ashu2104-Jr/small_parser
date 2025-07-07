#!/bin/bash

gcc error.c
./a.out
aarch64-linux-gnu-as -mcpu=cortex-a57 -g ans.s -o ans.o
aarch64-linux-gnu-ld -o ans ans.o
qemu-aarch64 ./ans
echo output = $?

