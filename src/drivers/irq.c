/*!
 * @file irq.c
 * @brief This file defines interrupt dummies for kernel, for debug purposes only
 *
 * @copyright
 * Copyright 2025 Anivice Ives
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 **/

#include "irq.h"
#include "marco.h"
#include "printk.h"
#include "idt.h"
#include "die.h"

#define IRQ_STUB(n)                                                     \
    __attribute__((naked, used, NO_OPTIMIZATION))                       \
    static void irq_stub_##n(void) {                                    \
        __asm__ __volatile__(                                           \
            "pushl $" #n "\n\t"      /* push vector number */           \
            "jmp irq_common\n\t"                                        \
        );                                                              \
    }

IRQ_STUB(0) IRQ_STUB(1) IRQ_STUB(2) IRQ_STUB(3) IRQ_STUB(4) IRQ_STUB(5) IRQ_STUB(6) IRQ_STUB(7) IRQ_STUB(8) IRQ_STUB(9)
IRQ_STUB(10) IRQ_STUB(11) IRQ_STUB(12) IRQ_STUB(13) IRQ_STUB(14) IRQ_STUB(15) IRQ_STUB(16) IRQ_STUB(17) IRQ_STUB(18)
IRQ_STUB(19) IRQ_STUB(20) IRQ_STUB(21) IRQ_STUB(22) IRQ_STUB(23) IRQ_STUB(24) IRQ_STUB(25) IRQ_STUB(26) IRQ_STUB(27)
IRQ_STUB(28) IRQ_STUB(29) IRQ_STUB(30) IRQ_STUB(31) IRQ_STUB(32) IRQ_STUB(33) IRQ_STUB(34) IRQ_STUB(35) IRQ_STUB(36)
IRQ_STUB(37) IRQ_STUB(38) IRQ_STUB(39) IRQ_STUB(40) IRQ_STUB(41) IRQ_STUB(42) IRQ_STUB(43) IRQ_STUB(44) IRQ_STUB(45)
IRQ_STUB(46) IRQ_STUB(47) IRQ_STUB(48) IRQ_STUB(49) IRQ_STUB(50) IRQ_STUB(51) IRQ_STUB(52) IRQ_STUB(53) IRQ_STUB(54)
IRQ_STUB(55) IRQ_STUB(56) IRQ_STUB(57) IRQ_STUB(58) IRQ_STUB(59) IRQ_STUB(60) IRQ_STUB(61) IRQ_STUB(62) IRQ_STUB(63)
IRQ_STUB(64) IRQ_STUB(65) IRQ_STUB(66) IRQ_STUB(67) IRQ_STUB(68) IRQ_STUB(69) IRQ_STUB(70) IRQ_STUB(71) IRQ_STUB(72)
IRQ_STUB(73) IRQ_STUB(74) IRQ_STUB(75) IRQ_STUB(76) IRQ_STUB(77) IRQ_STUB(78) IRQ_STUB(79) IRQ_STUB(80) IRQ_STUB(81)
IRQ_STUB(82) IRQ_STUB(83) IRQ_STUB(84) IRQ_STUB(85) IRQ_STUB(86) IRQ_STUB(87) IRQ_STUB(88) IRQ_STUB(89) IRQ_STUB(90)
IRQ_STUB(91) IRQ_STUB(92) IRQ_STUB(93) IRQ_STUB(94) IRQ_STUB(95) IRQ_STUB(96) IRQ_STUB(97) IRQ_STUB(98) IRQ_STUB(99)
IRQ_STUB(100) IRQ_STUB(101) IRQ_STUB(102) IRQ_STUB(103) IRQ_STUB(104) IRQ_STUB(105) IRQ_STUB(106) IRQ_STUB(107)
IRQ_STUB(108) IRQ_STUB(109) IRQ_STUB(110) IRQ_STUB(111) IRQ_STUB(112) IRQ_STUB(113) IRQ_STUB(114) IRQ_STUB(115)
IRQ_STUB(116) IRQ_STUB(117) IRQ_STUB(118) IRQ_STUB(119) IRQ_STUB(120) IRQ_STUB(121) IRQ_STUB(122) IRQ_STUB(123)
IRQ_STUB(124) IRQ_STUB(125) IRQ_STUB(126) IRQ_STUB(127) IRQ_STUB(128) IRQ_STUB(129) IRQ_STUB(130) IRQ_STUB(131)
IRQ_STUB(132) IRQ_STUB(133) IRQ_STUB(134) IRQ_STUB(135) IRQ_STUB(136) IRQ_STUB(137) IRQ_STUB(138) IRQ_STUB(139)
IRQ_STUB(140) IRQ_STUB(141) IRQ_STUB(142) IRQ_STUB(143) IRQ_STUB(144) IRQ_STUB(145) IRQ_STUB(146) IRQ_STUB(147)
IRQ_STUB(148) IRQ_STUB(149) IRQ_STUB(150) IRQ_STUB(151) IRQ_STUB(152) IRQ_STUB(153) IRQ_STUB(154) IRQ_STUB(155)
IRQ_STUB(156) IRQ_STUB(157) IRQ_STUB(158) IRQ_STUB(159) IRQ_STUB(160) IRQ_STUB(161) IRQ_STUB(162) IRQ_STUB(163)
IRQ_STUB(164) IRQ_STUB(165) IRQ_STUB(166) IRQ_STUB(167) IRQ_STUB(168) IRQ_STUB(169) IRQ_STUB(170) IRQ_STUB(171)
IRQ_STUB(172) IRQ_STUB(173) IRQ_STUB(174) IRQ_STUB(175) IRQ_STUB(176) IRQ_STUB(177) IRQ_STUB(178) IRQ_STUB(179)
IRQ_STUB(180) IRQ_STUB(181) IRQ_STUB(182) IRQ_STUB(183) IRQ_STUB(184) IRQ_STUB(185) IRQ_STUB(186) IRQ_STUB(187)
IRQ_STUB(188) IRQ_STUB(189) IRQ_STUB(190) IRQ_STUB(191) IRQ_STUB(192) IRQ_STUB(193) IRQ_STUB(194) IRQ_STUB(195)
IRQ_STUB(196) IRQ_STUB(197) IRQ_STUB(198) IRQ_STUB(199) IRQ_STUB(200) IRQ_STUB(201) IRQ_STUB(202) IRQ_STUB(203)
IRQ_STUB(204) IRQ_STUB(205) IRQ_STUB(206) IRQ_STUB(207) IRQ_STUB(208) IRQ_STUB(209) IRQ_STUB(210) IRQ_STUB(211)
IRQ_STUB(212) IRQ_STUB(213) IRQ_STUB(214) IRQ_STUB(215) IRQ_STUB(216) IRQ_STUB(217) IRQ_STUB(218) IRQ_STUB(219)
IRQ_STUB(220) IRQ_STUB(221) IRQ_STUB(222) IRQ_STUB(223) IRQ_STUB(224) IRQ_STUB(225) IRQ_STUB(226) IRQ_STUB(227)
IRQ_STUB(228) IRQ_STUB(229) IRQ_STUB(230) IRQ_STUB(231) IRQ_STUB(232) IRQ_STUB(233) IRQ_STUB(234) IRQ_STUB(235)
IRQ_STUB(236) IRQ_STUB(237) IRQ_STUB(238) IRQ_STUB(239) IRQ_STUB(240) IRQ_STUB(241) IRQ_STUB(242) IRQ_STUB(243)
IRQ_STUB(244) IRQ_STUB(245) IRQ_STUB(246) IRQ_STUB(247) IRQ_STUB(248) IRQ_STUB(249) IRQ_STUB(250) IRQ_STUB(251)
IRQ_STUB(252) IRQ_STUB(253) IRQ_STUB(254) IRQ_STUB(255)

