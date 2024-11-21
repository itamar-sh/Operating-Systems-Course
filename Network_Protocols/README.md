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


# Components of a TCP Segment
A TCP segment consists of:

1) Source Port (16 bits): The sender's port.

2) Destination Port (16 bits): The receiver's port.

3) Sequence Number (32 bits): The position of the first byte of data in the segment relative to the start of the data stream.

4) Acknowledgment Number (32 bits): The next byte the sender expects from the receiver.

5) Data Offset (4 bits): Size of the TCP header in 32-bit words.

6) Reserved (6 bits): Reserved for future use, set to zero.

7) Flags (6 bits): Control flags like SYN, ACK, FIN, etc.

8) Window Size (16 bits): Amount of data the receiver can accept.

9) Checksum (16 bits): Used to detect corruption.

10) Urgent Pointer (16 bits): Indicates the end of urgent data if the URG flag is set.

11) Options (variable): Additional configurations like Maximum Segment Size (MSS).

12) Payload/Data (variable): The actual data being transmitted.


# What Happens During the TCP Handshake?

The three-way handshake involves these steps:

1) SYN (Sender → Receiver): The sender sends a synchronization (SYN) packet to initiate communication, including an initial sequence number.

2) SYN-ACK (Receiver → Sender): The receiver responds with an acknowledgment (ACK) of the SYN, along with its own SYN packet and sequence number.

3) ACK (Sender → Receiver): The sender acknowledges the receiver’s SYN-ACK with its own ACK.

Synchronization (SYN) Packet:

    A SYN packet is the first step in the TCP three-way handshake.
    It initiates a connection between a sender and a receiver.
    The packet includes:
        SYN flag set to 1 (indicating this is a synchronization request).
        An Initial Sequence Number (ISN): A randomly chosen number that represents the starting point for the sender’s sequence numbers in the data stream. This randomness helps prevent certain attacks, like replay attacks.

Acknowledgment of the SYN:

    The receiver responds with a SYN-ACK packet:
        SYN flag set to 1 (indicating its synchronization request).
        ACK flag set to 1 (acknowledging the sender's SYN packet).
        Acknowledgment Number: This is the sender’s ISN incremented by 1, signaling that the receiver is ready to proceed with the next sequence number.
    The sender responds with an ACK packet, confirming receipt of the SYN-ACK and completing the handshake.



# How Do We Check if a TCP Segment is Corrupted?
The checksum field in the TCP header detects corruption.
The sender computes a checksum for the TCP segment (header + data + pseudo-header).
The receiver recomputes the checksum and compares it with the transmitted checksum.
If they don’t match, the segment is considered corrupted and discarded.

# How Do We Know if All TCP Segments Were Received?
TCP uses sequence numbers and acknowledgments to track data delivery.
The sender numbers each byte in the data stream.
The receiver acknowledges the highest byte received in order using the Acknowledgment Number.
If a segment is missing (sequence gap), the receiver waits or requests retransmission via duplicate ACKs or a timeout.

# How Do We Know the Source of a TCP Segment?
The source IP address in the IP header indicates where the packet originated.
The source port in the TCP header specifies the sending application or process on that machine.
Together with the destination IP address and destination port, the 4-tuple uniquely identifies the connection.

# What is a VPN?

A Virtual Private Network (VPN) is a technology that creates a secure and encrypted connection over a less secure network, typically the internet. It allows users to send and receive data as if their devices were directly connected to a private network, even if they are on a public or untrusted network (like the internet). This is commonly used to protect data privacy, secure internet traffic, and access geographically restricted content.
How Does a VPN Work?

A VPN works by creating a tunnel between your device (client) and a remote server (VPN server), ensuring that your internet traffic is encrypted and secure as it travels over the internet. Here’s how it works step-by-step:

Client Connection:
        The user connects to the internet, usually through a local, untrusted network (e.g., public Wi-Fi).
        The VPN software on the client device (such as a laptop or smartphone) initiates a connection to a VPN server.

Authentication:
        The client and the server authenticate each other to verify that they are legitimate. This is typically done using usernames, passwords, or encryption keys.

Encryption:
        Once the connection is established, all data between the client and the VPN server is encrypted. This means that even if a third party (such as a hacker) intercepts the data, they will not be able to read it without the encryption key.

Tunneling:
        The encrypted data is transmitted over the internet within a secure VPN tunnel. A tunnel is a secure pathway created by encryption protocols, such as OpenVPN, L2TP, or IPsec, that ensures the data cannot be tampered with or intercepted during transmission.

Data Routing:
        Once the encrypted data reaches the VPN server, it is decrypted and sent to its final destination (e.g., a website or web service). This step makes the data appear as if it’s coming from the VPN server, not the client device, which hides the client’s real IP address and location.

Response:
        The website or service responds to the VPN server, and the VPN server encrypts the response before sending it back to the client.
        The client decrypts the response and displays the content to the user.


## Which protocols are above (not used by) TCP and UDP.

## Why we use UDP and not simply IP? What fields it contains?

## Explain to me what is IP? What fields it contains?

## DHCP?

## When we use array and when LInked list? THere is any advantages in memory?

## When we use HAsh map and when binary search tree? Give me data strucutre that auto balance binary search tree? AVL?

## TCP API? file API?

## socket api?

## 3 rules for good hash func?

# HOw we allocate shared memory?


# what is a signal? when we use it? examples when we use it?

# what is system call? when we use it?







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