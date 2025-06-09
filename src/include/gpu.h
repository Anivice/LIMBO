#ifndef GPU_H
#define GPU_H

unsigned short get_cursor_loc();
void set_cursor_loc(unsigned short loc);
void write_to_video_memory(char c, unsigned loc, unsigned char attr);

#endif //GPU_H
