#!/bin/bash
sudo ip tuntap add mode tun $1
sudo ip link set $1 up
sudo ip addr add $2 dev $1
