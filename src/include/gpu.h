#ifndef GPU_H
#define GPU_H

/*!
 * @brief Get current cursor location
 * @return Current cursor location index [0-1999]
 */
unsigned short get_cursor_loc();

/*!
 * @brief Set new cursor location
 * @param loc New cursor location
 * @returns Nothing
 */
void set_cursor_loc(unsigned short loc);

/*!
 * @brief Write directly to VGA video memory
 * @param c ASCII code
 * @param loc Cursor location offset
 * @param attr Color attributes
 * @returns Nothing
 */
void write_to_video_memory(char c, unsigned loc, unsigned char attr);

#endif //GPU_H
