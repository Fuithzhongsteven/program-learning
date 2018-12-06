/*
 * Copyright (c) 2012, The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Google, Inc. nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

#define	TX_BUF_MAX_LEN (((240)*(320)*(4))	 + ((240)*(320)*(4)/(8)) + 128)
static unsigned int   spi_send_len;
static unsigned char *p_tx_buf;       
static unsigned char *p_spi_send_buf;

typedef unsigned long long ull64;
typedef unsigned int ul32;

#define swap_endian_64(x) (\
    (ull64)\
    (\
        (((ull64)(x)& (ull64)0x00000000000000ffULL) << 56) | \
        (((ull64)(x)& (ull64)0x000000000000ff00ULL) << 40) | \
        (((ull64)(x)& (ull64)0x0000000000ff0000ULL) << 24) | \
        (((ull64)(x)& (ull64)0x00000000ff000000ULL) << 8 ) | \
        (((ull64)(x)& (ull64)0x000000ff00000000ULL) >> 8 ) | \
        (((ull64)(x)& (ull64)0x0000ff0000000000ULL) >> 24) | \
        (((ull64)(x)& (ull64)0x00ff000000000000ULL) >> 40) | \
        (((ull64)(x)& (ull64)0xff00000000000000ULL) >> 56) \
    )\
)

#define swap_endian_32(x) (\
        (ul32)\
        (\
            (((ul32)(x)& (ul32)0x000000ff) << 24) | \
            (((ul32)(x)& (ul32)0x0000ff00) << 8 ) | \
            (((ul32)(x)& (ul32)0x00ff0000) >> 8 ) | \
            (((ul32)(x)& (ul32)0xff000000) >> 24)   \
        )\
)

// 0 0x2a 1 xsh 1 xsl 1 xeh 1 xel 0 0x2b 1 ysh 1 + ysl
//#define BIG_HEADER0_MASK    (000101010100000000100000000100000000100000000000101011100000001b)
#define BIG_HEADER0_MASK    (0xAA0100804005701ULL)
// 1 yeh 1 yel 0 0x2c 1 data0 1 data1 1 data2 1 data3 1 +data4
//#define BIG_HEADER1_MASK    (100000000100000000000101100000000001000000001000000001000000001b)
#define BIG_HEADER1_MASK    (0x402002C008040201ULL)
//pbits[0] |=  (1 YEH 1 YEL 0 nop 0 nop 0 nop 0 nop 0 nop 0);
//#define BIG_HEADER_NOP_MASK (100000000100000000000000000000000000000000000000000000000000000b)
#define BIG_HEADER_NOP_MASK (0x4020000000000000ULL)
//1 data0 1 data1 1 data2 1 data3 1 data4 1 data5 1 data6 1 + data7
//#define BIG_DATA_MASK       (100000000100000000100000000100000000100000000100000000100000001b)
#define BIG_DATA_MASK       (0x4020100804020101ULL)

static void fill_header_withnop(unsigned int x, unsigned int y,unsigned char* dst){
    unsigned char *px = (unsigned char *)(&x);
    unsigned char *py = (unsigned char *)(&x);
    ull64 *pbits = (ull64 *)dst;
    // (0 0x2a 1 xsh 1 xsl 1 xeh 1 xel 0 0x2b 1 ysh 1) + ysl
    pbits[0] |= BIG_HEADER0_MASK;
    pbits[0] |= (((ull64)((ull64)px[3]))<< 46)|(((ull64)((ull64)px[2]))<< 37)
        |(((ull64)((ull64)px[1]))<< 28)|(((ull64)((ull64)px[0]))<< 19)
        |(((ull64)((ull64)py[3]))<< 1);
    pbits[0] = swap_endian_64(pbits[0]);
    dst[8] = py[2];
    pbits = (ull64 *)(dst+9);
    //(1 YEH 1 YEL 0 nop 0 nop 0 nop 0 nop 0 nop 0)+0x2c;
    pbits[0] |= BIG_HEADER_NOP_MASK;
    pbits[0] |= (((ull64)((ull64)py[1]))<< 55)|(((ull64)((ull64)py[0]))<< 46);
    pbits[0] = swap_endian_64(pbits[0]);
    dst[17] = 0x2c;  
}
static void fill_data_withnop(unsigned int * src,unsigned char* dst){
    ull64 *pbits = (ull64 *)dst;
    unsigned char *p = (unsigned char *)src;
    //pbits[0] |=  (1 data0 1 data1 1 data2 1 data3 1 data4 1 data5 1 data6 1);
    pbits[0] |=  BIG_DATA_MASK;
    pbits[0] |= 
         (((ull64)((ull64)p[1]))<<55)|(((ull64)((ull64)p[0]))<<46)
        |(((ull64)((ull64)p[3]))<<37)|(((ull64)((ull64)p[2]))<<28)
        |(((ull64)((ull64)p[5]))<<19)|(((ull64)((ull64)p[4]))<<10)
        |(((ull64)((ull64)p[7]))<<1);
    pbits[0] = swap_endian_64(pbits[0]);
    dst[8] = p[6];
}

static int filling_spi_send_display_data1(void *data_buf, unsigned int len, unsigned int x, unsigned int y)
{
	unsigned int i;
	//unsigned int *p_buf = (unsigned int *)data_buf;   // we use short, as each pixel is represent by two byte
	int ret;
	unsigned char *psrc = (unsigned char *)data_buf;
    unsigned char *pdst = p_spi_send_buf;
    ull64 *pbits = (ull64 *)pdst;
    

	// len in 32bit, len*4, pure data; 
	// 12 0x2a, 4byte, 0x2b 4byte, 0x2c , 0x00  1+4+1+4+1+1
	i = (16 + len * 4 + 8) * 9;  
	spi_send_len = (i % 8)?(i / 8 + 1):(i / 8);
	if ((spi_send_len == 0) || (spi_send_len > TX_BUF_MAX_LEN)){
		return -1;
	}
	memset(pdst, 0, spi_send_len);
    
	pdst = p_spi_send_buf;
    fill_header_withnop(x, y,pdst);
    pdst += 18;
	for(i=0;i<len/2;i++){
        //pbits[0] |=  (1 data0 1 data1 1 data2 1 data3 1 data4 1 data5 1 data6 1);
        pbits[0] |=  BIG_DATA_MASK;
        pbits[0] |= 
             (((ull64)((ull64)psrc[1]))<<55)|(((ull64)((ull64)psrc[0]))<<46)
            |(((ull64)((ull64)psrc[3]))<<37)|(((ull64)((ull64)psrc[2]))<<28)
            |(((ull64)((ull64)psrc[5]))<<19)|(((ull64)((ull64)psrc[4]))<<10)
            |(((ull64)((ull64)psrc[7]))<<1);
        pbits[0] = swap_endian_64(pbits[i]);
        pdst[8] = psrc[6];
        psrc += 8;
        pdst += 9;
        pbits = (ull64 *)pdst;
    }
	return ret;
}

static int filling_spi_send_display_data2(void *data_buf, unsigned int len, unsigned int x, unsigned int y)
{
	unsigned int i;
	int ret;
	unsigned char *psrc = (unsigned char *)data_buf;
    unsigned char *pdst = p_spi_send_buf;

	// len in 32bit, len*4, pure data; 
	// 12 0x2a, 4byte, 0x2b 4byte, 0x2c , 0x00  1+4+1+4+1+1
	i = (16 + len * 4 + 8) * 9;  
	spi_send_len = (i % 8)?(i / 8 + 1):(i / 8);
	if ((spi_send_len == 0) || (spi_send_len > TX_BUF_MAX_LEN)){
		return -1;
	}
	memset(pdst, 0, spi_send_len);
    
    fill_header_withnop(x, y,pdst);
    pdst += 18;
    len = len/2;
	for(i=0;i<len;i++){
        // 1xxxxxxx x1xxxxxx xx1xxxxx xxx1xxxx 
        // xxxx1xxx xxxxx1xx xxxxxx1x xxxxxxx1
        pdst[0] = (unsigned char)(0x80|(psrc[1]>>1));
        pdst[1] = (unsigned char)(0x40|(psrc[0]>>2)|(psrc[1]<<7));
        pdst[2] = (unsigned char)(0x20|(psrc[3]>>3)|(psrc[0]<<6));
        pdst[3] = (unsigned char)(0x10|(psrc[2]>>4)|(psrc[3]<<5));
        pdst[4] = (unsigned char)(0x08|(psrc[5]>>5)|(psrc[2]<<4));
        pdst[5] = (unsigned char)(0x04|(psrc[4]>>6)|(psrc[5]<<3));
        pdst[6] = (unsigned char)(0x02|(psrc[7]>>7)|(psrc[4]<<2));
        pdst[7] = (unsigned char)(0x01|((psrc[7]<<1)));
        pdst[8] = (unsigned char)(psrc[6]);
        psrc += 8;
        pdst += 9;
    }
	return ret;
}

static inline void fill_header_withnop1(unsigned int x, unsigned int y,unsigned char* dst){
    unsigned char *px = (unsigned char *)(&x);
    unsigned char *py = (unsigned char *)(&y);
    unsigned char *pDst = dst;
    unsigned int *pbits = (unsigned int *)pDst;
    // (0 0x2a 1 xsh 1 xsl 1 xeh 1 xel 0 0x2b 1 ysh 1) + ysl
    // 00010101 01xxxxxx xx1xxxxx xxx1xxxx 
    // xxxx1xxx xxxxx000 1010111x xxxxxxx1 xxxxxxxx
    // 1xxxxxxx x1xxxxxx xx000000 00000000   
    // 00000000 00000000 00000000 00000000 00101100   
    pbits[0] = (((ul32)((ul32)px[3]))<<14)|(((ul32)((ul32)px[2]))<<5)
            |(((ul32)((ul32)px[1]))>>4)|(0x15402010);
    pbits[1] = (((ul32)((ul32)px[1]))<<28)|(((ul32)((ul32)px[0]))<<19)
            |(((ul32)((ul32)py[3]))<<1)|(0x0800ae01);
    pbits[0] = swap_endian_32(pbits[0]);
    pbits[1] = swap_endian_32(pbits[1]);
    pDst[8] = py[2];
    pDst += 9;
    pbits = (unsigned int *)(pDst);
    pbits[0] = (((ul32)((ul32)py[1]))<<23)|(((ul32)((ul32)py[0]))<<14)
            |(0x80400000);
    pbits[0] = swap_endian_32(pbits[0]);
    pbits[1] = 0x00000000;
    pDst[8] = 0x2c;
}

static int filling_spi_send_display_data3(void *data_buf, unsigned int len, unsigned int x, unsigned int y)
{
	unsigned int i;
	int ret;
	unsigned char *psrc = (unsigned char *)data_buf;
    unsigned char *pdst = p_spi_send_buf;
    unsigned int *pbits = (unsigned int *)pdst;

	// len in 32bit, len*4, pure data; 
	// 16 0x2a 4byte,0x2b 4byte,0x00,0x00,0x00,0x00,0x00,0x2c + 0x00 8bytes
	i = (16 + len * 4 + 8) * 9;  
	spi_send_len = (i % 8)?(i / 8 + 1):(i / 8);
	if ((spi_send_len == 0) || (spi_send_len > TX_BUF_MAX_LEN)){    
		return -1;
	}
	memset(pdst, 0, spi_send_len);
    
    fill_header_withnop1(x, y,pdst);
    pdst += 18;
    
    len = len/2;
	for(i=0;i<len;i++){
        // 1xxxxxxx x1xxxxxx xx1xxxxx xxx1xxxx 
        // xxxx1xxx xxxxx1xx xxxxxx1x xxxxxxx1
        pbits = (unsigned int *)pdst;
        pbits[0] = 
             (((ul32)((ul32)psrc[1]))<<23)|(((ul32)((ul32)psrc[0]))<<14)
            |(((ul32)((ul32)psrc[3]))<<5)|(((ul32)((ul32)psrc[2]))>>4)
            |(0x80402010);
        pbits[1] = 
             (((ul32)((ul32)psrc[2]))<<28)|(((ul32)((ul32)psrc[5]))<<19)
            |(((ul32)((ul32)psrc[4]))<<10)|(((ul32)((ul32)psrc[7]))<<1)
            |(0x08040201);    
        pbits[0] = swap_endian_32(pbits[0]);
        pbits[1] = swap_endian_32(pbits[1]);
        pdst[8] = psrc[6];
        psrc += 8;
        pdst += 9;
    }
	return ret;
}


static int filling_spi_send_display_data4(void *data_buf, unsigned int len, unsigned int x, unsigned int y)
{
	unsigned int i;
	int ret;
	unsigned char *psrc = (unsigned char *)data_buf;
    unsigned char *pdst = p_spi_send_buf;
    unsigned int *pbits = (unsigned int *)pdst;

	// len in 32bit, len*4, pure data; 
	// 16 0x2a 4byte,0x2b 4byte,0x00,0x00,0x00,0x00,0x00,0x2c + 0x00 8bytes
	i = (16 + len * 4 + 8) * 9;  
	spi_send_len = (i % 8)?(i / 8 + 1):(i / 8);
	if ((spi_send_len == 0) || (spi_send_len > TX_BUF_MAX_LEN)){    
		return -1;
	}
	memset(pdst, 0, spi_send_len);
    
    fill_header_withnop1(x, y,pdst);
    pdst += 18;
    
    len = len/2;
	for(i=0;i<len;i++){
        // xxx1xxxx xx1xxxxx x1xxxxxx 1xxxxxxx 
        // xxxxxxx1 xxxxxx1x xxxxx1xx xxxx1xxx 
        pbits = (unsigned int *)pdst;
        pbits[0] = 
             (((ul32)((ul32)psrc[1]))>>1)|(((ul32)(psrc[1]&0x01))<<15)
            |(((ul32)((ul32)(psrc[0]&0xfc)))<<6)|(((ul32)(psrc[0]&0x03))<<24)
            |(((ul32)(psrc[3]&0xf8))<<13)|(((ul32)(psrc[3]&0x07))<<29)
            |(((ul32)(psrc[2]&0xf0))<<20)
            |(0x10204080);
        pbits[1] = 
             (((ul32)(psrc[2]&0x0f))<<4)|(((ul32)(psrc[5]&0xe0))>>5)
            |(((ul32)((ul32)(psrc[5]&0x1f)))<<11)|(((ul32)(psrc[4]&0xc0))<<2)
            |(((ul32)(psrc[4]&0x3f))<<18)|(((ul32)(psrc[7]&0x80))<<9)
            |(((ul32)(psrc[7]&0xfe))<<25)
            |(0x01020408);    
        pdst[8] = psrc[6];
        psrc += 8;
        pdst += 9;
    }
	return ret;
}



static void get_u8_from_u32(unsigned char *buf, unsigned int in_data){
	buf[0] = (unsigned char)(in_data >> 24);
	buf[1] = (unsigned char)(in_data >> 16);
	buf[2] = (unsigned char)(in_data >> 8);
	buf[3] = (unsigned char)in_data;
}

static void write_lcm_command(unsigned char lcm_cmd, unsigned char *buf, unsigned int *bit_pos){
	unsigned int i, j;
	
	i = *bit_pos / 8;
	j = *bit_pos % 8;
	j = (j + 1) % 8;
	if (j == 0){
		i++;
		buf[i] = lcm_cmd;
	} else {
		buf[i] |= (unsigned char)(lcm_cmd >> j);
		i++;
		buf[i] |= (unsigned char)(lcm_cmd <<  (8 - j));	
	}
	*bit_pos += 9;
}
static void write_lcm_data(unsigned char lcm_data, unsigned char *buf, unsigned int *bit_pos){
	unsigned int i, j;
	
	i = *bit_pos / 8;
	j = *bit_pos % 8;
	
	buf[i] |= (unsigned char)(0x80 >> j);
	
	j = (j + 1) % 8;
	
	if (j == 0){
		i++;
		buf[i] = lcm_data;
	} else {
		buf[i] |= (unsigned char)(lcm_data >> j);
		i++;
		buf[i] |= (unsigned char)(lcm_data <<  (8 - j));	
	}
	
	*bit_pos += 9;
}


static int filling_spi_send_display_data(void *data_buf, unsigned int len, unsigned int x, unsigned int y){
	unsigned int b_pos, i, data_len;
	unsigned char temp_buf[4];
	unsigned char *p_tx_temp_buf;
	unsigned int *p_buf = (unsigned int *)data_buf;
	int ret;

	data_len = 0;
	b_pos = 0;
	p_tx_temp_buf = p_spi_send_buf;
	// len in 32bit, len*4, pure data; 
	// 16 0x2a 4byte,0x2b 4byte,0x00,0x00,0x00,0x00,0x00,0x2c + 0x00 8bytes
	i = (12 + len * 4) * 9;  
	spi_send_len = (i % 8)?(i / 8 + 1):(i / 8);
	if ((spi_send_len == 0) || (spi_send_len > TX_BUF_MAX_LEN))
	{
		return -1;
	}
	memset(p_tx_temp_buf, 0, spi_send_len);
	
	write_lcm_command(0x2A, p_tx_temp_buf, &b_pos);
	
	get_u8_from_u32(temp_buf, x);

	for (i = 0; i < 4; i++)
	{
		write_lcm_data(temp_buf[i], p_tx_temp_buf, &b_pos);
	}

	write_lcm_command(0x2B, p_tx_temp_buf, &b_pos);
	
	get_u8_from_u32(temp_buf, y);

	for (i = 0; i < 4; i++)
	{
		write_lcm_data(temp_buf[i], p_tx_temp_buf, &b_pos);
	}
	
	write_lcm_command(0x2C, p_tx_temp_buf, &b_pos);
	
	for (i = 0; i < len; i++){  // 4 byte 

		get_u8_from_u32(temp_buf, p_buf[i]);
		write_lcm_data(temp_buf[2], p_tx_temp_buf, &b_pos);
		write_lcm_data(temp_buf[3], p_tx_temp_buf, &b_pos);
		write_lcm_data(temp_buf[0], p_tx_temp_buf, &b_pos);
		write_lcm_data(temp_buf[1], p_tx_temp_buf, &b_pos);
	}
	
	write_lcm_command(0x00, p_tx_temp_buf, &b_pos);
	return ret;
}


static int isLittleEndian(){
    unsigned int sEndianDetector = 1;
    return (*((unsigned char *)&sEndianDetector));
}
static unsigned long long toBigEndian(unsigned long long data){
    if(isLittleEndian()){
        return swap_endian_64(data);    
    }else{
        return data;
    }
}

#define TEST_DATA_LEN 320*240/2
static unsigned int FrameBuff[TEST_DATA_LEN] = {0};

enum {
    SYSTEM_TIME_REALTIME = 0,  // system-wide realtime clock
    SYSTEM_TIME_MONOTONIC = 1, // monotonic time since unspecified starting point
    SYSTEM_TIME_PROCESS = 2,   // high-resolution per-process clock
    SYSTEM_TIME_THREAD = 3,    // high-resolution per-thread clock
    SYSTEM_TIME_BOOTTIME = 4   // same as SYSTEM_TIME_MONOTONIC, but including CPU suspend time
};

typedef long long nsecs_t;
nsecs_t getSystemTime()
{
    struct timespec t;
    t.tv_sec = t.tv_nsec = 0;
    clock_gettime(SYSTEM_TIME_MONOTONIC, &t);
    return (nsecs_t)((t.tv_sec)*1000000000LL + t.tv_nsec);
}

int main(int argc, char *argv[]) {
    nsecs_t startTime = 0,startTime1 = 0;
    nsecs_t now = 0;
    nsecs_t calltime = 0;
    int count = 60;
    int i = 0;
    
    unsigned long long endianLL = 0x12345678abcdef09ULL;
    unsigned char *p = (unsigned char *)(&endianLL);

    for(i=0;i<TEST_DATA_LEN;i++){
        FrameBuff[i] = 0x12345678;
    }
    p_tx_buf = (unsigned char *)malloc(TX_BUF_MAX_LEN);
    if(p_tx_buf == NULL){
        printf("no mem\n");
        return -1;
    }
    p_spi_send_buf = (unsigned char *)malloc(TX_BUF_MAX_LEN);
    if(p_spi_send_buf == NULL){
        printf("no mem\n");
        free(p_tx_buf);
        return -1;
    }
    printf("###################################################################\n");
    printf("sizeof ll: %d, sizeof l: %d, sizeof int: %d\n",
        sizeof(unsigned long long),
        sizeof(unsigned long),
        sizeof(unsigned int)
    );
    printf("###################################################################\n");
    printf("platform endian: %s\n endianLL = %llx \n endianLL char:0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n",
        (isLittleEndian())?"little endian":"big endian",
        endianLL,
        p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);
    endianLL = swap_endian_64(endianLL);
    printf("swapendian:0x%02x 0x%02x 0x%02x 0x%02x %02x 0x%02x 0x%02x 0x%02x\n",
        p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);
    printf("###################################################################\n");


    printf("###################################################################\n");
    startTime1 = getSystemTime();
    while(count--){
        //startTime = getSystemTime();
        filling_spi_send_display_data(FrameBuff, TEST_DATA_LEN, 239, 319);
        //now = getSystemTime();
        //printf("call send_display_data %02d used %lld nsecs\n", count, now-startTime);
    }
    now = getSystemTime();
    printf("call send_display_data av used %lld nsecs\n", (now-startTime1)/60);
    printf("###########################################\n");
    printf("spi_header:\n");
    for(i=0;i<18;i++){
        printf("0x%02x ",p_spi_send_buf[i]);
    }
    printf("\n");
    printf("spi_data:\n");
    for(i=0;i<TEST_DATA_LEN*4;i++){
        printf("0x%02x ",p_spi_send_buf[i+18]);
        if(i%16 == 0)printf("\n");
    }
    printf("\n");
    printf("###########################################\n");
    #if 0
    printf("###################################################################\n");
    count = 60;
    startTime1 = getSystemTime();
    while(count--){
        //startTime = getSystemTime();
        filling_spi_send_display_data1(FrameBuff, 320*240/2, 239, 319);
        //now = getSystemTime();
        //printf("call send_display_data1 %02d used %lld nsecs\n", count, now-startTime);
    }
    now = getSystemTime();
    printf("call send_display_data1 av used %lld nsecs\n", (now-startTime1)/60);
    
    printf("###################################################################\n");
    #endif

    #if 0
    printf("###################################################################\n");
    count = 60;
    startTime1 = getSystemTime();
    while(count--){
        //startTime = getSystemTime();
        filling_spi_send_display_data2(FrameBuff, 320*240/2, 239, 319);
        //now = getSystemTime();
        //printf("call send_display_data2 %02d used %lld nsecs\n", count, now-startTime);
    }
    now = getSystemTime();
    printf("call send_display_data2 av used %lld nsecs\n", (now-startTime1)/60);
    printf("###########################################\n");
    printf("spi_header:\n");
    for(i=0;i<18;i++){
        printf("0x%02x ",p_spi_send_buf[i]);
    }
    printf("\n");
    printf("spi_data:\n");
    for(i=0;i<TEST_DATA_LEN*4;i++){
        printf("0x%02x ",p_spi_send_buf[i+18]);
        if(i/%16 == 0)printf("\n");
    }
    printf("\n");
    printf("###########################################\n");  
    printf("###################################################################\n");
    #endif

    printf("###################################################################\n");
    count = 60;
    startTime1 = getSystemTime();
    while(count--){
        //startTime = getSystemTime();
        filling_spi_send_display_data3(FrameBuff, 320*240/2, 239, 319);
        //now = getSystemTime();
        //printf("call send_display_data3 %02d used %lld nsecs\n", count, now-startTime);
    }
    now = getSystemTime();
    printf("call send_display_data3 av used %lld nsecs\n", (now-startTime1)/60);
    printf("###########################################\n");
    printf("spi_header:\n");
    for(i=0;i<18;i++){
        printf("0x%02x ",p_spi_send_buf[i]);
    }
    printf("\n");
    printf("spi_data:\n");
    for(i=0;i<TEST_DATA_LEN*4;i++){
        printf("0x%02x ",p_spi_send_buf[i+18]);
        if(i%16 == 0)printf("\n");
    }
    printf("\n");
    printf("###########################################\n"); 
    printf("###################################################################\n");
    
    if(p_tx_buf)free(p_tx_buf);
    if(p_spi_send_buf)free(p_spi_send_buf);
    
    return 0;
}


