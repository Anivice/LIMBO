#include "ide.h"
#include "io.h"

#define IO_PORT 					((uint16_t)0x1F0)
#define IO_ERR_STATE 				((uint16_t)0x1F1)
#define IO_BLOCK_COUNT 				((uint16_t)0x1F2)
#define IO_LBA28_0_7 				((uint16_t)0x1F3)
#define IO_LBA28_8_15 				((uint16_t)0x1F4)
#define IO_LBA28_16_23 				((uint16_t)0x1F5)
#define IO_LBA28_24_27_W_4_CTRL 	((uint16_t)0x1F6)
#define IO_REQUEST_AND_STATE 		((uint16_t)0x1F7)
#define IO_READ 					((uint8_t)0x20)
#define IDE_DRQ 				    ((uint8_t)0x08)
#define IO_WRITE                    ((uint8_t)0x30)
#define IDE_DRQ                     ((uint8_t)0x08)
#define IDE_BSY                     ((uint8_t)0x80)
#define IDE_ERR                     ((uint8_t)0x01)
#define ATA_CMD_CACHE_FLUSH         ((uint8_t)0xE7)

int get_disk_err_code()
{
    uint8_t err = 0;
    in8(IO_ERR_STATE, &err);
    return -(int)err;
}

int disk_read(char * buffer, const uint32_t sector, const uint8_t count)
{
    const uint8_t last_4bits_in_lba = (((char*)&sector)[3] & 0x0F) | 0xE0;
    uint8_t status = 0;

    if (!count)
    {
        return 0;
    }

    out8(IO_BLOCK_COUNT, count);
    out8(IO_LBA28_0_7, ((char*)&sector)[0]);
    out8(IO_LBA28_8_15, ((char*)&sector)[1]);
    out8(IO_LBA28_16_23, ((char*)&sector)[2]);
    out8(IO_LBA28_24_27_W_4_CTRL, last_4bits_in_lba);

    out8(IO_REQUEST_AND_STATE, IO_READ);

    // read
    uint16_t ax = 0;
    for (uint32_t i = 0; i < count; i++)
    {
        // wait
        do {
            in8(IO_REQUEST_AND_STATE, &status);
        } while (!(status & IDE_DRQ) && !(status & IDE_ERR));

        if (status & IDE_ERR)
        {
            return get_disk_err_code();
        }

        for (uint32_t j = 0; j < 256; j++)
        {
            in16(IO_PORT, &ax);
            buffer[i * 512 + j * 2] = ((char*)&ax)[0];
            buffer[i * 512 + j * 2 + 1] = ((char*)&ax)[1];
        }
    }

    return 0;
}

int disk_write(const char *buffer, const uint32_t sector, const uint8_t count)
{
    const uint8_t drive_head = (((uint8_t*)&sector)[3] & 0x0F) | 0xE0;
    uint8_t status = 0;

    if (!count)
    {
        return 0;
    }

    out8(IO_BLOCK_COUNT, count);
    out8(IO_LBA28_0_7,  ((uint8_t*)&sector)[0]);
    out8(IO_LBA28_8_15, ((uint8_t*)&sector)[1]);
    out8(IO_LBA28_16_23, ((uint8_t*)&sector)[2]);
    out8(IO_LBA28_24_27_W_4_CTRL, drive_head);

    out8(IO_REQUEST_AND_STATE, IO_WRITE);

    for (uint32_t i = 0; i < count; ++i)
    {
        do {
            in8(IO_REQUEST_AND_STATE, &status);
        } while (!(status & IDE_DRQ) && !(status & IDE_ERR));

        if (status & IDE_ERR)
        {
            return get_disk_err_code();
        }

        for (uint32_t j = 0; j < 256; ++j) {
            const uint16_t data_word = (uint16_t)(
                (uint8_t)buffer[i * 512 + j * 2] |
                ((uint8_t)buffer[i * 512 + j * 2 + 1] << 8)
            );
            out16(IO_PORT, data_word);
        }
    }

    out8(IO_REQUEST_AND_STATE, ATA_CMD_CACHE_FLUSH);
    do {
        in8(IO_REQUEST_AND_STATE, &status);
    } while (status & IDE_BSY && !(status & IDE_ERR));

    if (status & IDE_ERR)
    {
        return get_disk_err_code();
    }

    return 0;
}
