#ifndef DIE_H
#define DIE_H

/*!
 * Invoke a kernel panic
 * This will display an error message, show the update and current die time (UNIX timestamp of current time in RTC),
 * and display caller frame trace to indicate who called die().
 * Then, it will enter an endless indefinite halt and will never resume.
 * This is used to indicate an unrecoverable error happened in kernel code.
 * @param str Error message
 */
[[noreturn]] void die(const char * str);

#endif //DIE_H
