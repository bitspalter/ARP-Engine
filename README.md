# ARP-Engine (alpha)

1. compile:
g++ *.cpp -std=c++11 -o ARP-Engine `pkg-config gtkmm-3.0 --cflags --libs`

2. set right to open raw socket and set promiscuous mode as non root:
setcap cap_net_raw,cap_net_admin=eip ./ARP-Engine

![alt tag](https://github.com/bitspalter/ARP-Engine/blob/master/ARP-Engine.png "ARP-Engine")