typedef void (*irq_stub_t)();

irq_stub_t const irq_stub_table[256] =
{
#define E(n) irq_stub_##n,
    E(0) E(1) E(2) E(3) E(4) E(5) E(6) E(7) E(8) E(9) E(10) E(11) E(12) E(13) E(14) E(15) E(16) E(17) E(18) E(19) E(20)
    E(21) E(22) E(23) E(24) E(25) E(26) E(27) E(28) E(29) E(30) E(31) E(32) E(33) E(34) E(35) E(36) E(37) E(38) E(39)
    E(40) E(41) E(42) E(43) E(44) E(45) E(46) E(47) E(48) E(49) E(50) E(51) E(52) E(53) E(54) E(55) E(56) E(57) E(58)
    E(59) E(60) E(61) E(62) E(63) E(64) E(65) E(66) E(67) E(68) E(69) E(70) E(71) E(72) E(73) E(74) E(75) E(76) E(77)
    E(78) E(79) E(80) E(81) E(82) E(83) E(84) E(85) E(86) E(87) E(88) E(89) E(90) E(91) E(92) E(93) E(94) E(95) E(96)
    E(97) E(98) E(99) E(100) E(101) E(102) E(103) E(104) E(105) E(106) E(107) E(108) E(109) E(110) E(111) E(112) E(113)
    E(114) E(115) E(116) E(117) E(118) E(119) E(120) E(121) E(122) E(123) E(124) E(125) E(126) E(127) E(128) E(129) E(130)
    E(131) E(132) E(133) E(134) E(135) E(136) E(137) E(138) E(139) E(140) E(141) E(142) E(143) E(144) E(145) E(146) E(147)
    E(148) E(149) E(150) E(151) E(152) E(153) E(154) E(155) E(156) E(157) E(158) E(159) E(160) E(161) E(162) E(163) E(164)
    E(165) E(166) E(167) E(168) E(169) E(170) E(171) E(172) E(173) E(174) E(175) E(176) E(177) E(178) E(179) E(180) E(181)
    E(182) E(183) E(184) E(185) E(186) E(187) E(188) E(189) E(190) E(191) E(192) E(193) E(194) E(195) E(196) E(197) E(198)
    E(199) E(200) E(201) E(202) E(203) E(204) E(205) E(206) E(207) E(208) E(209) E(210) E(211) E(212) E(213) E(214) E(215)
    E(216) E(217) E(218) E(219) E(220) E(221) E(222) E(223) E(224) E(225) E(226) E(227) E(228) E(229) E(230) E(231) E(232)
    E(233) E(234) E(235) E(236) E(237) E(238) E(239) E(240) E(241) E(242) E(243) E(244) E(245) E(246) E(247) E(248) E(249)
    E(250) E(251) E(252) E(253) E(254) E(255)
#undef E
};

