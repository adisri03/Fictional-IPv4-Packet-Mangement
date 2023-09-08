# IPv4-Packets

What is IPv4 Packets?

IPv4 packets are the fundamental units of data transmitted over the Internet using the Internet Protocol version 4. They consist of a header and payload. The header contains information such as source and destination IP addresses, packet length, and other control details, while the payload carries the actual data being transmitted, such as web content or email messages. IPv4 packets are a core component of the global Internet's communication infrastructure, although they are gradually being replaced by the newer IPv6 protocol to accommodate the growing number of Internet-connected devices.




Part 1: Print the Fields and Payload of a WolfPack Network Packet

A function called print_packet_sf that takes a valid WolfPack network packet and prints its fields in hexadecimal format as specified. It also displays the payload as a string.

Part 2: Compute a Packet’s Checksum

In this part, given a WolfPack network packet with a missing Checksum field, the function should compute and return the packet's checksum without modifying the packet.

Part 3: Reconstruct a Message Sent as a Series of Packets

The reconstruct_sf function, which takes an array of WolfPack network packets, extracts the payloads, and writes the original transmitted data into a message buffer. The function should ignore packets with invalid checksums and ensure that the null-terminator is written correctly. It returns the number of payloads successfully written to the message buffer.

Part 4: Packetize a Message

The final part involves creating a function called packetize_sf. This function takes a null-terminated string message, divides it into payloads, and attaches these payloads to new WolfPack network packets. It handles memory allocation, sets packet fields like Fragment Offset and Checksum, and returns the number of packets created.

The assignment provides detailed specifications, including examples and edge cases, for each of these parts. It also emphasizes the use of malloc for dynamic memory allocation and ensures that functions adhere to specified guidelines. 

The assignment aims to enhances the understanding of byte-level computations, array manipulation, memory allocation using malloc, and working with a network packet format resembling IPv4.
