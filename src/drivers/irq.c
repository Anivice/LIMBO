#include "irq.h"
#include "printk.h"

#define prefix() put('I'); put('R'); put('Q'); put(' ');

__attribute__((naked)) void irq_dummy_0() { prefix(); put('0'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_1() { prefix(); put('0'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_2() { prefix(); put('0'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_3() { prefix(); put('0'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_4() { prefix(); put('0'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_5() { prefix(); put('0'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_6() { prefix(); put('0'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_7() { prefix(); put('0'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_8() { prefix(); put('0'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_9() { prefix(); put('0'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_10() { prefix(); put('0'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_11() { prefix(); put('0'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_12() { prefix(); put('0'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_13() { prefix(); put('0'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_14() { prefix(); put('0'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_15() { prefix(); put('0'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_16() { prefix(); put('0'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_17() { prefix(); put('0'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_18() { prefix(); put('0'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_19() { prefix(); put('0'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_20() { prefix(); put('0'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_21() { prefix(); put('0'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_22() { prefix(); put('0'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_23() { prefix(); put('0'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_24() { prefix(); put('0'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_25() { prefix(); put('0'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_26() { prefix(); put('0'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_27() { prefix(); put('0'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_28() { prefix(); put('0'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_29() { prefix(); put('0'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_30() { prefix(); put('0'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_31() { prefix(); put('0'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_32() { prefix(); put('0'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_33() { prefix(); put('0'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_34() { prefix(); put('0'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_35() { prefix(); put('0'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_36() { prefix(); put('0'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_37() { prefix(); put('0'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_38() { prefix(); put('0'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_39() { prefix(); put('0'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_40() { prefix(); put('0'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_41() { prefix(); put('0'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_42() { prefix(); put('0'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_43() { prefix(); put('0'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_44() { prefix(); put('0'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_45() { prefix(); put('0'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_46() { prefix(); put('0'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_47() { prefix(); put('0'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_48() { prefix(); put('0'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_49() { prefix(); put('0'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_50() { prefix(); put('0'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_51() { prefix(); put('0'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_52() { prefix(); put('0'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_53() { prefix(); put('0'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_54() { prefix(); put('0'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_55() { prefix(); put('0'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_56() { prefix(); put('0'); put('5'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_57() { prefix(); put('0'); put('5'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_58() { prefix(); put('0'); put('5'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_59() { prefix(); put('0'); put('5'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_60() { prefix(); put('0'); put('6'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_61() { prefix(); put('0'); put('6'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_62() { prefix(); put('0'); put('6'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_63() { prefix(); put('0'); put('6'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_64() { prefix(); put('0'); put('6'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_65() { prefix(); put('0'); put('6'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_66() { prefix(); put('0'); put('6'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_67() { prefix(); put('0'); put('6'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_68() { prefix(); put('0'); put('6'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_69() { prefix(); put('0'); put('6'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_70() { prefix(); put('0'); put('7'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_71() { prefix(); put('0'); put('7'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_72() { prefix(); put('0'); put('7'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_73() { prefix(); put('0'); put('7'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_74() { prefix(); put('0'); put('7'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_75() { prefix(); put('0'); put('7'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_76() { prefix(); put('0'); put('7'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_77() { prefix(); put('0'); put('7'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_78() { prefix(); put('0'); put('7'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_79() { prefix(); put('0'); put('7'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_80() { prefix(); put('0'); put('8'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_81() { prefix(); put('0'); put('8'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_82() { prefix(); put('0'); put('8'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_83() { prefix(); put('0'); put('8'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_84() { prefix(); put('0'); put('8'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_85() { prefix(); put('0'); put('8'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_86() { prefix(); put('0'); put('8'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_87() { prefix(); put('0'); put('8'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_88() { prefix(); put('0'); put('8'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_89() { prefix(); put('0'); put('8'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_90() { prefix(); put('0'); put('9'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_91() { prefix(); put('0'); put('9'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_92() { prefix(); put('0'); put('9'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_93() { prefix(); put('0'); put('9'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_94() { prefix(); put('0'); put('9'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_95() { prefix(); put('0'); put('9'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_96() { prefix(); put('0'); put('9'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_97() { prefix(); put('0'); put('9'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_98() { prefix(); put('0'); put('9'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_99() { prefix(); put('0'); put('9'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_100() { prefix(); put('1'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_101() { prefix(); put('1'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_102() { prefix(); put('1'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_103() { prefix(); put('1'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_104() { prefix(); put('1'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_105() { prefix(); put('1'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_106() { prefix(); put('1'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_107() { prefix(); put('1'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_108() { prefix(); put('1'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_109() { prefix(); put('1'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_110() { prefix(); put('1'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_111() { prefix(); put('1'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_112() { prefix(); put('1'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_113() { prefix(); put('1'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_114() { prefix(); put('1'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_115() { prefix(); put('1'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_116() { prefix(); put('1'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_117() { prefix(); put('1'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_118() { prefix(); put('1'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_119() { prefix(); put('1'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_120() { prefix(); put('1'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_121() { prefix(); put('1'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_122() { prefix(); put('1'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_123() { prefix(); put('1'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_124() { prefix(); put('1'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_125() { prefix(); put('1'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_126() { prefix(); put('1'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_127() { prefix(); put('1'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_128() { prefix(); put('1'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_129() { prefix(); put('1'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_130() { prefix(); put('1'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_131() { prefix(); put('1'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_132() { prefix(); put('1'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_133() { prefix(); put('1'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_134() { prefix(); put('1'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_135() { prefix(); put('1'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_136() { prefix(); put('1'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_137() { prefix(); put('1'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_138() { prefix(); put('1'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_139() { prefix(); put('1'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_140() { prefix(); put('1'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_141() { prefix(); put('1'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_142() { prefix(); put('1'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_143() { prefix(); put('1'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_144() { prefix(); put('1'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_145() { prefix(); put('1'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_146() { prefix(); put('1'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_147() { prefix(); put('1'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_148() { prefix(); put('1'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_149() { prefix(); put('1'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_150() { prefix(); put('1'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_151() { prefix(); put('1'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_152() { prefix(); put('1'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_153() { prefix(); put('1'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_154() { prefix(); put('1'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_155() { prefix(); put('1'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_156() { prefix(); put('1'); put('5'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_157() { prefix(); put('1'); put('5'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_158() { prefix(); put('1'); put('5'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_159() { prefix(); put('1'); put('5'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_160() { prefix(); put('1'); put('6'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_161() { prefix(); put('1'); put('6'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_162() { prefix(); put('1'); put('6'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_163() { prefix(); put('1'); put('6'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_164() { prefix(); put('1'); put('6'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_165() { prefix(); put('1'); put('6'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_166() { prefix(); put('1'); put('6'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_167() { prefix(); put('1'); put('6'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_168() { prefix(); put('1'); put('6'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_169() { prefix(); put('1'); put('6'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_170() { prefix(); put('1'); put('7'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_171() { prefix(); put('1'); put('7'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_172() { prefix(); put('1'); put('7'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_173() { prefix(); put('1'); put('7'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_174() { prefix(); put('1'); put('7'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_175() { prefix(); put('1'); put('7'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_176() { prefix(); put('1'); put('7'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_177() { prefix(); put('1'); put('7'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_178() { prefix(); put('1'); put('7'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_179() { prefix(); put('1'); put('7'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_180() { prefix(); put('1'); put('8'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_181() { prefix(); put('1'); put('8'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_182() { prefix(); put('1'); put('8'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_183() { prefix(); put('1'); put('8'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_184() { prefix(); put('1'); put('8'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_185() { prefix(); put('1'); put('8'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_186() { prefix(); put('1'); put('8'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_187() { prefix(); put('1'); put('8'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_188() { prefix(); put('1'); put('8'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_189() { prefix(); put('1'); put('8'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_190() { prefix(); put('1'); put('9'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_191() { prefix(); put('1'); put('9'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_192() { prefix(); put('1'); put('9'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_193() { prefix(); put('1'); put('9'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_194() { prefix(); put('1'); put('9'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_195() { prefix(); put('1'); put('9'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_196() { prefix(); put('1'); put('9'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_197() { prefix(); put('1'); put('9'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_198() { prefix(); put('1'); put('9'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_199() { prefix(); put('1'); put('9'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_200() { prefix(); put('2'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_201() { prefix(); put('2'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_202() { prefix(); put('2'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_203() { prefix(); put('2'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_204() { prefix(); put('2'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_205() { prefix(); put('2'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_206() { prefix(); put('2'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_207() { prefix(); put('2'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_208() { prefix(); put('2'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_209() { prefix(); put('2'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_210() { prefix(); put('2'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_211() { prefix(); put('2'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_212() { prefix(); put('2'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_213() { prefix(); put('2'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_214() { prefix(); put('2'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_215() { prefix(); put('2'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_216() { prefix(); put('2'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_217() { prefix(); put('2'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_218() { prefix(); put('2'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_219() { prefix(); put('2'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_220() { prefix(); put('2'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_221() { prefix(); put('2'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_222() { prefix(); put('2'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_223() { prefix(); put('2'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_224() { prefix(); put('2'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_225() { prefix(); put('2'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_226() { prefix(); put('2'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_227() { prefix(); put('2'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_228() { prefix(); put('2'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_229() { prefix(); put('2'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_230() { prefix(); put('2'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_231() { prefix(); put('2'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_232() { prefix(); put('2'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_233() { prefix(); put('2'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_234() { prefix(); put('2'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_235() { prefix(); put('2'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_236() { prefix(); put('2'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_237() { prefix(); put('2'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_238() { prefix(); put('2'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_239() { prefix(); put('2'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_240() { prefix(); put('2'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_241() { prefix(); put('2'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_242() { prefix(); put('2'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_243() { prefix(); put('2'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_244() { prefix(); put('2'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_245() { prefix(); put('2'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_246() { prefix(); put('2'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_247() { prefix(); put('2'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_248() { prefix(); put('2'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_249() { prefix(); put('2'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_250() { prefix(); put('2'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_251() { prefix(); put('2'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_252() { prefix(); put('2'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_253() { prefix(); put('2'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_254() { prefix(); put('2'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_255() { prefix(); put('2'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }

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
