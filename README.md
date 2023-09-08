# WolfPack Network Protocol

![C](https://img.shields.io/badge/C%2B-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## Table of Contents

- [Overview](#overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## Overview

This repository contains an implementation of the WolfPack network protocol, a fictional network protocol with specific packet formatting and processing requirements. The assignment includes four main parts, each implemented in its respective source file:

1. Print WolfPack packet fields and payload.
2. Compute and return packet checksum.
3. Reconstruct messages from packets with validation.
4. Divide messages into WolfPack packets.

Please follow the instructions below to get started and use these functions.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C compiler (e.g., GCC)
- Git (for cloning the repository)

## Usage

1. Clone the repository to your local machine:
```bash
git clone https://github.com/your-username/wolfpack-network-protocol.git
```
2. Navigate to the Project Directory:
```bash
cd wolfpack-assignment
```
3. Compile the Code:
```bash
  make 
```
4. Run the Tests:
```bash
  make test
```
5. Memory Leak Detection (Optional):
```bash
make valgrind
```




