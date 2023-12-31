#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "wolfpack.h"

unsigned long extractSrcAdd(const unsigned char *packet){
    unsigned long srcAdd=0;
    for(int i = 0;i<5;i++){
        int shift=8;
        long temp = *packet;
        srcAdd = srcAdd << shift;
        srcAdd |= temp;
        
        
        packet++;
    }
    return srcAdd;
}
unsigned long extractDesAdd(const unsigned char *packet){
    unsigned long desAdd=0;
    packet += 5;
    for(int i = 0;i<5;i++){
        int shift=8;
        long temp = *packet;
        desAdd = desAdd << shift;
        desAdd |= temp;
    
        packet++;
    }
    return desAdd;

}
unsigned long extractSrcPort(const unsigned char *packet){
    unsigned long srcPort=0;
    packet += 10;
    for(int i = 0;i<1;i++){
       int shift=8;
        long temp = *packet;
        srcPort = srcPort << shift;
        srcPort |= temp;
    
        packet++;
    }

    return srcPort;

}
unsigned long extractDesPort(const unsigned char *packet){
    unsigned long desPort=0;
    packet+=11;
    for(int i = 0;i<1;i++){
        int shift=8;
        long temp = *packet;
        desPort = desPort << shift;
        desPort |= temp;
    
        packet++;
    }
    return desPort;
}
unsigned long extractFragOff(const unsigned char *packet){
    unsigned long fragOff=0;
    packet+=12;
    for(int i = 0;i<3;i++){
        int shift=8;
        long temp = *packet;
        fragOff = fragOff << shift;
        fragOff |= temp;
    
        packet++;
    }
    return fragOff;
}
unsigned long extractFlags(const unsigned char *packet){
    unsigned long flags=0;
    packet+=15;
   for(int i = 0;i<2;i++){
         int shift=8;
        long temp = *packet;
        flags = flags << shift;
        flags |= temp;
    
        packet++;
    }
    return flags;
}
unsigned long extractTotalLength(const unsigned char *packet){
    unsigned long totalLength=0;
    packet+=17;
    for(int i = 0;i < 3;i++){
        int shift=8;
        long temp = *packet;
        totalLength = totalLength << shift;
        totalLength |= temp;
    
        packet++;
    }
    return totalLength;
}
unsigned long extractCheckSum(const unsigned char *packet){
    unsigned long checkSum=0;
    packet+=20;
    for(int i = 0;i<4;i++){
        int shift=8;
        long temp = *packet;
        checkSum = checkSum << shift;
        checkSum |= temp;
    
        packet++;
    }
    return checkSum;

}
void print_packet_sf(const unsigned char *packet) {
    
    unsigned long totalLength=extractTotalLength(packet);
    
    printf("%010lx\n",extractSrcAdd(packet));
    printf("%010lx\n",extractDesAdd(packet));
    printf("%02lx\n",extractSrcPort(packet));
    printf("%02lx\n",extractDesPort(packet));
    printf("%06lx\n",extractFragOff(packet));
    printf("%02lx\n",extractFlags(packet));
    printf("%06lx\n",extractTotalLength(packet));
    printf("%08lx\n",extractCheckSum(packet));
    packet = packet+24;
    for(long unsigned i =0; i < totalLength-24;i++){
        printf("%c",*packet);
        packet++;
    }
    printf("\n");    
}
unsigned int packetize_sf(const char *message, unsigned char *packets[], unsigned int packets_len, unsigned int max_payload, unsigned long src_addr, unsigned long dest_addr, unsigned short flags) {
    size_t messageLen = strlen(message);
	unsigned int numPackets = (messageLen + max_payload - 1) / max_payload;
	unsigned int headerSize = 24;

	if (numPackets > packets_len) {
		numPackets = packets_len;
		messageLen = numPackets * max_payload;
	}
	unsigned int payloadIdx = 0;
	for (unsigned int i = 0; i < numPackets; i++) {
		unsigned int payloadSize = max_payload;
		if (payloadIdx + payloadSize > messageLen) {
			payloadSize = messageLen - payloadIdx;
		}
		packets[i] = malloc(headerSize + payloadSize);
		if (packets[i] == NULL) {
			return i;
		}
        //srcAdd
        unsigned long tempSrcAddr = src_addr;
       for(int j = 4; j>=0,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }
    
        //destAdd
        unsigned long tempDestAddr = dest_addr;
       for(int j = 9; j>=5,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }

        //srcPort
        packets[i][10]=32;

        //destPort
        packets[i][11]=64;

        //fragOff
        unsigned long tempIdx= payloadIdx;
      for(int j = 14; j>=12,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }

        //flag
        unsigned int tempFlags = flags;
        for(int j = 16; j>=15,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }

        //totalLength
        unsigned long tempSize = payloadSize + headerSize;
        for(int j = 19; j>=17,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }
       

        //checksum
        unsigned int tempChecksum = checksum_sf(packets[i]);
        for(int j = 23; j>=20,j--){
            packets[i][j]=tempChecksum&0xff;
            tempChecksum>>=8;
        }
    
        memcpy(&packets[i][headerSize].&message[payloadIdx], payloadSize)
		payloadIdx += payloadSize;  
	}
	return numPackets;
}
unsigned int checksum_sf(const unsigned char *packet) {
    unsigned long sum = extractSrcAdd(packet)+extractDesAdd(packet)+extractSrcPort(packet)+extractDesPort(packet)+extractFragOff(packet)+extractFlags(packet)+extractTotalLength(packet);
    sum %= (1ull << 32) - 1;
    return sum;
}
unsigned int reconstruct_sf(unsigned char *packets[], unsigned int packets_len, char *message, unsigned int messageLen) {
    unsigned int payloadsWritten = 0;
    unsigned int lastPosition = 0;
    for (unsigned int i = 0; i < packets_len; i++) {
        unsigned char *packet = packets[i];
        
         if(checksum_sf(packet) != extractCheckSum(packet)){
           continue;
        }
        unsigned long fragmentOffset = extractFragOff(packet);
        unsigned long payloadLength = extractTotalLength(packet)-24;
        if (fragmentOffset >= messageLen-1) {
           continue;
        }
        if (fragmentOffset + payloadLength > messageLen) {
            payloadLength = messageLen - fragmentOffset;
        }
        for (long unsigned j = 0; j < payloadLength; j++) {
            message[fragmentOffset + j] = packet[24 + j];
        }
        if (fragmentOffset + payloadLength > lastPosition) {
            lastPosition = fragmentOffset + payloadLength;
        }
        payloadsWritten++;
    }
    if (lastPosition < messageLen) {
        message[lastPosition] = '\0';
    } else {
        message[messageLen - 1] = '\0';
    }

    return payloadsWritten;
}
