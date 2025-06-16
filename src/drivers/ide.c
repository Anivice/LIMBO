#include "ide.h"
#include "io.h"

#define IO_PORT 					((unsigned short)0x1F0)
#define IO_ERR_STATE 				((unsigned short)0x1F1)
#define IO_BLOCK_COUNT 				((unsigned short)0x1F2)
#define IO_LBA28_0_7 				((unsigned short)0x1F3)
#define IO_LBA28_8_15 				((unsigned short)0x1F4)
#define IO_LBA28_16_23 				((unsigned short)0x1F5)
#define IO_LBA28_24_27_W_4_CTRL 	((unsigned short)0x1F6)
#define IO_REQUEST_AND_STATE 		((unsigned short)0x1F7)
#define IO_READ 					((unsigned char)0x20)
#define IDE_DRQ 				    ((unsigned char)0x08)
#define IO_WRITE                    ((unsigned char)0x30)
#define IDE_DRQ                     ((unsigned char)0x08)
#define IDE_BSY                     ((unsigned char)0x80)
#define ATA_CMD_CACHE_FLUSH         ((unsigned char)0xE7)

void disk_read(char * buffer, const unsigned int sector, const unsigned char count)
{
    const unsigned char last_4bits_in_lba = (((char*)&sector)[3] & 0x0F) | 0xE0;
    unsigned char byte = 0;

    if (!count)
    {
        return;
    }

    out8(IO_BLOCK_COUNT, count);
    out8(IO_LBA28_0_7, ((char*)&sector)[0]);
    out8(IO_LBA28_8_15, ((char*)&sector)[1]);
    out8(IO_LBA28_16_23, ((char*)&sector)[2]);
    out8(IO_LBA28_24_27_W_4_CTRL, last_4bits_in_lba);
    out8(IO_REQUEST_AND_STATE, IO_READ);

    // read
    unsigned short ax = 0;
    for (unsigned int i = 0; i < count; i++)
    {
        // wait
        do {
            in8(IO_REQUEST_AND_STATE, &byte);
        } while (!(byte & IDE_DRQ));

        for (unsigned int j = 0; j < 256; j++)
        {
            in16(IO_PORT, &ax);
            buffer[i * 512 + j * 2] = ((char*)&ax)[0];
            buffer[i * 512 + j * 2 + 1] = ((char*)&ax)[1];
        }
    }
}

void disk_write(const char *buffer, const unsigned int sector, const unsigned char count)
{
    const unsigned char drive_head = (((unsigned char*)&sector)[3] & 0x0F) | 0xE0;
    unsigned char status = 0;

    if (!count)
    {
        return;
    }

    out8(IO_BLOCK_COUNT, count);
    out8(IO_LBA28_0_7,  ((unsigned char*)&sector)[0]);
    out8(IO_LBA28_8_15, ((unsigned char*)&sector)[1]);
    out8(IO_LBA28_16_23, ((unsigned char*)&sector)[2]);
    out8(IO_LBA28_24_27_W_4_CTRL, drive_head);

    out8(IO_REQUEST_AND_STATE, IO_WRITE);

    for (unsigned int i = 0; i < count; ++i) {
        do {
            in8(IO_REQUEST_AND_STATE, &status);
        } while (!(status & IDE_DRQ));

        for (unsigned int j = 0; j < 256; ++j) {
            const unsigned short data_word = (unsigned short)(
                (unsigned char)buffer[i * 512 + j * 2] |
                ((unsigned char)buffer[i * 512 + j * 2 + 1] << 8)
            );
            out16(IO_PORT, data_word);
        }
    }

    out8(IO_REQUEST_AND_STATE, ATA_CMD_CACHE_FLUSH);
    do {
        in8(IO_REQUEST_AND_STATE, &status);
    } while (status & IDE_BSY);
}
