/*!
 * @file irq.c
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
 * @brief This file defines IRQ dummies for kernel, for debug purposes only
 **/

#include "irq.h"
#include "die.h"

__attribute__((naked)) void irq_dummy_0()           { die("IRQ 000"); }
__attribute__((naked)) void irq_dummy_1()           { die("IRQ 001"); }
__attribute__((naked)) void irq_dummy_2()           { die("IRQ 002"); }
__attribute__((naked)) void irq_dummy_3()           { die("IRQ 003"); }
__attribute__((naked)) void irq_dummy_4()           { die("IRQ 004"); }
__attribute__((naked)) void irq_dummy_5()           { die("IRQ 005"); }
__attribute__((naked)) void irq_dummy_6()           { die("IRQ 006"); }
__attribute__((naked)) void irq_dummy_7()           { die("IRQ 007"); }
__attribute__((naked)) void irq_dummy_8()           { die("IRQ 008"); }
__attribute__((naked)) void irq_dummy_9()           { die("IRQ 009"); }
__attribute__((naked)) void irq_dummy_10()          { die("IRQ 010"); }
__attribute__((naked)) void irq_dummy_11()          { die("IRQ 011"); }
__attribute__((naked)) void irq_dummy_12()          { die("IRQ 012"); }
__attribute__((naked)) void irq_dummy_13()          { die("IRQ 013"); }
__attribute__((naked)) void irq_dummy_14()          { die("IRQ 014"); }
__attribute__((naked)) void irq_dummy_15()          { die("IRQ 015"); }
__attribute__((naked)) void irq_dummy_16()          { die("IRQ 016"); }
__attribute__((naked)) void irq_dummy_17_to_31()    { __asm__("iret");   }
__attribute__((naked)) void irq_dummy_32_to_255()   { __asm__("iret");   }

void * irq_dummy_table[256];

