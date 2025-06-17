#include "irq.h"
#include "printk.h"

__attribute__((naked)) void irq_dummy_0() { put('0'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_1() { put('0'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_2() { put('0'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_3() { put('0'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_4() { put('0'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_5() { put('0'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_6() { put('0'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_7() { put('0'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_8() { put('0'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_9() { put('0'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_10() { put('0'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_11() { put('0'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_12() { put('0'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_13() { put('0'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_14() { put('0'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_15() { put('0'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_16() { put('0'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_17() { put('0'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_18() { put('0'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_19() { put('0'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_20() { put('0'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_21() { put('0'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_22() { put('0'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_23() { put('0'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_24() { put('0'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_25() { put('0'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_26() { put('0'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_27() { put('0'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_28() { put('0'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_29() { put('0'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_30() { put('0'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_31() { put('0'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_32() { put('0'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_33() { put('0'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_34() { put('0'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_35() { put('0'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_36() { put('0'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_37() { put('0'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_38() { put('0'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_39() { put('0'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_40() { put('0'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_41() { put('0'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_42() { put('0'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_43() { put('0'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_44() { put('0'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_45() { put('0'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_46() { put('0'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_47() { put('0'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_48() { put('0'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_49() { put('0'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_50() { put('0'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_51() { put('0'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_52() { put('0'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_53() { put('0'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_54() { put('0'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_55() { put('0'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_56() { put('0'); put('5'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_57() { put('0'); put('5'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_58() { put('0'); put('5'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_59() { put('0'); put('5'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_60() { put('0'); put('6'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_61() { put('0'); put('6'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_62() { put('0'); put('6'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_63() { put('0'); put('6'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_64() { put('0'); put('6'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_65() { put('0'); put('6'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_66() { put('0'); put('6'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_67() { put('0'); put('6'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_68() { put('0'); put('6'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_69() { put('0'); put('6'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_70() { put('0'); put('7'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_71() { put('0'); put('7'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_72() { put('0'); put('7'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_73() { put('0'); put('7'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_74() { put('0'); put('7'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_75() { put('0'); put('7'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_76() { put('0'); put('7'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_77() { put('0'); put('7'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_78() { put('0'); put('7'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_79() { put('0'); put('7'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_80() { put('0'); put('8'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_81() { put('0'); put('8'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_82() { put('0'); put('8'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_83() { put('0'); put('8'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_84() { put('0'); put('8'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_85() { put('0'); put('8'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_86() { put('0'); put('8'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_87() { put('0'); put('8'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_88() { put('0'); put('8'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_89() { put('0'); put('8'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_90() { put('0'); put('9'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_91() { put('0'); put('9'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_92() { put('0'); put('9'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_93() { put('0'); put('9'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_94() { put('0'); put('9'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_95() { put('0'); put('9'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_96() { put('0'); put('9'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_97() { put('0'); put('9'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_98() { put('0'); put('9'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_99() { put('0'); put('9'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_100() { put('1'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_101() { put('1'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_102() { put('1'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_103() { put('1'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_104() { put('1'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_105() { put('1'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_106() { put('1'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_107() { put('1'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_108() { put('1'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_109() { put('1'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_110() { put('1'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_111() { put('1'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_112() { put('1'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_113() { put('1'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_114() { put('1'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_115() { put('1'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_116() { put('1'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_117() { put('1'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_118() { put('1'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_119() { put('1'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_120() { put('1'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_121() { put('1'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_122() { put('1'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_123() { put('1'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_124() { put('1'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_125() { put('1'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_126() { put('1'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_127() { put('1'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_128() { put('1'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_129() { put('1'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_130() { put('1'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_131() { put('1'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_132() { put('1'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_133() { put('1'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_134() { put('1'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_135() { put('1'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_136() { put('1'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_137() { put('1'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_138() { put('1'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_139() { put('1'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_140() { put('1'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_141() { put('1'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_142() { put('1'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_143() { put('1'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_144() { put('1'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_145() { put('1'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_146() { put('1'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_147() { put('1'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_148() { put('1'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_149() { put('1'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_150() { put('1'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_151() { put('1'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_152() { put('1'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_153() { put('1'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_154() { put('1'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_155() { put('1'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_156() { put('1'); put('5'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_157() { put('1'); put('5'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_158() { put('1'); put('5'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_159() { put('1'); put('5'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_160() { put('1'); put('6'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_161() { put('1'); put('6'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_162() { put('1'); put('6'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_163() { put('1'); put('6'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_164() { put('1'); put('6'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_165() { put('1'); put('6'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_166() { put('1'); put('6'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_167() { put('1'); put('6'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_168() { put('1'); put('6'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_169() { put('1'); put('6'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_170() { put('1'); put('7'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_171() { put('1'); put('7'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_172() { put('1'); put('7'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_173() { put('1'); put('7'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_174() { put('1'); put('7'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_175() { put('1'); put('7'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_176() { put('1'); put('7'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_177() { put('1'); put('7'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_178() { put('1'); put('7'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_179() { put('1'); put('7'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_180() { put('1'); put('8'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_181() { put('1'); put('8'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_182() { put('1'); put('8'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_183() { put('1'); put('8'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_184() { put('1'); put('8'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_185() { put('1'); put('8'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_186() { put('1'); put('8'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_187() { put('1'); put('8'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_188() { put('1'); put('8'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_189() { put('1'); put('8'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_190() { put('1'); put('9'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_191() { put('1'); put('9'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_192() { put('1'); put('9'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_193() { put('1'); put('9'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_194() { put('1'); put('9'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_195() { put('1'); put('9'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_196() { put('1'); put('9'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_197() { put('1'); put('9'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_198() { put('1'); put('9'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_199() { put('1'); put('9'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_200() { put('2'); put('0'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_201() { put('2'); put('0'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_202() { put('2'); put('0'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_203() { put('2'); put('0'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_204() { put('2'); put('0'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_205() { put('2'); put('0'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_206() { put('2'); put('0'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_207() { put('2'); put('0'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_208() { put('2'); put('0'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_209() { put('2'); put('0'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_210() { put('2'); put('1'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_211() { put('2'); put('1'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_212() { put('2'); put('1'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_213() { put('2'); put('1'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_214() { put('2'); put('1'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_215() { put('2'); put('1'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_216() { put('2'); put('1'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_217() { put('2'); put('1'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_218() { put('2'); put('1'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_219() { put('2'); put('1'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_220() { put('2'); put('2'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_221() { put('2'); put('2'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_222() { put('2'); put('2'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_223() { put('2'); put('2'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_224() { put('2'); put('2'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_225() { put('2'); put('2'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_226() { put('2'); put('2'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_227() { put('2'); put('2'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_228() { put('2'); put('2'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_229() { put('2'); put('2'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_230() { put('2'); put('3'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_231() { put('2'); put('3'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_232() { put('2'); put('3'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_233() { put('2'); put('3'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_234() { put('2'); put('3'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_235() { put('2'); put('3'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_236() { put('2'); put('3'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_237() { put('2'); put('3'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_238() { put('2'); put('3'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_239() { put('2'); put('3'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_240() { put('2'); put('4'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_241() { put('2'); put('4'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_242() { put('2'); put('4'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_243() { put('2'); put('4'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_244() { put('2'); put('4'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_245() { put('2'); put('4'); put('5'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_246() { put('2'); put('4'); put('6'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_247() { put('2'); put('4'); put('7'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_248() { put('2'); put('4'); put('8'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_249() { put('2'); put('4'); put('9'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_250() { put('2'); put('5'); put('0'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_251() { put('2'); put('5'); put('1'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_252() { put('2'); put('5'); put('2'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_253() { put('2'); put('5'); put('3'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_254() { put('2'); put('5'); put('4'); put('\n'); __asm__ __volatile__("iret"); }
__attribute__((naked)) void irq_dummy_255() { put('2'); put('5'); put('5'); put('\n'); __asm__ __volatile__("iret"); }

void * irq_table[256];

void irq_dummies_init()
{
    irq_table[0] = irq_dummy_0;
    irq_table[1] = irq_dummy_1;
    irq_table[2] = irq_dummy_2;
    irq_table[3] = irq_dummy_3;
    irq_table[4] = irq_dummy_4;
    irq_table[5] = irq_dummy_5;
    irq_table[6] = irq_dummy_6;
    irq_table[7] = irq_dummy_7;
    irq_table[8] = irq_dummy_8;
    irq_table[9] = irq_dummy_9;
    irq_table[10] = irq_dummy_10;
    irq_table[11] = irq_dummy_11;
    irq_table[12] = irq_dummy_12;
    irq_table[13] = irq_dummy_13;
    irq_table[14] = irq_dummy_14;
    irq_table[15] = irq_dummy_15;
    irq_table[16] = irq_dummy_16;
    irq_table[17] = irq_dummy_17;
    irq_table[18] = irq_dummy_18;
    irq_table[19] = irq_dummy_19;
    irq_table[20] = irq_dummy_20;
    irq_table[21] = irq_dummy_21;
    irq_table[22] = irq_dummy_22;
    irq_table[23] = irq_dummy_23;
    irq_table[24] = irq_dummy_24;
    irq_table[25] = irq_dummy_25;
    irq_table[26] = irq_dummy_26;
    irq_table[27] = irq_dummy_27;
    irq_table[28] = irq_dummy_28;
    irq_table[29] = irq_dummy_29;
    irq_table[30] = irq_dummy_30;
    irq_table[31] = irq_dummy_31;
    irq_table[32] = irq_dummy_32;
    irq_table[33] = irq_dummy_33;
    irq_table[34] = irq_dummy_34;
    irq_table[35] = irq_dummy_35;
    irq_table[36] = irq_dummy_36;
    irq_table[37] = irq_dummy_37;
    irq_table[38] = irq_dummy_38;
    irq_table[39] = irq_dummy_39;
    irq_table[40] = irq_dummy_40;
    irq_table[41] = irq_dummy_41;
    irq_table[42] = irq_dummy_42;
    irq_table[43] = irq_dummy_43;
    irq_table[44] = irq_dummy_44;
    irq_table[45] = irq_dummy_45;
    irq_table[46] = irq_dummy_46;
    irq_table[47] = irq_dummy_47;
    irq_table[48] = irq_dummy_48;
    irq_table[49] = irq_dummy_49;
    irq_table[50] = irq_dummy_50;
    irq_table[51] = irq_dummy_51;
    irq_table[52] = irq_dummy_52;
    irq_table[53] = irq_dummy_53;
    irq_table[54] = irq_dummy_54;
    irq_table[55] = irq_dummy_55;
    irq_table[56] = irq_dummy_56;
    irq_table[57] = irq_dummy_57;
    irq_table[58] = irq_dummy_58;
    irq_table[59] = irq_dummy_59;
    irq_table[60] = irq_dummy_60;
    irq_table[61] = irq_dummy_61;
    irq_table[62] = irq_dummy_62;
    irq_table[63] = irq_dummy_63;
    irq_table[64] = irq_dummy_64;
    irq_table[65] = irq_dummy_65;
    irq_table[66] = irq_dummy_66;
    irq_table[67] = irq_dummy_67;
    irq_table[68] = irq_dummy_68;
    irq_table[69] = irq_dummy_69;
    irq_table[70] = irq_dummy_70;
    irq_table[71] = irq_dummy_71;
    irq_table[72] = irq_dummy_72;
    irq_table[73] = irq_dummy_73;
    irq_table[74] = irq_dummy_74;
    irq_table[75] = irq_dummy_75;
    irq_table[76] = irq_dummy_76;
    irq_table[77] = irq_dummy_77;
    irq_table[78] = irq_dummy_78;
    irq_table[79] = irq_dummy_79;
    irq_table[80] = irq_dummy_80;
    irq_table[81] = irq_dummy_81;
    irq_table[82] = irq_dummy_82;
    irq_table[83] = irq_dummy_83;
    irq_table[84] = irq_dummy_84;
    irq_table[85] = irq_dummy_85;
    irq_table[86] = irq_dummy_86;
    irq_table[87] = irq_dummy_87;
    irq_table[88] = irq_dummy_88;
    irq_table[89] = irq_dummy_89;
    irq_table[90] = irq_dummy_90;
    irq_table[91] = irq_dummy_91;
    irq_table[92] = irq_dummy_92;
    irq_table[93] = irq_dummy_93;
    irq_table[94] = irq_dummy_94;
    irq_table[95] = irq_dummy_95;
    irq_table[96] = irq_dummy_96;
    irq_table[97] = irq_dummy_97;
    irq_table[98] = irq_dummy_98;
    irq_table[99] = irq_dummy_99;
    irq_table[100] = irq_dummy_100;
    irq_table[101] = irq_dummy_101;
    irq_table[102] = irq_dummy_102;
    irq_table[103] = irq_dummy_103;
    irq_table[104] = irq_dummy_104;
    irq_table[105] = irq_dummy_105;
    irq_table[106] = irq_dummy_106;
    irq_table[107] = irq_dummy_107;
    irq_table[108] = irq_dummy_108;
    irq_table[109] = irq_dummy_109;
    irq_table[110] = irq_dummy_110;
    irq_table[111] = irq_dummy_111;
    irq_table[112] = irq_dummy_112;
    irq_table[113] = irq_dummy_113;
    irq_table[114] = irq_dummy_114;
    irq_table[115] = irq_dummy_115;
    irq_table[116] = irq_dummy_116;
    irq_table[117] = irq_dummy_117;
    irq_table[118] = irq_dummy_118;
    irq_table[119] = irq_dummy_119;
    irq_table[120] = irq_dummy_120;
    irq_table[121] = irq_dummy_121;
    irq_table[122] = irq_dummy_122;
    irq_table[123] = irq_dummy_123;
    irq_table[124] = irq_dummy_124;
    irq_table[125] = irq_dummy_125;
    irq_table[126] = irq_dummy_126;
    irq_table[127] = irq_dummy_127;
    irq_table[128] = irq_dummy_128;
    irq_table[129] = irq_dummy_129;
    irq_table[130] = irq_dummy_130;
    irq_table[131] = irq_dummy_131;
    irq_table[132] = irq_dummy_132;
    irq_table[133] = irq_dummy_133;
    irq_table[134] = irq_dummy_134;
    irq_table[135] = irq_dummy_135;
    irq_table[136] = irq_dummy_136;
    irq_table[137] = irq_dummy_137;
    irq_table[138] = irq_dummy_138;
    irq_table[139] = irq_dummy_139;
    irq_table[140] = irq_dummy_140;
    irq_table[141] = irq_dummy_141;
    irq_table[142] = irq_dummy_142;
    irq_table[143] = irq_dummy_143;
    irq_table[144] = irq_dummy_144;
    irq_table[145] = irq_dummy_145;
    irq_table[146] = irq_dummy_146;
    irq_table[147] = irq_dummy_147;
    irq_table[148] = irq_dummy_148;
    irq_table[149] = irq_dummy_149;
    irq_table[150] = irq_dummy_150;
    irq_table[151] = irq_dummy_151;
    irq_table[152] = irq_dummy_152;
    irq_table[153] = irq_dummy_153;
    irq_table[154] = irq_dummy_154;
    irq_table[155] = irq_dummy_155;
    irq_table[156] = irq_dummy_156;
    irq_table[157] = irq_dummy_157;
    irq_table[158] = irq_dummy_158;
    irq_table[159] = irq_dummy_159;
    irq_table[160] = irq_dummy_160;
    irq_table[161] = irq_dummy_161;
    irq_table[162] = irq_dummy_162;
    irq_table[163] = irq_dummy_163;
    irq_table[164] = irq_dummy_164;
    irq_table[165] = irq_dummy_165;
    irq_table[166] = irq_dummy_166;
    irq_table[167] = irq_dummy_167;
    irq_table[168] = irq_dummy_168;
    irq_table[169] = irq_dummy_169;
    irq_table[170] = irq_dummy_170;
    irq_table[171] = irq_dummy_171;
    irq_table[172] = irq_dummy_172;
    irq_table[173] = irq_dummy_173;
    irq_table[174] = irq_dummy_174;
    irq_table[175] = irq_dummy_175;
    irq_table[176] = irq_dummy_176;
    irq_table[177] = irq_dummy_177;
    irq_table[178] = irq_dummy_178;
    irq_table[179] = irq_dummy_179;
    irq_table[180] = irq_dummy_180;
    irq_table[181] = irq_dummy_181;
    irq_table[182] = irq_dummy_182;
    irq_table[183] = irq_dummy_183;
    irq_table[184] = irq_dummy_184;
    irq_table[185] = irq_dummy_185;
    irq_table[186] = irq_dummy_186;
    irq_table[187] = irq_dummy_187;
    irq_table[188] = irq_dummy_188;
    irq_table[189] = irq_dummy_189;
    irq_table[190] = irq_dummy_190;
    irq_table[191] = irq_dummy_191;
    irq_table[192] = irq_dummy_192;
    irq_table[193] = irq_dummy_193;
    irq_table[194] = irq_dummy_194;
    irq_table[195] = irq_dummy_195;
    irq_table[196] = irq_dummy_196;
    irq_table[197] = irq_dummy_197;
    irq_table[198] = irq_dummy_198;
    irq_table[199] = irq_dummy_199;
    irq_table[200] = irq_dummy_200;
    irq_table[201] = irq_dummy_201;
    irq_table[202] = irq_dummy_202;
    irq_table[203] = irq_dummy_203;
    irq_table[204] = irq_dummy_204;
    irq_table[205] = irq_dummy_205;
    irq_table[206] = irq_dummy_206;
    irq_table[207] = irq_dummy_207;
    irq_table[208] = irq_dummy_208;
    irq_table[209] = irq_dummy_209;
    irq_table[210] = irq_dummy_210;
    irq_table[211] = irq_dummy_211;
    irq_table[212] = irq_dummy_212;
    irq_table[213] = irq_dummy_213;
    irq_table[214] = irq_dummy_214;
    irq_table[215] = irq_dummy_215;
    irq_table[216] = irq_dummy_216;
    irq_table[217] = irq_dummy_217;
    irq_table[218] = irq_dummy_218;
    irq_table[219] = irq_dummy_219;
    irq_table[220] = irq_dummy_220;
    irq_table[221] = irq_dummy_221;
    irq_table[222] = irq_dummy_222;
    irq_table[223] = irq_dummy_223;
    irq_table[224] = irq_dummy_224;
    irq_table[225] = irq_dummy_225;
    irq_table[226] = irq_dummy_226;
    irq_table[227] = irq_dummy_227;
    irq_table[228] = irq_dummy_228;
    irq_table[229] = irq_dummy_229;
    irq_table[230] = irq_dummy_230;
    irq_table[231] = irq_dummy_231;
    irq_table[232] = irq_dummy_232;
    irq_table[233] = irq_dummy_233;
    irq_table[234] = irq_dummy_234;
    irq_table[235] = irq_dummy_235;
    irq_table[236] = irq_dummy_236;
    irq_table[237] = irq_dummy_237;
    irq_table[238] = irq_dummy_238;
    irq_table[239] = irq_dummy_239;
    irq_table[240] = irq_dummy_240;
    irq_table[241] = irq_dummy_241;
    irq_table[242] = irq_dummy_242;
    irq_table[243] = irq_dummy_243;
    irq_table[244] = irq_dummy_244;
    irq_table[245] = irq_dummy_245;
    irq_table[246] = irq_dummy_246;
    irq_table[247] = irq_dummy_247;
    irq_table[248] = irq_dummy_248;
    irq_table[249] = irq_dummy_249;
    irq_table[250] = irq_dummy_250;
    irq_table[251] = irq_dummy_251;
    irq_table[252] = irq_dummy_252;
    irq_table[253] = irq_dummy_253;
    irq_table[254] = irq_dummy_254;
    irq_table[255] = irq_dummy_255;
}
