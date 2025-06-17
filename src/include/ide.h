#ifndef IDE_H
#define IDE_H

#include "stdint.h"

/*!
 * @brief Read disk, buffer will need to be 512 aligned, 0 < count <= 255 (0 will cause the operation to be discarded)
 * @param buffer Destination buffer
 * @param sector Starting sector
 * @param count Sector count
 * @returns Error code, 0 means successful
 */
[[nodiscard]]
int disk_read(char * buffer, uint32_t sector, uint8_t count);

/*!
 * @brief Write disk, buffer will need to be 512 aligned, 0 < count <= 255 (0 will cause the operation to be discarded)
 * @param buffer Source buffer
 * @param sector Starting sector
 * @param count Sector count
 * @returns Error code, 0 means successful
 */
[[nodiscard]]
int disk_write(const char *buffer, uint32_t sector, uint8_t count);

#endif //IDE_H
