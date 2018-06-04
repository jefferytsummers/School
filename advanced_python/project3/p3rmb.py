#!/usr/bin/env python3

import sys

import p3mod


gen = p3mod.find_start_positions()
gen.send(None)   # prime the generator

with open(sys.argv[1]) as f:
    for line in f:
        (seqid,seq) = line.strip().lower().split()
        slocs = gen.send(seq)
        print(seqid,slocs,"\n")