void irq_dummies_init()
{
    irq_dummy_table[0] = irq_dummy_0;
    irq_dummy_table[1] = irq_dummy_1;
    irq_dummy_table[2] = irq_dummy_2;
    irq_dummy_table[3] = irq_dummy_3;
    irq_dummy_table[4] = irq_dummy_4;
    irq_dummy_table[5] = irq_dummy_5;
    irq_dummy_table[6] = irq_dummy_6;
    irq_dummy_table[7] = irq_dummy_7;
    irq_dummy_table[8] = irq_dummy_8;
    irq_dummy_table[9] = irq_dummy_9;
    irq_dummy_table[10] = irq_dummy_10;
    irq_dummy_table[11] = irq_dummy_11;
    irq_dummy_table[12] = irq_dummy_12;
    irq_dummy_table[13] = irq_dummy_13;
    irq_dummy_table[14] = irq_dummy_14;
    irq_dummy_table[15] = irq_dummy_15;
    irq_dummy_table[16] = irq_dummy_16;
    irq_dummy_table[17] = irq_dummy_17_to_31;
    irq_dummy_table[18] = irq_dummy_17_to_31;
    irq_dummy_table[19] = irq_dummy_17_to_31;
    irq_dummy_table[20] = irq_dummy_17_to_31;
    irq_dummy_table[21] = irq_dummy_17_to_31;
    irq_dummy_table[22] = irq_dummy_17_to_31;
    irq_dummy_table[23] = irq_dummy_17_to_31;
    irq_dummy_table[24] = irq_dummy_17_to_31;
    irq_dummy_table[25] = irq_dummy_17_to_31;
    irq_dummy_table[26] = irq_dummy_17_to_31;
    irq_dummy_table[27] = irq_dummy_17_to_31;
    irq_dummy_table[28] = irq_dummy_17_to_31;
    irq_dummy_table[29] = irq_dummy_17_to_31;
    irq_dummy_table[30] = irq_dummy_17_to_31;
    irq_dummy_table[31] = irq_dummy_17_to_31;
    irq_dummy_table[32] = irq_dummy_32_to_255;
    irq_dummy_table[33] = irq_dummy_32_to_255;
    irq_dummy_table[34] = irq_dummy_32_to_255;
    irq_dummy_table[35] = irq_dummy_32_to_255;
    irq_dummy_table[36] = irq_dummy_32_to_255;
    irq_dummy_table[37] = irq_dummy_32_to_255;
    irq_dummy_table[38] = irq_dummy_32_to_255;
    irq_dummy_table[39] = irq_dummy_32_to_255;
    irq_dummy_table[40] = irq_dummy_32_to_255;
    irq_dummy_table[41] = irq_dummy_32_to_255;
    irq_dummy_table[42] = irq_dummy_32_to_255;
    irq_dummy_table[43] = irq_dummy_32_to_255;
    irq_dummy_table[44] = irq_dummy_32_to_255;
    irq_dummy_table[45] = irq_dummy_32_to_255;
    irq_dummy_table[46] = irq_dummy_32_to_255;
    irq_dummy_table[47] = irq_dummy_32_to_255;
    irq_dummy_table[48] = irq_dummy_32_to_255;
    irq_dummy_table[49] = irq_dummy_32_to_255;
    irq_dummy_table[50] = irq_dummy_32_to_255;
    irq_dummy_table[51] = irq_dummy_32_to_255;
    irq_dummy_table[52] = irq_dummy_32_to_255;
    irq_dummy_table[53] = irq_dummy_32_to_255;
    irq_dummy_table[54] = irq_dummy_32_to_255;
    irq_dummy_table[55] = irq_dummy_32_to_255;
    irq_dummy_table[56] = irq_dummy_32_to_255;
    irq_dummy_table[57] = irq_dummy_32_to_255;
    irq_dummy_table[58] = irq_dummy_32_to_255;
    irq_dummy_table[59] = irq_dummy_32_to_255;
    irq_dummy_table[60] = irq_dummy_32_to_255;
    irq_dummy_table[61] = irq_dummy_32_to_255;
    irq_dummy_table[62] = irq_dummy_32_to_255;
    irq_dummy_table[63] = irq_dummy_32_to_255;
    irq_dummy_table[64] = irq_dummy_32_to_255;
    irq_dummy_table[65] = irq_dummy_32_to_255;
    irq_dummy_table[66] = irq_dummy_32_to_255;
    irq_dummy_table[67] = irq_dummy_32_to_255;
    irq_dummy_table[68] = irq_dummy_32_to_255;
    irq_dummy_table[69] = irq_dummy_32_to_255;
    irq_dummy_table[70] = irq_dummy_32_to_255;
    irq_dummy_table[71] = irq_dummy_32_to_255;
    irq_dummy_table[72] = irq_dummy_32_to_255;
    irq_dummy_table[73] = irq_dummy_32_to_255;
    irq_dummy_table[74] = irq_dummy_32_to_255;
    irq_dummy_table[75] = irq_dummy_32_to_255;
    irq_dummy_table[76] = irq_dummy_32_to_255;
    irq_dummy_table[77] = irq_dummy_32_to_255;
    irq_dummy_table[78] = irq_dummy_32_to_255;
    irq_dummy_table[79] = irq_dummy_32_to_255;
    irq_dummy_table[80] = irq_dummy_32_to_255;
    irq_dummy_table[81] = irq_dummy_32_to_255;
    irq_dummy_table[82] = irq_dummy_32_to_255;
    irq_dummy_table[83] = irq_dummy_32_to_255;
    irq_dummy_table[84] = irq_dummy_32_to_255;
    irq_dummy_table[85] = irq_dummy_32_to_255;
    irq_dummy_table[86] = irq_dummy_32_to_255;
    irq_dummy_table[87] = irq_dummy_32_to_255;
    irq_dummy_table[88] = irq_dummy_32_to_255;
    irq_dummy_table[89] = irq_dummy_32_to_255;
    irq_dummy_table[90] = irq_dummy_32_to_255;
    irq_dummy_table[91] = irq_dummy_32_to_255;
    irq_dummy_table[92] = irq_dummy_32_to_255;
    irq_dummy_table[93] = irq_dummy_32_to_255;
    irq_dummy_table[94] = irq_dummy_32_to_255;
    irq_dummy_table[95] = irq_dummy_32_to_255;
    irq_dummy_table[96] = irq_dummy_32_to_255;
    irq_dummy_table[97] = irq_dummy_32_to_255;
    irq_dummy_table[98] = irq_dummy_32_to_255;
    irq_dummy_table[99] = irq_dummy_32_to_255;
    irq_dummy_table[100] = irq_dummy_32_to_255;
    irq_dummy_table[101] = irq_dummy_32_to_255;
    irq_dummy_table[102] = irq_dummy_32_to_255;
    irq_dummy_table[103] = irq_dummy_32_to_255;
    irq_dummy_table[104] = irq_dummy_32_to_255;
    irq_dummy_table[105] = irq_dummy_32_to_255;
    irq_dummy_table[106] = irq_dummy_32_to_255;
    irq_dummy_table[107] = irq_dummy_32_to_255;
    irq_dummy_table[108] = irq_dummy_32_to_255;
    irq_dummy_table[109] = irq_dummy_32_to_255;
    irq_dummy_table[110] = irq_dummy_32_to_255;
    irq_dummy_table[111] = irq_dummy_32_to_255;
    irq_dummy_table[112] = irq_dummy_32_to_255;
    irq_dummy_table[113] = irq_dummy_32_to_255;
    irq_dummy_table[114] = irq_dummy_32_to_255;
    irq_dummy_table[115] = irq_dummy_32_to_255;
    irq_dummy_table[116] = irq_dummy_32_to_255;
    irq_dummy_table[117] = irq_dummy_32_to_255;
    irq_dummy_table[118] = irq_dummy_32_to_255;
    irq_dummy_table[119] = irq_dummy_32_to_255;
    irq_dummy_table[120] = irq_dummy_32_to_255;
    irq_dummy_table[121] = irq_dummy_32_to_255;
    irq_dummy_table[122] = irq_dummy_32_to_255;
    irq_dummy_table[123] = irq_dummy_32_to_255;
    irq_dummy_table[124] = irq_dummy_32_to_255;
    irq_dummy_table[125] = irq_dummy_32_to_255;
    irq_dummy_table[126] = irq_dummy_32_to_255;
    irq_dummy_table[127] = irq_dummy_32_to_255;
    irq_dummy_table[128] = irq_dummy_32_to_255;
    irq_dummy_table[129] = irq_dummy_32_to_255;
    irq_dummy_table[130] = irq_dummy_32_to_255;
    irq_dummy_table[131] = irq_dummy_32_to_255;
    irq_dummy_table[132] = irq_dummy_32_to_255;
    irq_dummy_table[133] = irq_dummy_32_to_255;
    irq_dummy_table[134] = irq_dummy_32_to_255;
    irq_dummy_table[135] = irq_dummy_32_to_255;
    irq_dummy_table[136] = irq_dummy_32_to_255;
    irq_dummy_table[137] = irq_dummy_32_to_255;
    irq_dummy_table[138] = irq_dummy_32_to_255;
    irq_dummy_table[139] = irq_dummy_32_to_255;
    irq_dummy_table[140] = irq_dummy_32_to_255;
    irq_dummy_table[141] = irq_dummy_32_to_255;
    irq_dummy_table[142] = irq_dummy_32_to_255;
    irq_dummy_table[143] = irq_dummy_32_to_255;
    irq_dummy_table[144] = irq_dummy_32_to_255;
    irq_dummy_table[145] = irq_dummy_32_to_255;
    irq_dummy_table[146] = irq_dummy_32_to_255;
    irq_dummy_table[147] = irq_dummy_32_to_255;
    irq_dummy_table[148] = irq_dummy_32_to_255;
    irq_dummy_table[149] = irq_dummy_32_to_255;
    irq_dummy_table[150] = irq_dummy_32_to_255;
    irq_dummy_table[151] = irq_dummy_32_to_255;
    irq_dummy_table[152] = irq_dummy_32_to_255;
    irq_dummy_table[153] = irq_dummy_32_to_255;
    irq_dummy_table[154] = irq_dummy_32_to_255;
    irq_dummy_table[155] = irq_dummy_32_to_255;
    irq_dummy_table[156] = irq_dummy_32_to_255;
    irq_dummy_table[157] = irq_dummy_32_to_255;
    irq_dummy_table[158] = irq_dummy_32_to_255;
    irq_dummy_table[159] = irq_dummy_32_to_255;
    irq_dummy_table[160] = irq_dummy_32_to_255;
    irq_dummy_table[161] = irq_dummy_32_to_255;
    irq_dummy_table[162] = irq_dummy_32_to_255;
    irq_dummy_table[163] = irq_dummy_32_to_255;
    irq_dummy_table[164] = irq_dummy_32_to_255;
    irq_dummy_table[165] = irq_dummy_32_to_255;
    irq_dummy_table[166] = irq_dummy_32_to_255;
    irq_dummy_table[167] = irq_dummy_32_to_255;
    irq_dummy_table[168] = irq_dummy_32_to_255;
    irq_dummy_table[169] = irq_dummy_32_to_255;
    irq_dummy_table[170] = irq_dummy_32_to_255;
    irq_dummy_table[171] = irq_dummy_32_to_255;
    irq_dummy_table[172] = irq_dummy_32_to_255;
    irq_dummy_table[173] = irq_dummy_32_to_255;
    irq_dummy_table[174] = irq_dummy_32_to_255;
    irq_dummy_table[175] = irq_dummy_32_to_255;
    irq_dummy_table[176] = irq_dummy_32_to_255;
    irq_dummy_table[177] = irq_dummy_32_to_255;
    irq_dummy_table[178] = irq_dummy_32_to_255;
    irq_dummy_table[179] = irq_dummy_32_to_255;
    irq_dummy_table[180] = irq_dummy_32_to_255;
    irq_dummy_table[181] = irq_dummy_32_to_255;
    irq_dummy_table[182] = irq_dummy_32_to_255;
    irq_dummy_table[183] = irq_dummy_32_to_255;
    irq_dummy_table[184] = irq_dummy_32_to_255;
    irq_dummy_table[185] = irq_dummy_32_to_255;
    irq_dummy_table[186] = irq_dummy_32_to_255;
    irq_dummy_table[187] = irq_dummy_32_to_255;
    irq_dummy_table[188] = irq_dummy_32_to_255;
    irq_dummy_table[189] = irq_dummy_32_to_255;
    irq_dummy_table[190] = irq_dummy_32_to_255;
    irq_dummy_table[191] = irq_dummy_32_to_255;
    irq_dummy_table[192] = irq_dummy_32_to_255;
    irq_dummy_table[193] = irq_dummy_32_to_255;
    irq_dummy_table[194] = irq_dummy_32_to_255;
    irq_dummy_table[195] = irq_dummy_32_to_255;
    irq_dummy_table[196] = irq_dummy_32_to_255;
    irq_dummy_table[197] = irq_dummy_32_to_255;
    irq_dummy_table[198] = irq_dummy_32_to_255;
    irq_dummy_table[199] = irq_dummy_32_to_255;
    irq_dummy_table[200] = irq_dummy_32_to_255;
    irq_dummy_table[201] = irq_dummy_32_to_255;
    irq_dummy_table[202] = irq_dummy_32_to_255;
    irq_dummy_table[203] = irq_dummy_32_to_255;
    irq_dummy_table[204] = irq_dummy_32_to_255;
    irq_dummy_table[205] = irq_dummy_32_to_255;
    irq_dummy_table[206] = irq_dummy_32_to_255;
    irq_dummy_table[207] = irq_dummy_32_to_255;
    irq_dummy_table[208] = irq_dummy_32_to_255;
    irq_dummy_table[209] = irq_dummy_32_to_255;
    irq_dummy_table[210] = irq_dummy_32_to_255;
    irq_dummy_table[211] = irq_dummy_32_to_255;
    irq_dummy_table[212] = irq_dummy_32_to_255;
    irq_dummy_table[213] = irq_dummy_32_to_255;
    irq_dummy_table[214] = irq_dummy_32_to_255;
    irq_dummy_table[215] = irq_dummy_32_to_255;
    irq_dummy_table[216] = irq_dummy_32_to_255;
    irq_dummy_table[217] = irq_dummy_32_to_255;
    irq_dummy_table[218] = irq_dummy_32_to_255;
    irq_dummy_table[219] = irq_dummy_32_to_255;
    irq_dummy_table[220] = irq_dummy_32_to_255;
    irq_dummy_table[221] = irq_dummy_32_to_255;
    irq_dummy_table[222] = irq_dummy_32_to_255;
    irq_dummy_table[223] = irq_dummy_32_to_255;
    irq_dummy_table[224] = irq_dummy_32_to_255;
    irq_dummy_table[225] = irq_dummy_32_to_255;
    irq_dummy_table[226] = irq_dummy_32_to_255;
    irq_dummy_table[227] = irq_dummy_32_to_255;
    irq_dummy_table[228] = irq_dummy_32_to_255;
    irq_dummy_table[229] = irq_dummy_32_to_255;
    irq_dummy_table[230] = irq_dummy_32_to_255;
    irq_dummy_table[231] = irq_dummy_32_to_255;
    irq_dummy_table[232] = irq_dummy_32_to_255;
    irq_dummy_table[233] = irq_dummy_32_to_255;
    irq_dummy_table[234] = irq_dummy_32_to_255;
    irq_dummy_table[235] = irq_dummy_32_to_255;
    irq_dummy_table[236] = irq_dummy_32_to_255;
    irq_dummy_table[237] = irq_dummy_32_to_255;
    irq_dummy_table[238] = irq_dummy_32_to_255;
    irq_dummy_table[239] = irq_dummy_32_to_255;
    irq_dummy_table[240] = irq_dummy_32_to_255;
    irq_dummy_table[241] = irq_dummy_32_to_255;
    irq_dummy_table[242] = irq_dummy_32_to_255;
    irq_dummy_table[243] = irq_dummy_32_to_255;
    irq_dummy_table[244] = irq_dummy_32_to_255;
    irq_dummy_table[245] = irq_dummy_32_to_255;
    irq_dummy_table[246] = irq_dummy_32_to_255;
    irq_dummy_table[247] = irq_dummy_32_to_255;
    irq_dummy_table[248] = irq_dummy_32_to_255;
    irq_dummy_table[249] = irq_dummy_32_to_255;
    irq_dummy_table[250] = irq_dummy_32_to_255;
    irq_dummy_table[251] = irq_dummy_32_to_255;
    irq_dummy_table[252] = irq_dummy_32_to_255;
    irq_dummy_table[253] = irq_dummy_32_to_255;
    irq_dummy_table[254] = irq_dummy_32_to_255;
    irq_dummy_table[255] = irq_dummy_32_to_255;
}
