program: main.c 
main.c content's: 
        #include "SFIio.c"
        int main() { 
             SFIwrite("main.c", 3, //hello, world);
        }

Valgrind repo: execution
==7081== Memcheck, a memory error detector
==7081== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==7081== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==7081== Command: ./a.out
==7081== 
==7081== 
==7081== HEAP SUMMARY:
==7081==     in use at exit: 0 bytes in 0 blocks
==7081==   total heap usage: 6 allocs, 6 frees, 9,581 bytes allocated
==7081== 
==7081== All heap blocks were freed -- no leaks are possible
==7081== 
==7081== For lists of detected and suppressed errors, rerun with: -s
==7081== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

main.c content's after execution:
       #include "SFIio.c"
       int main() {
           //hello, world
           SFIwrite("main.c", 3, //hello, world);
      }
