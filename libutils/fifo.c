/*
 * This file is just for study and part from FFmpeg.
 *
 * a very simple circular buffer FIFO implementation
 */


#include "fifo.h"
#define STMIN(a,b) ((a) > (b) ? (b) : (a))
static STfifoBuffer *fifo_alloc_common(void *buffer, size_t size)
{
    STfifoBuffer *f;
    if (!buffer)
        return NULL;
    f = (STfifoBuffer *)malloc(sizeof(STfifoBuffer));
    if (!f) {
        free(buffer);
        return NULL;
    }
    f->buffer = buffer;
    f->end    = f->buffer + size;
    st_fifo_reset(f);
    return f;
}

STfifoBuffer *st_fifo_alloc(unsigned int size)
{
    void *buffer = malloc(size);
    return fifo_alloc_common(buffer, size);
}

void st_fifo_free(STfifoBuffer *f)
{
    if (f) {
        free(&f->buffer);
        free(f);
    }
}

void st_fifo_reset(STfifoBuffer *f)
{
    f->wptr = f->rptr = f->buffer;
    f->wndx = f->rndx = 0;
}

int st_fifo_size(const STfifoBuffer *f)
{
    return (uint32_t)(f->wndx - f->rndx);
}

int st_fifo_space(const STfifoBuffer *f)
{
    return f->end - f->buffer - st_fifo_size(f);
}


/* src must NOT be const as it can be a context for func that may need
 * updating (like a pointer or byte counter) */
int st_fifo_write(STfifoBuffer *f, void *src, int size)
{
    int total = size;
    uint32_t wndx= f->wndx;
    uint8_t *wptr= f->wptr;

    do {
        int len = STMIN(f->end - wptr, size);
        memcpy(wptr, src, len);
        src = (uint8_t *)src + len;
        // Write memory barrier needed for SMP here in theory
        wptr += len;
        if (wptr >= f->end)
            wptr = f->buffer;
        wndx    += len;
        size    -= len;
    } while (size > 0);
    f->wndx= wndx;
    f->wptr= wptr;
    return total - size;
}


int st_fifo_read(STfifoBuffer *f, void *dest, int buf_size,
                         void (*func)(void *, void *, int))
{
    // Read memory barrier needed for SMP here in theory
    do {
        int len = STMIN(f->end - f->rptr, buf_size);
        memcpy(dest, f->rptr, len);
        dest = (uint8_t *)dest + len;
        // memory barrier needed for SMP here in theory
        st_fifo_drain(f, len);
        buf_size -= len;
    } while (buf_size > 0);
    return 0;
}

/** Discard data from the FIFO. */
void st_fifo_drain(STfifoBuffer *f, int size)
{
    f->rptr += size;
    if (f->rptr >= f->end)
        f->rptr -= f->end - f->buffer;
    f->rndx += size;
}
