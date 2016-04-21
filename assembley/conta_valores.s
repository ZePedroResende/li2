  .file   "contar.c"
        .text
        .p2align 2,,3
.globl contar_valores
        .type   contar_valores,@function
contar_valores:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        movl    8(%ebp), %esi
        movl    12(%ebp), %edi
        movl    16(%ebp), %ecx
        xorl    %ebx, %ebx
        xorl    %edx, %edx
        .p2align 2,,3
.L6:
        movl    $0, (%ecx,%edx,4)
        incl    %edx
        cmpl    $12, %edx
        jle     .L6
        xorl    %edx, %edx
        cmpl    %edi, %edx
        jge     .L16
        .p2align 2,,3
.L12:
        movl    4(%esi,%edx,8), %eax
        incl    (%ecx,%eax,4)
        movl    4(%esi,%edx,8), %eax
        movl    (%ecx,%eax,4), %eax
        cmpl    %ebx, %eax
        jle     .L9
        movl    %eax, %ebx
.L9:
        incl    %edx
        cmpl    %edi, %edx
        jl      .L12
.L16:
        movl    %ebx, %eax
        popl    %ebx
        popl    %esi
        popl    %edi
        leave
        ret
.Lfe1:
        .size   contar_valores,.Lfe1-contar_valores
        .section        .rodata
        .align 4
.LC0:
        .long   2
        .long   7
        .long   2
        .long   0
        .long   3
        .long   7
        .long   0
        .long   2
        .long   3
        .long   12
        .long   2
        .long   3
        .long   0
        .long   11
        .long   3
        .long   0
        .long   1
        .long   5
        .long   0
        .long   5
        .long   2
        .long   4
        .long   2
        .long   1
        .long   2
        .long   7
        .section        .rodata.str1.1,"aMS",@progbits,1
.LC1:
        .string "%d\t"
.LC2:
        .string "%3d"
        .text
        .p2align 2,,3
.globl main
        .type   main,@function
main:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %edi
        pushl   %esi
        subl    $176, %esp
        andl    $-16, %esp
        subl    $20, %esp
        leal    -184(%ebp), %eax
        pushl   %eax
        pushl   $13
        leal    -120(%ebp), %eax
        cld
        pushl   %eax
        leal    -120(%ebp), %edi
        movl    $.LC0, %esi
        movl    $26, %ecx
        rep
        movsl
        call    contar_valores
        addl    $24, %esp
        pushl   %eax
        pushl   $.LC1
        call    printf
        xorl    %esi, %esi
        addl    $16, %esp
        .p2align 2,,3
.L22:
        subl    $8, %esp
        pushl   -184(%ebp,%esi,4)
        pushl   $.LC2
        incl    %esi
        call    printf
        addl    $16, %esp
        cmpl    $12, %esi
        jle     .L22
        subl    $12, %esp
        pushl   $10
        call    putchar
        leal    -8(%ebp), %esp
        popl    %esi
        xorl    %eax, %eax
        popl    %edi
        leave
        ret

