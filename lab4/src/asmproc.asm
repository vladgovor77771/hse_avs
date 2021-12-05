section .text

; Процедура вычисления ключа
global CalcKey
CalcKey:
    mov rsi,rdi ; rdi - аргумент фукции, указатель на struct Data
    ; Загружаем ссылку на данные и копируем в rsi для чтения
    lodsq
    mov rsi,rax
    
    ; Очистка регистров для накопления суммы и количества
    xor r10,r10
    xor r11,r11
cicle1:
    ; Здесь грузим байьт из rsi, и если он нулевой - то конец цикла
    xor rax,rax
    lodsb 
    cmp al,0
    je fin1    
    ; иначе увеличиваем сумму и количество
    add r10,rax
    inc r11
    jmp cicle1

fin1:
    ; Делим сумму на количество как вещественное число, его вернем в регистре xmm0
    cvtsi2ss xmm0,r10
    cvtsi2ss xmm1,r11
    divss xmm0,xmm1
        
    ret

    ; Вычисление индекса алфавита по символу
    ; здесь передаем через al и возвращаем через al
char2index:
    ; проверяем, не в диапазоне ли 0-9
    cmp al,'9'
    jg next1
    sub al,'0' ; диапазон индексов алфавита - 0-9
    ret
    ; проверяем, не в диапазоне ли A-Z
next1:    
    cmp al,'Z'
    jg next2
    sub al,'A' 
    add al,36 ; диапазон индексов алфавита - 35-61
    ret
    ; осталось только a-z
next2:    
    sub al,'a' 
    add al,10 ; диапазон индексов алфавита - 10-35
    ret
    
    ; Вычисление символа по индексу алфавита
    ; здесь передаем через al и возвращаем через al
index2char:
    ; проверяем, не в диапазоне ли 0-9
    cmp al,9
    jg next3
    add al,'0' ; диапазон индексов алфавита - 0-9
    ret
    ; проверяем, не в диапазоне ли a-z
next3:    
    cmp al,35
    jg next4
    sub al,10
    add al,'a' ; диапазон индексов алфавита - 10-35     
    ret
    ; осталось только A-Z
next4:    
    sub al,36
    add al,'A' ; диапазон индексов алфавита - 36-61     
    ret
    
    ; Процедура шифрования сдвигом
    global EncryptShift
EncryptShift:
    mov rsi,rdi ; rdi - аргумент фукции, указатель на struct Data
    
    lodsq
    mov r10,rax ; запомним указатель на строку
    add rsi,4 ; пропускаем 4 байта типа шифрования
    xor rax,rax
    lodsd ; грузим число сдвига
    mov r11,rax ; запоминаем число сдвига    
    add rsi,4 ; пропускаем еще 4 байта данных шифрования    
    lodsq ; грузим начало выходной строки
    mov rsi,r10 ; Теперь здесь указатель на входные данные
    mov rdi,rax ; А тут выходные
        
cicle2:
    ; Грузим байт из строки, если он нулевой - то выход из цикла
    xor rax,rax
    lodsb 
    cmp al,0
    je fin2    
        
    ; Иначе переводим символ в код порядковый, добавляем сдвиг, делим на длину алфавита 
    ; забираем остаток как новый символ и снова переводим, но уже обратно код в символ алфавита
    call char2index
    add rax,r11
    mov r12,62
    xor rdx,rdx
    div r12
    mov al,dl
    call index2char
    
    ; Запоминаем результат в выходную строку
    stosb    
    jmp cicle2
    
fin2:
    mov al,0 ; Ставим терминальный нуль
    stosb
    
    ret    

    ; Процедура шифрования заменой
    global EncryptChar
EncryptChar:
    mov rsi,rdi
    ; rsi - аргумент фукции, указатель на struct Data
    lodsq
    mov r10,rax ; запомним указатель на строку
    add rsi,4 ; пропускаем 4 байта типа шифрования
    xor rax,rax
    lodsq ; грузим начало таблицы
    mov r11,rax ; запоминаем начало таблицы замены
    lodsq ; грузим начало выходной строки
    mov rsi,r10 ; Теперь здесь указатель на входные данные
    mov rdi,rax ; А тут выходные  
        
cicle3:
    ; Грузим байт из строки, если он нулевой - то выход из цикла
    xor rax,rax
    lodsb 
    cmp al,0
    je fin3
     
    ; иначе переводим символ в код
    call char2index
    push rsi ; сохраним указатель на исходную строку
    mov rsi,r11 ; ставим указатель на строку замену
    add rsi,rax ; сдвигаем указатель на значение кода символа - аналог rsi[rax]
    lodsb  ; считываем символ замены   
    pop rsi ; Восстановим указатель на исходную строку
    stosb ; и пишем в выходную строку новый символ   
    jmp cicle3
    
