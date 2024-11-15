section .data
    cpu_freq_msg db "Found CPU frequency (MHz): ", 0
    cpu_freq_err_msg db "Unable to find CPU frequency (MHz); Using default value: 3400", 10, 0
    input_success_msg db "Input successfully received.", 10, 0
    nonsense_msg db "You have entered nonsense; Returning 0.0 to the driver!", 10, 0
    return_msg db "Returning the resistance of the system to the driver.", 10, 0
    fmt_freq db "%s%d", 10, 0
    default_freq dq 3400.0

section .note.GNU-stack noalloc noexec nowrite progbits

section .text
global resistance
extern get_resistance
extern compute_resistance
extern show_resistance
extern printf

resistance:
    push rbp
    mov rbp, rsp
    sub rsp, 64  ; Reserve stack space

    ; Check CPU frequency
    mov eax, 0x0  ; Get max function ID
    cpuid
    cmp eax, 0x16  ; Check if frequency info is available
    jl use_default_freq

    mov eax, 0x16  ; Get CPU frequency
    cpuid
    test eax, eax
    jz use_default_freq
    
    ; CPU frequency found
    push rax                    ; Save CPU frequency
    sub rsp, 8                  ; Align stack for printf
    mov rdi, fmt_freq          ; Format string
    mov rsi, cpu_freq_msg      ; First argument
    mov rdx, [rsp+16]          ; Second argument (saved CPU frequency)
    xor eax, eax               ; No vector registers used
    call printf
    add rsp, 8                 ; Restore stack alignment
    pop rax                    ; Restore CPU frequency
    
    cvtsi2sd xmm0, eax
    movq [rbp-8], xmm0  ; Store frequency
    jmp freq_found

use_default_freq:
    mov rdi, cpu_freq_err_msg
    xor eax, eax
    call printf
    movsd xmm0, [default_freq]
    movq [rbp-8], xmm0

freq_found:
    ; Get start time
    rdtsc
    shl rdx, 32
    or rax, rdx
    mov [rbp-16], rax  ; Store start time

    ; Get resistances
    lea rdi, [rbp-48]  ; R1
    lea rsi, [rbp-40]  ; R2
    lea rdx, [rbp-32]  ; R3
    lea rcx, [rbp-24]  ; R4
    call get_resistance
    test eax, eax
    jz invalid_input

    mov rdi, input_success_msg
    xor eax, eax
    call printf

    ; Calculate resistance
    movsd xmm0, [rbp-48]
    movsd xmm1, [rbp-40]
    movsd xmm2, [rbp-32]
    movsd xmm3, [rbp-24]
    call compute_resistance

    ; Save result
    movq [rbp-56], xmm0

    ; Get end time
    rdtsc
    shl rdx, 32
    or rax, rdx
    sub rax, [rbp-16]  ; Calculate elapsed ticks

    ; Show results with visualization
    movq xmm0, [rbp-56]  ; resistance
    cvtsi2sd xmm1, rax   ; ticks
    movsd xmm2, [rbp-8]  ; frequency
    movsd xmm3, [rbp-48] ; r1
    movsd xmm4, [rbp-40] ; r2
    movsd xmm5, [rbp-32] ; r3
    movsd xmm6, [rbp-24] ; r4
    call show_resistance

    mov rdi, return_msg
    xor eax, eax
    call printf

    movq xmm0, [rbp-56]  ; Return resistance
    jmp done

invalid_input:
    mov rdi, nonsense_msg
    xor eax, eax
    call printf
    xorpd xmm0, xmm0   ; Return 0.0

done:
    leave
    ret
