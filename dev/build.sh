#!/bin/bash
# Author Producks 9/9/2023

nasm -felf64 $1.s && ld $1.o && ./a.out