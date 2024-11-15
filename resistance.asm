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
extern free

resistance:
    push rbp
    mov rbp, rsp
    sub rsp, 80  ; Reserve stack space

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

    ; Get resistances - new dynamic version
    lea rdi, [rbp-32]  ; resistances array pointer
    lea rsi, [rbp-36]  ; count
    call get_resistance
    test eax, eax
    jz invalid_input

    mov rdi, input_success_msg
    xor eax, eax
    call printf

    ; Calculate resistance
    mov rdi, [rbp-32]  ; resistances array
    mov esi, [rbp-36]  ; count
    movsd xmm0, [rel default_voltage] ; default voltage 120.0V
    call compute_resistance
    mov [rbp-48], rax  ; Save CircuitResults pointer

    ; Get end time
    rdtsc
    shl rdx, 32
    or rax, rdx
    sub rax, [rbp-16]  ; Calculate elapsed ticks

    ; Show results with visualization
    mov rdi, [rbp-48]  ; CircuitResults pointer
    cvtsi2sd xmm0, rax   ; ticks
    movsd xmm1, [rbp-8]  ; frequency
    mov rsi, [rbp-32]    ; resistances array
    mov edx, [rbp-36]    ; count
    call show_resistance

    mov rdi, return_msg
    xor eax, eax
    call printf

    ; Get total resistance from CircuitResults
    mov rax, [rbp-48]
    movsd xmm0, [rax]  ; Load total_resistance

    ; Cleanup
    mov rdi, [rax+8]   ; Free currents array
    call free
    mov rdi, [rax+16]  ; Free powers array
    call free
    mov rdi, rax       ; Free CircuitResults struct
    call free
    mov rdi, [rbp-32]  ; Free resistances array
    call free

    jmp done

invalid_input:
    mov rdi, nonsense_msg
    xor eax, eax
    call printf
    xorpd xmm0, xmm0   ; Return 0.0

done:
    leave
    ret

section .data
    default_voltage: dq 120.0  ; Default voltage for the circuit