__attribute__((used))
static void int_dispatcher(const int num, const uint32_t eip)
{
    switch (num)
    {
        case 0: // div/0
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        case 14: // Page Fault
        case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25:
        case 26: case 27: case 28: case 29: case 30: case 31:
            printk("fatal error (INT %d) at position 0x%x\n", num, eip);
            die("FATAL\n");
        default:
            printk("CPU interrupt: %d, at position 0x%x\n", num, eip);
    }
}

// static const char irq_message[] __attribute__((used)) =
    // "Unhandled processor exception or interrupt";

__attribute__((naked, used, NO_OPTIMIZATION))
static void irq_common()
{
    __asm__ __volatile__(
        "cli                        \n\t"
        "cld                        \n\t"

        /* Save all GP regs and segment regs we may clobber */
        "pusha                      \n\t"
        "push   %ds                 \n\t"
        "push   %es                 \n\t"
        "push   %fs                 \n\t"
        "push   %gs                 \n\t"

        /* Load kernel data segments */
        "mov    $0x08,      %ax     \n\t"
        "mov    %ax,        %ds     \n\t"
        "mov    %ax,        %es     \n\t"
        "mov    %ax,        %fs     \n\t"
        "mov    %ax,        %gs     \n\t"

        /*
         * Stack layout now (offset from ESP):
         *   0  %gs
         *   4  %fs
         *   8  %es
         *  12  %ds
         *  16  %edi
         *  20  %esi
         *  24  %ebp
         *  28  saved %esp (from pusha)
         *  32  %ebx
         *  36  %edx
         *  40  %ecx
         *  44  %eax
         *  48  vector N          <-- pushed by irq_stub_N
         *  52  EIP               <-- iret destination
         *  56  CS
         *  60  EFLAGS
         */

        /* cdecl: push args right-to-left */
        "pushl  52(%esp)            \n\t"  /* 2nd arg: iret EIP  */
        "pushl  52(%esp)            \n\t"  /* 1st arg: irq number */
        "call   int_dispatcher      \n\t"
        "add    $8,         %esp    \n\t"  /* clean up args       */

        /* Restore everything */
        "pop    %gs                 \n\t"
        "pop    %fs                 \n\t"
        "pop    %es                 \n\t"
        "pop    %ds                 \n\t"
        "popa                       \n\t"
        "add    $4,         %esp    \n\t"  /* drop vector number  */
        "iret                       \n\t"
    );
}

NO_PLEASE_DONT_OPTIMIZE
void install_irq()
{
    __asm__ volatile ("cli" ::: "memory");

    for (unsigned i = 0; i < 256; ++i) {
        idt_set_gate(i, (uint32_t)irq_stub_table[i], 0x10, 0x8E);
    }

    idt_descriptor.limit = sizeof(idt) - 1;
    idt_descriptor.base = (uint32_t)idt;
    __asm__ volatile ("lidt %0" : : "m"(idt_descriptor) : "memory");
}