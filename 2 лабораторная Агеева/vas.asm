global _start

section .data
arr1 dw 0x8000, 0x4000, 0x801, 0x1, 0x2, 0x5, 0x6, 0x7, 0x9, 0xa

section .bss
arr2 resw 10

section .text 
_start:
    mov ecx, 10     ; Количество элементов в массиве
    mov esi, arr1   ; Адрес первого массива
    mov edi, arr2   ; Адрес второго массива
    xor eax, eax    ; Обнуляем eax
lp1:
    lodsw           ; Считываем слово в ax по адресу esi, инкреметируем esi
    not ah          ; Инвертируем старший байт
    stosw           ; Записываем слово по адресу в edi, инкреметируем edi
    loop lp1

    mov ecx, 10     ; Количество элементов в массиве
    mov esi, arr2   ; Адрес массива
    xor ebx, ebx    ; Обнуляем ebx
lp2:
    lodsw           ; Считываем слово в ax по адресу esi, инкреметируем esi
    test ax, 1      ; Проверяем на четность
    jnp is_odd      ; Проверяем флаг PF
    add ebx, eax    ; Добавляем число к сумме
is_odd:
    loop lp2

    mov eax, 1      ; Системный вызов exit
    mov ebx, 0      ; Код возврата
    int 0x80        ; Инициируем прерывание