fin3:
    mov al,0 ; Ставим терминальный нуль
    stosb    
    ret    

; Процедура шифрования заменой на числа
global EncryptNum
EncryptNum:
    mov rsi,rdi ; rdi - аргумент фукции, указатель на struct Data    
    lodsq
    mov r10,rax ; запомним указатель на строку
    add rsi,4 ; пропускаем 4 байта типа шифрования
    xor rax,rax
    lodsq ; грузим начало таблицы
    mov r11,rax ; запоминаем начало таблицы замены
    lodsq ; грузим начало выходной строки
    mov rsi,r10 ; Теперь здесь указатель на входные данные
    mov rdi,rax ; А тут выходные    
        
cicle4:
   ; Грузим байт из строки, если он нулевой - то выход из цикла
    xor rax,rax
    lodsb 
    cmp al,0
    je fin4
        
    ; иначе переводим символ в код
    call char2index
    push rsi ; сохраним указатель на исходную строку
    mov rsi,r11 ; ставим указатель на строку замену
    add rsi,rax ; сдвигаем указатель на значение кода символа - аналог rsi[rax]
    lodsb  ; читаем число из строки замены  
    pop rsi ; Восстановим указатель на исходную строку
    stosb  ; и пишем в выходную строку новое число      
    jmp cicle4
    
fin4:
    
    ; здесь не нужен терминальный нуль - выходные данные это массив чисел
    
    ret    


    ; Процедура шифрования
    global EncryptData
EncryptData:
    mov rsi,rdi  ; rdi - аргумент фукции, указатель на struct Data

    ; Пропускаем первые 8 байт
    add rsi,8    
    lodsd ; Загружаем код шифрования и разветвляемся в зависимости от типа
    cmp eax,0
    je labEncryptShift
    cmp eax,1
    je labEncryptChar    
    
    call EncryptNum
    ret
    
labEncryptShift:
    call EncryptShift
    ret

labEncryptChar:
    call EncryptChar
    ret


; Внутренняя процедура - обмен двух 8-байтных чисел по индексу в массиве
ProcSwap:    
    push rax
    push rbx 
    push rcx
    push rdx
    
    ; Переводим индекс в размер, умножив на 8
    mov rax,rdi
    mov r12,8
    mul r12
    add rax,r10 ;  Добавляем к указателю начала массива
    mov rsi,rax
    
    lodsq    
    mov rcx,rax ; rcx - буфер для обмена (аналог переменной tmp)
    
    lodsq    
    ; Теперь у нас в rcx - первое значение, а в rax - второе
    ; ставим выходной указатель, возвращаемся на 16 байт назад
    mov rdi,rsi
    sub rdi,16
    stosq ; и записываем оба регистра, но в обратном порядке
    
    mov rax,rcx ; из буфера для обмена
    stosq

    pop rdx
    pop rcx
    pop rbx
    pop rax    
    ret

; Внутреняя процедура вычисления ключа по индексу - передаем индекс массива, 
; получаем в xmm0 значение ключа
CalcKeyByIndex:    
    push rax
    push rbx
    push rcx
    push rdx
    push r9
    push r10
    push r11
    
    ; Переводим индекс в размер, умножив на 8
    mov rax,rdi
    mov r12,8
    mul r12
    add rax,r10 ;  Добавляем к указателю начала массива
    mov rsi,rax 
    lodsq  ; Загружаем адрес структуры
    mov rdi,rax ;  и вызываем процедуру вычисления ключа
    call CalcKey
    
    pop r11
    pop r10
    pop r9
    pop rdx
    pop rcx
    pop rbx    
    pop rax
    ret

    ; Процедура сортировки
    global DoSort:function
DoSort:
    
    mov r10,rdi ; Запоминаем указатель на массив
    mov r11,rsi ; Запоминаем число значений в массиве
                                
mainloop:        
    mov r9,0
    mov rax,0 ; в регистре текущий индекс
    mov rbx,r11
    dec rbx ; Здесь число сравнений
sortloop:        
    ; Вычисление и сравнение ключей
    mov rdi,rax
    call CalcKeyByIndex
    movss xmm9,xmm0
    
    mov rdi,rax
    inc rdi            
    call CalcKeyByIndex
    
    ; Сравнениваем два вещественных числа
    cmpss xmm9,xmm0,6
    movmskps edx,xmm9
    cmp edx,0
    ; Если порядок правильный, то конец
    je skipexc 
    ; Иначе передаем индекс для обмена
    mov rdi,rax
    call ProcSwap
    mov r9,1

skipexc:    
   ; Нужно делать обмен, пока не дошли до конца
    inc rax
    cmp rax,rbx
    jl sortloop 
        
     ; но если обмен так и не случился, то конец обработке
    cmp r9,1
    je mainloop
    
    ret

    
