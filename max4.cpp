#include <iostream>
using namespace std;
/**
 * 这就是传说中的函数模板
 * 以前用的都是值参数
 * 这里用的是类型参数,类型参数化
 * T是类型形参
 */
template<typename T>  //类似宏定义
T max(T x,T y){       //类似宏替换
    return x > y ? x : y;
}
int main(void){
    /**
     * max<int>这里的int是类型实参
     */
    cout << ::max<int>(100,200) << endl;
    cout << ::max<string>("hello","world") << endl;
    cout << ::max<double>(3.14,5.66) << endl;
    return 0;
}
#if 0
zn@zn-OptiPlex-9010:~/demo/121915$ g++ max4.cpp 
zn@zn-OptiPlex-9010:~/demo/121915$ nm a.out  看二进制文件
00000000006020b8 B __bss_start
00000000006021d0 b completed.6973
                 U __cxa_atexit@@GLIBC_2.2.5
00000000006020a8 D __data_start
00000000006020a8 W data_start
0000000000400b60 t deregister_tm_clones
0000000000400bd0 t __do_global_dtors_aux
0000000000601df8 t __do_global_dtors_aux_fini_array_entry
00000000006020b0 D __dso_handle
0000000000601e08 d _DYNAMIC
00000000006020b8 D _edata
00000000006021d8 B _end
0000000000400f44 T _fini
0000000000400bf0 t frame_dummy
0000000000601de8 t __frame_dummy_init_array_entry
00000000004011b0 r __FRAME_END__
0000000000602000 d _GLOBAL_OFFSET_TABLE_
0000000000400df9 t _GLOBAL__sub_I_main
                 w __gmon_start__
                 U __gxx_personality_v0@@CXXABI_1.3
00000000004009d8 T _init
0000000000601df8 t __init_array_end
0000000000601de8 t __init_array_start
0000000000400f50 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000601e00 d __JCR_END__
0000000000601e00 d __JCR_LIST__
                 w _Jv_RegisterClasses
0000000000400f40 T __libc_csu_fini
0000000000400ed0 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
0000000000400c1d T main
                 w __pthread_key_create
0000000000400b90 t register_tm_clones
0000000000400b30 T _start
00000000006020b8 D __TMC_END__
                 U _Unwind_Resume@@GCC_3.0
0000000000400e74 W _Z3maxIdET_S0_S0_    max_double
0000000000400e0e W _Z3maxIiET_S0_S0_      max_int
0000000000400e2a W _Z3maxISsET_S0_S0_   max_string
0000000000400dbc t _Z41__static_initialization_and_destruction_0ii
                 U _ZNKSs7compareERKSs@@GLIBCXX_3.4
                 U _ZNSaIcEC1Ev@@GLIBCXX_3.4
                 U _ZNSaIcED1Ev@@GLIBCXX_3.4
                 U _ZNSolsEd@@GLIBCXX_3.4
                 U _ZNSolsEi@@GLIBCXX_3.4
                 U _ZNSolsEPFRSoS_E@@GLIBCXX_3.4
                 U _ZNSsC1EPKcRKSaIcE@@GLIBCXX_3.4
                 U _ZNSsC1ERKSs@@GLIBCXX_3.4
                 U _ZNSsD1Ev@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitC1Ev@@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4
00000000006020c0 B _ZSt4cout@@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4
0000000000400ea3 W _ZStgtIcSt11char_traitsIcESaIcEEbRKSbIT_T0_T1_ES8_
00000000006021d1 b _ZStL8__ioinit
                 U _ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E@@GLIBCXX_3.4
0000000000400f68 r _ZZL18__gthread_active_pvE20__gthread_active_ptr
#endif
