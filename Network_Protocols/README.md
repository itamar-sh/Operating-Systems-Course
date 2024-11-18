# Network Protocols

## Switch

## Router
The Router acts as the gateway between the local networks (LAN) and the internet (WAN).
It also handles the DHCP process for the local network devices.

## Assigning IP address - DHCP Protocol
When you first connect your computer to the network. The Router will assign an  IP address to your computer using DHCP, Dynamic Host Configuration Protocol.

DHCP protocol - It automatically assign an IP address and DNS server you your computer.

The protocol DHCP follow this steps:
1) The new computer asing a broadcast message called DHCP Discover. Which is basically ask for an IP address.
2) The DHCP server responds with DHCP Offer, which is an available IP address.
3) The new computer accepts send DHCP request to confirm the IP assignment.
4) The router then sends a DHCP acknoledment to finalize the process.

The DHCP server is located or on the Router on dedicated local server.

## Get IP address via domain name - DNS (Domain Name System)
Every time you want to connect with someone you need his IP address.
In many cases you have only domain name like google.com.

The DNS will give you when you sends a DNS query a response with the IP address of google.

The IP of the DNS server is configured on the router and provider by the Internet Service Provider.
Many companies have local DNS server that resolves names for the internal network and forwards external queries to public DNS servers.

IP addresses are unique in your LAN, and the router has a unique global IP given by the Internet Service Provider.

## Send packets to an IP - IP (Internet Protcol) and TCP (Transmission Control Protocol)
The overall process will deliver packets via those components:
Your Router, the local network, intermediate routers and the router of the target IP.

The protocols involved in sending a package are IP and TCP.
The IP - Internet Protocol is used to route the packets across networks.
The TCP - Transmission Control Protocol is for reliable communication.

Those are the steps:
1) Your computer uses ARP - Adderss Resolution Protocol - to find the MAC address of the router in your local network.
2) Your computer creates an IP packet and a TCP segment with the data, the meta data like port, source and destination IP,
3) The IP packet and the TCP segment are wrapped in an Ethernet frame, which have the global IP of the router and the MAC address of the Ethernet connect of the computer, also EtherType and CRC for error detection. The Ethernet frame is sent to your router.
4) The Router send the Ethernet frame to the next Router and this process continues across the internet. There is a destination IP in the Ethernet frame.

What is exactly sent is: electrical signals in wired networks, or radio waves in wireless networks (Wi-Fi). Also there are fiber optics that send the data via light pulses.

## Find the target IP address accross the Internet. BGP (Border Gateway) and OSPF(Open Shortest Path First)
How some router knows where the target router related to target IP address is located?

Follow up question: What are those protocols? How you communicate them?

## Process the response from the remote IP.
HTTP (Hypertext Transfer Protocol) for web applications.

FTP (File Transfer Protocol).


NFS


------------------

SCTP

Ethernet

Wi-Fi

PPP

HDLC

OSPF

BGP

RIP

NetFlow