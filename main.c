#include <stdio.h>
#include <stdlib.h>

typedef unsigned char vc_uint8;
typedef unsigned short int vc_uint16;
typedef unsigned long int vc_uint32;

void dump_mem(vc_uint8 *str, vc_uint8 *ptr, vc_uint32 len);
vc_uint8 dmaTxBuff[512];
vc_uint8 pktBuff[512];
typedef struct neotest{
    vc_uint32 neo1;
    vc_uint32 neo2;
    vc_uint32 neo3;
}neotest;
typedef struct dmaPkt{
    vc_uint8 ptr[512];
    vc_uint16 ptrLen;
}dmaPkt;
void dump_mem(vc_uint8 *str, vc_uint8 *ptr, vc_uint32 len)
{
	vc_uint32 i;
	printf("%s\r\n",str);
	printf("======================\r\n");
	for(i=0;i<len;i++){
		printf("%02X ",ptr[i]);
	}
	printf("\r\n");
	printf("======================\r\n");	

}
void txBuf_Init(dmaPkt *pkt)
{
	vc_uint16 i;
	for(i=0;i<512;i++){
		pkt->ptr[i]=0x00;
	}
	pkt->ptrLen = 0;
	
}
void txBuf_Attach(dmaPkt *pkt, vc_uint8 *ptr, vc_uint16 len)
{
	vc_uint16 i;
	for(i=0;i<len;i++){		
		pkt->ptr[pkt->ptrLen + i] = ptr[i];
		printf("%d,%d=>%02X\r\n",pkt->ptrLen, i, pkt->ptr[pkt->ptrLen + i]);
	}	
	pkt->ptrLen+=len;
	//dump_mem(ptr, len);
}
int main()
{
	dmaPkt *pkt = NULL;
	neotest *neoPtr=NULL;
	neotest neo2;
	
	neoPtr = malloc(sizeof(neotest));	
	neoPtr->neo2 = 0xFFEEAABB;
	neoPtr->neo3 = 0x11223344;
	neoPtr->neo1 = 0x66554433; 
	neo2.neo2 = 0x11111111;
	neo2.neo3 = 0x22222222;
	neo2.neo1 = 0x33333333;
	
	pkt = &dmaTxBuff;//malloc(sizeof(dmaPkt));
	txBuf_Init(pkt);
	txBuf_Attach(pkt, neoPtr, sizeof(neotest));
	txBuf_Attach(pkt, &neo2, sizeof(neotest));
	printf("\r\n");
	dump_mem("pkt:",pkt->ptr, pkt->ptrLen);
	//memcpy(dmaTxBuff, pkt->ptr, pkt->ptrLen);	
	//dump_mem("dma:",dmaTxBuff, pkt->ptrLen);	
	/*
	fc.sof_STEI = ((STEI & 0x0FF0)>>4)| ((STEI & 0x000F)<<8);
    	fc.sof_DTEI = ((DTEI & 0x0F00)>>8)| ((DTEI & 0x00FF)<<4);
	*/
	return 0;
}

