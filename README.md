# WolfPack Network Protocol

![WolfPack Logo](wolfpack_logo.png)

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Part 1: Print the Fields and Payload of a WolfPack Network Packet](#part-1-print-the-fields-and-payload-of-a-wolfpack-network-packet)
  - [Part 2: Compute a Packet's Checksum](#part-2-compute-a-packets-checksum)
  - [Part 3: Reconstruct a Message Sent as a Series of Packets](#part-3-reconstruct-a-message-sent-as-a-series-of-packets)
  - [Part 4: Packetize a Message](#part-4-packetize-a-message)
- [Contributing](#contributing)
- [License](#license)

## Overview

This repository contains an implementation of the WolfPack network protocol, a fictional network protocol with specific packet formatting and processing requirements. The assignment includes four main parts, each implemented in its respective source file:

1. `print_packet_sf.c`: Printing the fields and payload of a WolfPack network packet.
2. `checksum_sf.c`: Computing a packet's checksum.
3. `reconstruct_sf.c`: Reconstructing a message sent as a series of WolfPack packets.
4. `packetize_sf.c`: Packetizing a message into WolfPack packets.

Please follow the instructions below to get started and use these functions.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C compiler (e.g., GCC)
- Git (for cloning the repository)

### Installation

1. Clone the repository to your local machine:

```bash
git clone https://github.com/your-username/wolfpack-network-protocol.git
