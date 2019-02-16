/*
 * This file is just for study and part from FFmpeg.
 *
 * a very simple circular buffer FIFO implementation
 */

#ifndef ST_FIFO_H
#define ST_FIFO_H

#include <stdint.h>

typedef struct __FifoBuffer {
    uint8_t *buffer;
    uint8_t *rptr, *wptr, *end;
    uint32_t rndx, wndx;
} STfifoBuffer;

/**
 * Initialize an STfifoBuffer.
 * @param size of FIFO
 * @return STfifoBuffer or NULL in case of memory allocation failure
 */
STfifoBuffer *stfifo_alloc(unsigned int size);

/**
 * Free an STfifoBuffer.
 * @param f STfifoBuffer to free
 */
void sb_fifo_free(STfifoBuffer *f);

/**
 * Reset the STfifoBuffer to the state right after sb_fifo_alloc, in particular it is emptied.
 * @param f STfifoBuffer to reset
 */
void sb_fifo_reset(STfifoBuffer *f);

/**
 * Return the amount of data in bytes in the STfifoBuffer, that is the
 * amount of data you can read from it.
 * @param f STfifoBuffer to read from
 * @return size
 */
int sb_fifo_size(const STfifoBuffer *f);

/**
 * Return the amount of space in bytes in the STfifoBuffer, that is the
 * amount of data you can write into it.
 * @param f STfifoBuffer to write into
 * @return size
 */
int sb_fifo_space(const STfifoBuffer *f);

/**
 * Feed data from an STfifoBuffer to a user-supplied callback.
 * @param f STfifoBuffer to read from
 * @param buf_size number of bytes to read
 * @param func generic read function
 * @param dest data destination
 */
int sb_fifo_read(STfifoBuffer *f, void *dest, int buf_size);

/**
 * Feed data from a user-supplied callback to an STfifoBuffer.
 * @param f STfifoBuffer to write to
 * @param src data source; non-const since it may be used as a
 * modifiable context by the function defined in func
 * @param size number of bytes to write
 * @param func generic write function; the first parameter is src,
 * the second is dest_buf, the third is dest_buf_size.
 * func must return the number of bytes written to dest_buf, or <= 0 to
 * indicate no more data available to write.
 * If func is NULL, src is interpreted as a simple byte array for source data.
 * @return the number of bytes written to the FIFO
 */
int sb_fifo_write(STfifoBuffer *f, void *src, int size);

/**
 * Read and discard the specified amount of data from an STfifoBuffer.
 * @param f STfifoBuffer to read from
 * @param size amount of data to read in bytes
 */
void sb_fifo_drain(STfifoBuffer *f, int size);

#endif /* ST_FIFO_H */
