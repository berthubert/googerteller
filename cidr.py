#!/usr/bin/env -S python3 -u
import sys
from ipaddress import ip_network, ip_address

nets = []
with open("goog-prefixes.txt") as f:
    nets = [line.strip() for line in f.readlines()]

for line in iter(sys.stdin.readline, ''):
    line = line.strip()
    for net in nets:
        try:
            if ip_address(line) in ip_network(net):
                print(line)

                continue
        except:
            continue
