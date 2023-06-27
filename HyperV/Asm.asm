
_text segment

fwrap macro a, b
	sub rsp, 10h
	cvtss2sd xmm0, xmm0
	movsd qword ptr [rsp], xmm0
	fld qword ptr [rsp]
	a
	b
	fstp qword ptr [rsp]
	movsd xmm0, qword ptr [rsp]
	cvtsd2ss xmm0, xmm0
	add rsp, 10h
	ret
endm

HyperCall proc
  cpuid
  ret
HyperCall endp

CupCallEx proc
  push r9
  push r10
  push r11
  push r12
  push r8
  mov rax, r8
  mov r12,[rax + 0h]
  mov r8, [rax + 8h]
  mov r9, [rax + 10h]
  mov r10,[rax + 18h]
  mov r11,[rax + 20h]
  cpuid
  mov rcx, r8 
  pop r8
  mov [r8 + 0],r12
  mov [r8 + 8h],rcx
  mov [r8 + 10h],r9
  mov [r8 + 18h],r10
  mov [r8 + 20h],r11
  pop r12
  pop r11
  pop r10
  pop r9
  ret
CupCallEx endp

NtQuerySystemInformationEx proc
  mov r10, rcx
  mov eax, 36h 
  syscall 
  ret
NtQuerySystemInformationEx endp

VmCallEx proc 
  vmcall  ; RCX, RDX, R8, R9 
  ret
VmCallEx endp

__sqrtf proc
	fwrap fsqrt
__sqrtf endp

__sinf proc
	fwrap fsin
__sinf endp

__cosf proc
	fwrap fcos
__cosf endp

__tanf proc
	fwrap fptan, fmulp
__tanf endp

_text ends

end