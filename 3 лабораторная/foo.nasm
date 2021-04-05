global foo

section .text
; DWORD foo(DWORD dst, DWORD src, DWORD n)
foo:
    push ebp
    mov ebp, esp

    sub esp, 4 ; объявляем локальную переменную

    mov edi, [ebp+8]  ; адрес первого массива
    mov esi, [ebp+12] ; адрес второго массива
    mov ecx, [ebp+16] ; количество элементов
    mov DWORD [ebp-4], 0
.lp:
    mov eax, [esi]
    mul DWORD [edi]
    add DWORD [ebp-4], eax ; сохраняем результат в локальной переменной
    add esi, 4 ; переходим к следующему элементу в первом массиве
    add edi, 4 ; переходим к следующему элементу во втором массиве
    loop .lp

    mov eax, DWORD [ebp-4] ; сохраняем результат из локальной переменной
    add esp, 4 ; удаляем локальную переменную

    mov esp, ebp
    pop ebp
    ret
