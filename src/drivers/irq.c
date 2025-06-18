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

__attribute__((naked)) void irq_dummy_0() { die("IRQ 000"); }
__attribute__((naked)) void irq_dummy_1() { die("IRQ 001"); }
__attribute__((naked)) void irq_dummy_2() { die("IRQ 002"); }
__attribute__((naked)) void irq_dummy_3() { die("IRQ 003"); }
__attribute__((naked)) void irq_dummy_4() { die("IRQ 004"); }
__attribute__((naked)) void irq_dummy_5() { die("IRQ 005"); }
__attribute__((naked)) void irq_dummy_6() { die("IRQ 006"); }
__attribute__((naked)) void irq_dummy_7() { die("IRQ 007"); }
__attribute__((naked)) void irq_dummy_8() { die("IRQ 008"); }
__attribute__((naked)) void irq_dummy_9() { die("IRQ 009"); }
__attribute__((naked)) void irq_dummy_10() { die("IRQ 010"); }
__attribute__((naked)) void irq_dummy_11() { die("IRQ 011"); }
__attribute__((naked)) void irq_dummy_12() { die("IRQ 012"); }
__attribute__((naked)) void irq_dummy_13() { die("IRQ 013"); }
__attribute__((naked)) void irq_dummy_14() { die("IRQ 014"); }
__attribute__((naked)) void irq_dummy_15() { die("IRQ 015"); }
__attribute__((naked)) void irq_dummy_16() { die("IRQ 016"); }
__attribute__((naked)) void irq_dummy_17() { die("IRQ 017"); }
__attribute__((naked)) void irq_dummy_18() { die("IRQ 018"); }
__attribute__((naked)) void irq_dummy_19() { die("IRQ 019"); }
__attribute__((naked)) void irq_dummy_20() { die("IRQ 020"); }
__attribute__((naked)) void irq_dummy_21() { die("IRQ 021"); }
__attribute__((naked)) void irq_dummy_22() { die("IRQ 022"); }
__attribute__((naked)) void irq_dummy_23() { die("IRQ 023"); }
__attribute__((naked)) void irq_dummy_24() { die("IRQ 024"); }
__attribute__((naked)) void irq_dummy_25() { die("IRQ 025"); }
__attribute__((naked)) void irq_dummy_26() { die("IRQ 026"); }
__attribute__((naked)) void irq_dummy_27() { die("IRQ 027"); }
__attribute__((naked)) void irq_dummy_28() { die("IRQ 028"); }
__attribute__((naked)) void irq_dummy_29() { die("IRQ 029"); }
__attribute__((naked)) void irq_dummy_30() { die("IRQ 030"); }
__attribute__((naked)) void irq_dummy_31() { die("IRQ 031"); }
__attribute__((naked)) void irq_dummy_32() { die("IRQ 032"); }
__attribute__((naked)) void irq_dummy_33() { die("IRQ 033"); }
__attribute__((naked)) void irq_dummy_34() { die("IRQ 034"); }
__attribute__((naked)) void irq_dummy_35() { die("IRQ 035"); }
__attribute__((naked)) void irq_dummy_36() { die("IRQ 036"); }
__attribute__((naked)) void irq_dummy_37() { die("IRQ 037"); }
__attribute__((naked)) void irq_dummy_38() { die("IRQ 038"); }
__attribute__((naked)) void irq_dummy_39() { die("IRQ 039"); }
__attribute__((naked)) void irq_dummy_40() { die("IRQ 040"); }
__attribute__((naked)) void irq_dummy_41() { die("IRQ 041"); }
__attribute__((naked)) void irq_dummy_42() { die("IRQ 042"); }
__attribute__((naked)) void irq_dummy_43() { die("IRQ 043"); }
__attribute__((naked)) void irq_dummy_44() { die("IRQ 044"); }
__attribute__((naked)) void irq_dummy_45() { die("IRQ 045"); }
__attribute__((naked)) void irq_dummy_46() { die("IRQ 046"); }
__attribute__((naked)) void irq_dummy_47() { die("IRQ 047"); }
__attribute__((naked)) void irq_dummy_48() { die("IRQ 048"); }
__attribute__((naked)) void irq_dummy_49() { die("IRQ 049"); }
__attribute__((naked)) void irq_dummy_50() { die("IRQ 050"); }
__attribute__((naked)) void irq_dummy_51() { die("IRQ 051"); }
__attribute__((naked)) void irq_dummy_52() { die("IRQ 052"); }
__attribute__((naked)) void irq_dummy_53() { die("IRQ 053"); }
__attribute__((naked)) void irq_dummy_54() { die("IRQ 054"); }
__attribute__((naked)) void irq_dummy_55() { die("IRQ 055"); }
__attribute__((naked)) void irq_dummy_56() { die("IRQ 056"); }
__attribute__((naked)) void irq_dummy_57() { die("IRQ 057"); }
__attribute__((naked)) void irq_dummy_58() { die("IRQ 058"); }
__attribute__((naked)) void irq_dummy_59() { die("IRQ 059"); }
__attribute__((naked)) void irq_dummy_60() { die("IRQ 060"); }
__attribute__((naked)) void irq_dummy_61() { die("IRQ 061"); }
__attribute__((naked)) void irq_dummy_62() { die("IRQ 062"); }
__attribute__((naked)) void irq_dummy_63() { die("IRQ 063"); }
__attribute__((naked)) void irq_dummy_64() { die("IRQ 064"); }
__attribute__((naked)) void irq_dummy_65() { die("IRQ 065"); }
__attribute__((naked)) void irq_dummy_66() { die("IRQ 066"); }
__attribute__((naked)) void irq_dummy_67() { die("IRQ 067"); }
__attribute__((naked)) void irq_dummy_68() { die("IRQ 068"); }
__attribute__((naked)) void irq_dummy_69() { die("IRQ 069"); }
__attribute__((naked)) void irq_dummy_70() { die("IRQ 070"); }
__attribute__((naked)) void irq_dummy_71() { die("IRQ 071"); }
__attribute__((naked)) void irq_dummy_72() { die("IRQ 072"); }
__attribute__((naked)) void irq_dummy_73() { die("IRQ 073"); }
__attribute__((naked)) void irq_dummy_74() { die("IRQ 074"); }
__attribute__((naked)) void irq_dummy_75() { die("IRQ 075"); }
__attribute__((naked)) void irq_dummy_76() { die("IRQ 076"); }
__attribute__((naked)) void irq_dummy_77() { die("IRQ 077"); }
__attribute__((naked)) void irq_dummy_78() { die("IRQ 078"); }
__attribute__((naked)) void irq_dummy_79() { die("IRQ 079"); }
__attribute__((naked)) void irq_dummy_80() { die("IRQ 080"); }
__attribute__((naked)) void irq_dummy_81() { die("IRQ 081"); }
__attribute__((naked)) void irq_dummy_82() { die("IRQ 082"); }
__attribute__((naked)) void irq_dummy_83() { die("IRQ 083"); }
__attribute__((naked)) void irq_dummy_84() { die("IRQ 084"); }
__attribute__((naked)) void irq_dummy_85() { die("IRQ 085"); }
__attribute__((naked)) void irq_dummy_86() { die("IRQ 086"); }
__attribute__((naked)) void irq_dummy_87() { die("IRQ 087"); }
__attribute__((naked)) void irq_dummy_88() { die("IRQ 088"); }
__attribute__((naked)) void irq_dummy_89() { die("IRQ 089"); }
__attribute__((naked)) void irq_dummy_90() { die("IRQ 090"); }
__attribute__((naked)) void irq_dummy_91() { die("IRQ 091"); }
__attribute__((naked)) void irq_dummy_92() { die("IRQ 092"); }
__attribute__((naked)) void irq_dummy_93() { die("IRQ 093"); }
__attribute__((naked)) void irq_dummy_94() { die("IRQ 094"); }
__attribute__((naked)) void irq_dummy_95() { die("IRQ 095"); }
__attribute__((naked)) void irq_dummy_96() { die("IRQ 096"); }
__attribute__((naked)) void irq_dummy_97() { die("IRQ 097"); }
__attribute__((naked)) void irq_dummy_98() { die("IRQ 098"); }
__attribute__((naked)) void irq_dummy_99() { die("IRQ 099"); }
__attribute__((naked)) void irq_dummy_100() { die("IRQ 100"); }
__attribute__((naked)) void irq_dummy_101() { die("IRQ 101"); }
__attribute__((naked)) void irq_dummy_102() { die("IRQ 102"); }
__attribute__((naked)) void irq_dummy_103() { die("IRQ 103"); }
__attribute__((naked)) void irq_dummy_104() { die("IRQ 104"); }
__attribute__((naked)) void irq_dummy_105() { die("IRQ 105"); }
__attribute__((naked)) void irq_dummy_106() { die("IRQ 106"); }
__attribute__((naked)) void irq_dummy_107() { die("IRQ 107"); }
__attribute__((naked)) void irq_dummy_108() { die("IRQ 108"); }
__attribute__((naked)) void irq_dummy_109() { die("IRQ 109"); }
__attribute__((naked)) void irq_dummy_110() { die("IRQ 110"); }
__attribute__((naked)) void irq_dummy_111() { die("IRQ 111"); }
__attribute__((naked)) void irq_dummy_112() { die("IRQ 112"); }
__attribute__((naked)) void irq_dummy_113() { die("IRQ 113"); }
__attribute__((naked)) void irq_dummy_114() { die("IRQ 114"); }
__attribute__((naked)) void irq_dummy_115() { die("IRQ 115"); }
__attribute__((naked)) void irq_dummy_116() { die("IRQ 116"); }
__attribute__((naked)) void irq_dummy_117() { die("IRQ 117"); }
__attribute__((naked)) void irq_dummy_118() { die("IRQ 118"); }
__attribute__((naked)) void irq_dummy_119() { die("IRQ 119"); }
__attribute__((naked)) void irq_dummy_120() { die("IRQ 120"); }
__attribute__((naked)) void irq_dummy_121() { die("IRQ 121"); }
__attribute__((naked)) void irq_dummy_122() { die("IRQ 122"); }
__attribute__((naked)) void irq_dummy_123() { die("IRQ 123"); }
__attribute__((naked)) void irq_dummy_124() { die("IRQ 124"); }
__attribute__((naked)) void irq_dummy_125() { die("IRQ 125"); }
__attribute__((naked)) void irq_dummy_126() { die("IRQ 126"); }
__attribute__((naked)) void irq_dummy_127() { die("IRQ 127"); }
__attribute__((naked)) void irq_dummy_128() { die("IRQ 128"); }
__attribute__((naked)) void irq_dummy_129() { die("IRQ 129"); }
__attribute__((naked)) void irq_dummy_130() { die("IRQ 130"); }
__attribute__((naked)) void irq_dummy_131() { die("IRQ 131"); }
__attribute__((naked)) void irq_dummy_132() { die("IRQ 132"); }
__attribute__((naked)) void irq_dummy_133() { die("IRQ 133"); }
__attribute__((naked)) void irq_dummy_134() { die("IRQ 134"); }
__attribute__((naked)) void irq_dummy_135() { die("IRQ 135"); }
__attribute__((naked)) void irq_dummy_136() { die("IRQ 136"); }
__attribute__((naked)) void irq_dummy_137() { die("IRQ 137"); }
__attribute__((naked)) void irq_dummy_138() { die("IRQ 138"); }
__attribute__((naked)) void irq_dummy_139() { die("IRQ 139"); }
__attribute__((naked)) void irq_dummy_140() { die("IRQ 140"); }
__attribute__((naked)) void irq_dummy_141() { die("IRQ 141"); }
__attribute__((naked)) void irq_dummy_142() { die("IRQ 142"); }
__attribute__((naked)) void irq_dummy_143() { die("IRQ 143"); }
__attribute__((naked)) void irq_dummy_144() { die("IRQ 144"); }
__attribute__((naked)) void irq_dummy_145() { die("IRQ 145"); }
__attribute__((naked)) void irq_dummy_146() { die("IRQ 146"); }
__attribute__((naked)) void irq_dummy_147() { die("IRQ 147"); }
__attribute__((naked)) void irq_dummy_148() { die("IRQ 148"); }
__attribute__((naked)) void irq_dummy_149() { die("IRQ 149"); }
__attribute__((naked)) void irq_dummy_150() { die("IRQ 150"); }
__attribute__((naked)) void irq_dummy_151() { die("IRQ 151"); }
__attribute__((naked)) void irq_dummy_152() { die("IRQ 152"); }
__attribute__((naked)) void irq_dummy_153() { die("IRQ 153"); }
__attribute__((naked)) void irq_dummy_154() { die("IRQ 154"); }
__attribute__((naked)) void irq_dummy_155() { die("IRQ 155"); }
__attribute__((naked)) void irq_dummy_156() { die("IRQ 156"); }
__attribute__((naked)) void irq_dummy_157() { die("IRQ 157"); }
__attribute__((naked)) void irq_dummy_158() { die("IRQ 158"); }
__attribute__((naked)) void irq_dummy_159() { die("IRQ 159"); }
__attribute__((naked)) void irq_dummy_160() { die("IRQ 160"); }
__attribute__((naked)) void irq_dummy_161() { die("IRQ 161"); }
__attribute__((naked)) void irq_dummy_162() { die("IRQ 162"); }
__attribute__((naked)) void irq_dummy_163() { die("IRQ 163"); }
__attribute__((naked)) void irq_dummy_164() { die("IRQ 164"); }
__attribute__((naked)) void irq_dummy_165() { die("IRQ 165"); }
__attribute__((naked)) void irq_dummy_166() { die("IRQ 166"); }
__attribute__((naked)) void irq_dummy_167() { die("IRQ 167"); }
__attribute__((naked)) void irq_dummy_168() { die("IRQ 168"); }
__attribute__((naked)) void irq_dummy_169() { die("IRQ 169"); }
__attribute__((naked)) void irq_dummy_170() { die("IRQ 170"); }
__attribute__((naked)) void irq_dummy_171() { die("IRQ 171"); }
__attribute__((naked)) void irq_dummy_172() { die("IRQ 172"); }
__attribute__((naked)) void irq_dummy_173() { die("IRQ 173"); }
__attribute__((naked)) void irq_dummy_174() { die("IRQ 174"); }
__attribute__((naked)) void irq_dummy_175() { die("IRQ 175"); }
__attribute__((naked)) void irq_dummy_176() { die("IRQ 176"); }
__attribute__((naked)) void irq_dummy_177() { die("IRQ 177"); }
__attribute__((naked)) void irq_dummy_178() { die("IRQ 178"); }
__attribute__((naked)) void irq_dummy_179() { die("IRQ 179"); }
__attribute__((naked)) void irq_dummy_180() { die("IRQ 180"); }
__attribute__((naked)) void irq_dummy_181() { die("IRQ 181"); }
__attribute__((naked)) void irq_dummy_182() { die("IRQ 182"); }
__attribute__((naked)) void irq_dummy_183() { die("IRQ 183"); }
__attribute__((naked)) void irq_dummy_184() { die("IRQ 184"); }
__attribute__((naked)) void irq_dummy_185() { die("IRQ 185"); }
__attribute__((naked)) void irq_dummy_186() { die("IRQ 186"); }
__attribute__((naked)) void irq_dummy_187() { die("IRQ 187"); }
__attribute__((naked)) void irq_dummy_188() { die("IRQ 188"); }
__attribute__((naked)) void irq_dummy_189() { die("IRQ 189"); }
__attribute__((naked)) void irq_dummy_190() { die("IRQ 190"); }
__attribute__((naked)) void irq_dummy_191() { die("IRQ 191"); }
__attribute__((naked)) void irq_dummy_192() { die("IRQ 192"); }
__attribute__((naked)) void irq_dummy_193() { die("IRQ 193"); }
__attribute__((naked)) void irq_dummy_194() { die("IRQ 194"); }
__attribute__((naked)) void irq_dummy_195() { die("IRQ 195"); }
__attribute__((naked)) void irq_dummy_196() { die("IRQ 196"); }
__attribute__((naked)) void irq_dummy_197() { die("IRQ 197"); }
__attribute__((naked)) void irq_dummy_198() { die("IRQ 198"); }
__attribute__((naked)) void irq_dummy_199() { die("IRQ 199"); }
__attribute__((naked)) void irq_dummy_200() { die("IRQ 200"); }
__attribute__((naked)) void irq_dummy_201() { die("IRQ 201"); }
__attribute__((naked)) void irq_dummy_202() { die("IRQ 202"); }
__attribute__((naked)) void irq_dummy_203() { die("IRQ 203"); }
__attribute__((naked)) void irq_dummy_204() { die("IRQ 204"); }
__attribute__((naked)) void irq_dummy_205() { die("IRQ 205"); }
__attribute__((naked)) void irq_dummy_206() { die("IRQ 206"); }
__attribute__((naked)) void irq_dummy_207() { die("IRQ 207"); }
__attribute__((naked)) void irq_dummy_208() { die("IRQ 208"); }
__attribute__((naked)) void irq_dummy_209() { die("IRQ 209"); }
__attribute__((naked)) void irq_dummy_210() { die("IRQ 210"); }
__attribute__((naked)) void irq_dummy_211() { die("IRQ 211"); }
__attribute__((naked)) void irq_dummy_212() { die("IRQ 212"); }
__attribute__((naked)) void irq_dummy_213() { die("IRQ 213"); }
__attribute__((naked)) void irq_dummy_214() { die("IRQ 214"); }
__attribute__((naked)) void irq_dummy_215() { die("IRQ 215"); }
__attribute__((naked)) void irq_dummy_216() { die("IRQ 216"); }
__attribute__((naked)) void irq_dummy_217() { die("IRQ 217"); }
__attribute__((naked)) void irq_dummy_218() { die("IRQ 218"); }
__attribute__((naked)) void irq_dummy_219() { die("IRQ 219"); }
__attribute__((naked)) void irq_dummy_220() { die("IRQ 220"); }
__attribute__((naked)) void irq_dummy_221() { die("IRQ 221"); }
__attribute__((naked)) void irq_dummy_222() { die("IRQ 222"); }
__attribute__((naked)) void irq_dummy_223() { die("IRQ 223"); }
__attribute__((naked)) void irq_dummy_224() { die("IRQ 224"); }
__attribute__((naked)) void irq_dummy_225() { die("IRQ 225"); }
__attribute__((naked)) void irq_dummy_226() { die("IRQ 226"); }
__attribute__((naked)) void irq_dummy_227() { die("IRQ 227"); }
__attribute__((naked)) void irq_dummy_228() { die("IRQ 228"); }
__attribute__((naked)) void irq_dummy_229() { die("IRQ 229"); }
__attribute__((naked)) void irq_dummy_230() { die("IRQ 230"); }
__attribute__((naked)) void irq_dummy_231() { die("IRQ 231"); }
__attribute__((naked)) void irq_dummy_232() { die("IRQ 232"); }
__attribute__((naked)) void irq_dummy_233() { die("IRQ 233"); }
__attribute__((naked)) void irq_dummy_234() { die("IRQ 234"); }
__attribute__((naked)) void irq_dummy_235() { die("IRQ 235"); }
__attribute__((naked)) void irq_dummy_236() { die("IRQ 236"); }
__attribute__((naked)) void irq_dummy_237() { die("IRQ 237"); }
__attribute__((naked)) void irq_dummy_238() { die("IRQ 238"); }
__attribute__((naked)) void irq_dummy_239() { die("IRQ 239"); }
__attribute__((naked)) void irq_dummy_240() { die("IRQ 240"); }
__attribute__((naked)) void irq_dummy_241() { die("IRQ 241"); }
__attribute__((naked)) void irq_dummy_242() { die("IRQ 242"); }
__attribute__((naked)) void irq_dummy_243() { die("IRQ 243"); }
__attribute__((naked)) void irq_dummy_244() { die("IRQ 244"); }
__attribute__((naked)) void irq_dummy_245() { die("IRQ 245"); }
__attribute__((naked)) void irq_dummy_246() { die("IRQ 246"); }
__attribute__((naked)) void irq_dummy_247() { die("IRQ 247"); }
__attribute__((naked)) void irq_dummy_248() { die("IRQ 248"); }
__attribute__((naked)) void irq_dummy_249() { die("IRQ 249"); }
__attribute__((naked)) void irq_dummy_250() { die("IRQ 250"); }
__attribute__((naked)) void irq_dummy_251() { die("IRQ 251"); }
__attribute__((naked)) void irq_dummy_252() { die("IRQ 252"); }
__attribute__((naked)) void irq_dummy_253() { die("IRQ 253"); }
__attribute__((naked)) void irq_dummy_254() { die("IRQ 254"); }
__attribute__((naked)) void irq_dummy_255() { die("IRQ 255"); }

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
    irq_dummy_table[17] = irq_dummy_17;
    irq_dummy_table[18] = irq_dummy_18;
    irq_dummy_table[19] = irq_dummy_19;
    irq_dummy_table[20] = irq_dummy_20;
    irq_dummy_table[21] = irq_dummy_21;
    irq_dummy_table[22] = irq_dummy_22;
    irq_dummy_table[23] = irq_dummy_23;
    irq_dummy_table[24] = irq_dummy_24;
    irq_dummy_table[25] = irq_dummy_25;
    irq_dummy_table[26] = irq_dummy_26;
    irq_dummy_table[27] = irq_dummy_27;
    irq_dummy_table[28] = irq_dummy_28;
    irq_dummy_table[29] = irq_dummy_29;
    irq_dummy_table[30] = irq_dummy_30;
    irq_dummy_table[31] = irq_dummy_31;
    irq_dummy_table[32] = irq_dummy_32;
    irq_dummy_table[33] = irq_dummy_33;
    irq_dummy_table[34] = irq_dummy_34;
    irq_dummy_table[35] = irq_dummy_35;
    irq_dummy_table[36] = irq_dummy_36;
    irq_dummy_table[37] = irq_dummy_37;
    irq_dummy_table[38] = irq_dummy_38;
    irq_dummy_table[39] = irq_dummy_39;
    irq_dummy_table[40] = irq_dummy_40;
    irq_dummy_table[41] = irq_dummy_41;
    irq_dummy_table[42] = irq_dummy_42;
    irq_dummy_table[43] = irq_dummy_43;
    irq_dummy_table[44] = irq_dummy_44;
    irq_dummy_table[45] = irq_dummy_45;
    irq_dummy_table[46] = irq_dummy_46;
    irq_dummy_table[47] = irq_dummy_47;
    irq_dummy_table[48] = irq_dummy_48;
    irq_dummy_table[49] = irq_dummy_49;
    irq_dummy_table[50] = irq_dummy_50;
    irq_dummy_table[51] = irq_dummy_51;
    irq_dummy_table[52] = irq_dummy_52;
    irq_dummy_table[53] = irq_dummy_53;
    irq_dummy_table[54] = irq_dummy_54;
    irq_dummy_table[55] = irq_dummy_55;
    irq_dummy_table[56] = irq_dummy_56;
    irq_dummy_table[57] = irq_dummy_57;
    irq_dummy_table[58] = irq_dummy_58;
    irq_dummy_table[59] = irq_dummy_59;
    irq_dummy_table[60] = irq_dummy_60;
    irq_dummy_table[61] = irq_dummy_61;
    irq_dummy_table[62] = irq_dummy_62;
    irq_dummy_table[63] = irq_dummy_63;
    irq_dummy_table[64] = irq_dummy_64;
    irq_dummy_table[65] = irq_dummy_65;
    irq_dummy_table[66] = irq_dummy_66;
    irq_dummy_table[67] = irq_dummy_67;
    irq_dummy_table[68] = irq_dummy_68;
    irq_dummy_table[69] = irq_dummy_69;
    irq_dummy_table[70] = irq_dummy_70;
    irq_dummy_table[71] = irq_dummy_71;
    irq_dummy_table[72] = irq_dummy_72;
    irq_dummy_table[73] = irq_dummy_73;
    irq_dummy_table[74] = irq_dummy_74;
    irq_dummy_table[75] = irq_dummy_75;
    irq_dummy_table[76] = irq_dummy_76;
    irq_dummy_table[77] = irq_dummy_77;
    irq_dummy_table[78] = irq_dummy_78;
    irq_dummy_table[79] = irq_dummy_79;
    irq_dummy_table[80] = irq_dummy_80;
    irq_dummy_table[81] = irq_dummy_81;
    irq_dummy_table[82] = irq_dummy_82;
    irq_dummy_table[83] = irq_dummy_83;
    irq_dummy_table[84] = irq_dummy_84;
    irq_dummy_table[85] = irq_dummy_85;
    irq_dummy_table[86] = irq_dummy_86;
    irq_dummy_table[87] = irq_dummy_87;
    irq_dummy_table[88] = irq_dummy_88;
    irq_dummy_table[89] = irq_dummy_89;
    irq_dummy_table[90] = irq_dummy_90;
    irq_dummy_table[91] = irq_dummy_91;
    irq_dummy_table[92] = irq_dummy_92;
    irq_dummy_table[93] = irq_dummy_93;
    irq_dummy_table[94] = irq_dummy_94;
    irq_dummy_table[95] = irq_dummy_95;
    irq_dummy_table[96] = irq_dummy_96;
    irq_dummy_table[97] = irq_dummy_97;
    irq_dummy_table[98] = irq_dummy_98;
    irq_dummy_table[99] = irq_dummy_99;
    irq_dummy_table[100] = irq_dummy_100;
    irq_dummy_table[101] = irq_dummy_101;
    irq_dummy_table[102] = irq_dummy_102;
    irq_dummy_table[103] = irq_dummy_103;
    irq_dummy_table[104] = irq_dummy_104;
    irq_dummy_table[105] = irq_dummy_105;
    irq_dummy_table[106] = irq_dummy_106;
    irq_dummy_table[107] = irq_dummy_107;
    irq_dummy_table[108] = irq_dummy_108;
    irq_dummy_table[109] = irq_dummy_109;
    irq_dummy_table[110] = irq_dummy_110;
    irq_dummy_table[111] = irq_dummy_111;
    irq_dummy_table[112] = irq_dummy_112;
    irq_dummy_table[113] = irq_dummy_113;
    irq_dummy_table[114] = irq_dummy_114;
    irq_dummy_table[115] = irq_dummy_115;
    irq_dummy_table[116] = irq_dummy_116;
    irq_dummy_table[117] = irq_dummy_117;
    irq_dummy_table[118] = irq_dummy_118;
    irq_dummy_table[119] = irq_dummy_119;
    irq_dummy_table[120] = irq_dummy_120;
    irq_dummy_table[121] = irq_dummy_121;
    irq_dummy_table[122] = irq_dummy_122;
    irq_dummy_table[123] = irq_dummy_123;
    irq_dummy_table[124] = irq_dummy_124;
    irq_dummy_table[125] = irq_dummy_125;
    irq_dummy_table[126] = irq_dummy_126;
    irq_dummy_table[127] = irq_dummy_127;
    irq_dummy_table[128] = irq_dummy_128;
    irq_dummy_table[129] = irq_dummy_129;
    irq_dummy_table[130] = irq_dummy_130;
    irq_dummy_table[131] = irq_dummy_131;
    irq_dummy_table[132] = irq_dummy_132;
    irq_dummy_table[133] = irq_dummy_133;
    irq_dummy_table[134] = irq_dummy_134;
    irq_dummy_table[135] = irq_dummy_135;
    irq_dummy_table[136] = irq_dummy_136;
    irq_dummy_table[137] = irq_dummy_137;
    irq_dummy_table[138] = irq_dummy_138;
    irq_dummy_table[139] = irq_dummy_139;
    irq_dummy_table[140] = irq_dummy_140;
    irq_dummy_table[141] = irq_dummy_141;
    irq_dummy_table[142] = irq_dummy_142;
    irq_dummy_table[143] = irq_dummy_143;
    irq_dummy_table[144] = irq_dummy_144;
    irq_dummy_table[145] = irq_dummy_145;
    irq_dummy_table[146] = irq_dummy_146;
    irq_dummy_table[147] = irq_dummy_147;
    irq_dummy_table[148] = irq_dummy_148;
    irq_dummy_table[149] = irq_dummy_149;
    irq_dummy_table[150] = irq_dummy_150;
    irq_dummy_table[151] = irq_dummy_151;
    irq_dummy_table[152] = irq_dummy_152;
    irq_dummy_table[153] = irq_dummy_153;
    irq_dummy_table[154] = irq_dummy_154;
    irq_dummy_table[155] = irq_dummy_155;
    irq_dummy_table[156] = irq_dummy_156;
    irq_dummy_table[157] = irq_dummy_157;
    irq_dummy_table[158] = irq_dummy_158;
    irq_dummy_table[159] = irq_dummy_159;
    irq_dummy_table[160] = irq_dummy_160;
    irq_dummy_table[161] = irq_dummy_161;
    irq_dummy_table[162] = irq_dummy_162;
    irq_dummy_table[163] = irq_dummy_163;
    irq_dummy_table[164] = irq_dummy_164;
    irq_dummy_table[165] = irq_dummy_165;
    irq_dummy_table[166] = irq_dummy_166;
    irq_dummy_table[167] = irq_dummy_167;
    irq_dummy_table[168] = irq_dummy_168;
    irq_dummy_table[169] = irq_dummy_169;
    irq_dummy_table[170] = irq_dummy_170;
    irq_dummy_table[171] = irq_dummy_171;
    irq_dummy_table[172] = irq_dummy_172;
    irq_dummy_table[173] = irq_dummy_173;
    irq_dummy_table[174] = irq_dummy_174;
    irq_dummy_table[175] = irq_dummy_175;
    irq_dummy_table[176] = irq_dummy_176;
    irq_dummy_table[177] = irq_dummy_177;
    irq_dummy_table[178] = irq_dummy_178;
    irq_dummy_table[179] = irq_dummy_179;
    irq_dummy_table[180] = irq_dummy_180;
    irq_dummy_table[181] = irq_dummy_181;
    irq_dummy_table[182] = irq_dummy_182;
    irq_dummy_table[183] = irq_dummy_183;
    irq_dummy_table[184] = irq_dummy_184;
    irq_dummy_table[185] = irq_dummy_185;
    irq_dummy_table[186] = irq_dummy_186;
    irq_dummy_table[187] = irq_dummy_187;
    irq_dummy_table[188] = irq_dummy_188;
    irq_dummy_table[189] = irq_dummy_189;
    irq_dummy_table[190] = irq_dummy_190;
    irq_dummy_table[191] = irq_dummy_191;
    irq_dummy_table[192] = irq_dummy_192;
    irq_dummy_table[193] = irq_dummy_193;
    irq_dummy_table[194] = irq_dummy_194;
    irq_dummy_table[195] = irq_dummy_195;
    irq_dummy_table[196] = irq_dummy_196;
    irq_dummy_table[197] = irq_dummy_197;
    irq_dummy_table[198] = irq_dummy_198;
    irq_dummy_table[199] = irq_dummy_199;
    irq_dummy_table[200] = irq_dummy_200;
    irq_dummy_table[201] = irq_dummy_201;
    irq_dummy_table[202] = irq_dummy_202;
    irq_dummy_table[203] = irq_dummy_203;
    irq_dummy_table[204] = irq_dummy_204;
    irq_dummy_table[205] = irq_dummy_205;
    irq_dummy_table[206] = irq_dummy_206;
    irq_dummy_table[207] = irq_dummy_207;
    irq_dummy_table[208] = irq_dummy_208;
    irq_dummy_table[209] = irq_dummy_209;
    irq_dummy_table[210] = irq_dummy_210;
    irq_dummy_table[211] = irq_dummy_211;
    irq_dummy_table[212] = irq_dummy_212;
    irq_dummy_table[213] = irq_dummy_213;
    irq_dummy_table[214] = irq_dummy_214;
    irq_dummy_table[215] = irq_dummy_215;
    irq_dummy_table[216] = irq_dummy_216;
    irq_dummy_table[217] = irq_dummy_217;
    irq_dummy_table[218] = irq_dummy_218;
    irq_dummy_table[219] = irq_dummy_219;
    irq_dummy_table[220] = irq_dummy_220;
    irq_dummy_table[221] = irq_dummy_221;
    irq_dummy_table[222] = irq_dummy_222;
    irq_dummy_table[223] = irq_dummy_223;
    irq_dummy_table[224] = irq_dummy_224;
    irq_dummy_table[225] = irq_dummy_225;
    irq_dummy_table[226] = irq_dummy_226;
    irq_dummy_table[227] = irq_dummy_227;
    irq_dummy_table[228] = irq_dummy_228;
    irq_dummy_table[229] = irq_dummy_229;
    irq_dummy_table[230] = irq_dummy_230;
    irq_dummy_table[231] = irq_dummy_231;
    irq_dummy_table[232] = irq_dummy_232;
    irq_dummy_table[233] = irq_dummy_233;
    irq_dummy_table[234] = irq_dummy_234;
    irq_dummy_table[235] = irq_dummy_235;
    irq_dummy_table[236] = irq_dummy_236;
    irq_dummy_table[237] = irq_dummy_237;
    irq_dummy_table[238] = irq_dummy_238;
    irq_dummy_table[239] = irq_dummy_239;
    irq_dummy_table[240] = irq_dummy_240;
    irq_dummy_table[241] = irq_dummy_241;
    irq_dummy_table[242] = irq_dummy_242;
    irq_dummy_table[243] = irq_dummy_243;
    irq_dummy_table[244] = irq_dummy_244;
    irq_dummy_table[245] = irq_dummy_245;
    irq_dummy_table[246] = irq_dummy_246;
    irq_dummy_table[247] = irq_dummy_247;
    irq_dummy_table[248] = irq_dummy_248;
    irq_dummy_table[249] = irq_dummy_249;
    irq_dummy_table[250] = irq_dummy_250;
    irq_dummy_table[251] = irq_dummy_251;
    irq_dummy_table[252] = irq_dummy_252;
    irq_dummy_table[253] = irq_dummy_253;
    irq_dummy_table[254] = irq_dummy_254;
    irq_dummy_table[255] = irq_dummy_255;
}
