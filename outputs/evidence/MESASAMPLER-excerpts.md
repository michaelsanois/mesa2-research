# MESASAMPLER static disassembly excerpts

Source identity: 4ff7d6457038c2f9035bb734ab046f8488ebb30a992b74a3c48a0a5fde4785b0

Tool: /usr/bin/objdump -d --x86-asm-syntax=intel. Preferred PE virtual addresses; inferred function boundaries, no execution or decompiler. Data/jump tables can be decoded as instructions in linear output; do not treat them as executable facts.

## 0x10003ba0–0x10003be3

File start offset: 0x3ba0

```asm
10003ba0: 8b 54 24 10                  	mov	edx, dword ptr [esp + 0x10]
10003ba4: 33 c9                        	xor	ecx, ecx
10003ba6: 85 d2                        	test	edx, edx
10003ba8: 76 39                        	jbe	0x10003be3 <.text+0x2be3>
10003baa: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003bae: 53                           	push	ebx
10003baf: 55                           	push	ebp
10003bb0: 8b 6c 24 0c                  	mov	ebp, dword ptr [esp + 0xc]
10003bb4: 56                           	push	esi
10003bb5: 57                           	push	edi
10003bb6: 8b 7c 24 1c                  	mov	edi, dword ptr [esp + 0x1c]
10003bba: 8a 1c 39                     	mov	bl, byte ptr [ecx + edi]
10003bbd: 8b 30                        	mov	esi, dword ptr [eax]
10003bbf: 80 e3 0f                     	and	bl, 0xf
10003bc2: 88 1c 2e                     	mov	byte ptr [esi + ebp], bl
10003bc5: 8b 18                        	mov	ebx, dword ptr [eax]
10003bc7: 43                           	inc	ebx
10003bc8: 89 18                        	mov	dword ptr [eax], ebx
10003bca: 8b f3                        	mov	esi, ebx
10003bcc: 8a 1c 39                     	mov	bl, byte ptr [ecx + edi]
10003bcf: c0 eb 04                     	shr	bl, 0x4
10003bd2: 88 1c 2e                     	mov	byte ptr [esi + ebp], bl
10003bd5: 8b 30                        	mov	esi, dword ptr [eax]
10003bd7: 46                           	inc	esi
10003bd8: 41                           	inc	ecx
10003bd9: 3b ca                        	cmp	ecx, edx
10003bdb: 89 30                        	mov	dword ptr [eax], esi
10003bdd: 72 db                        	jb	0x10003bba <.text+0x2bba>
10003bdf: 5f                           	pop	edi
10003be0: 5e                           	pop	esi
10003be1: 5d                           	pop	ebp
10003be2: 5b                           	pop	ebx
10003be3: c2 10 00                     	ret	0x10
```

## 0x10003c30–0x10003c68

File start offset: 0x3c30

```asm
10003c30: 66 8b 44 24 04               	mov	ax, word ptr [esp + 0x4]
10003c35: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003c39: 56                           	push	esi
10003c3a: 8b 74 24 0c                  	mov	esi, dword ptr [esp + 0xc]
10003c3e: 57                           	push	edi
10003c3f: 8b 39                        	mov	edi, dword ptr [ecx]
10003c41: 8a d0                        	mov	dl, al
10003c43: 80 e2 7f                     	and	dl, 0x7f
10003c46: 88 14 37                     	mov	byte ptr [edi + esi], dl
10003c49: 8b 11                        	mov	edx, dword ptr [ecx]
10003c4b: 0f bf c0                     	movsx	eax, ax
10003c4e: 42                           	inc	edx
10003c4f: 89 11                        	mov	dword ptr [ecx], edx
10003c51: 8b fa                        	mov	edi, edx
10003c53: 99                           	cdq
10003c54: 83 e2 7f                     	and	edx, 0x7f
10003c57: 03 c2                        	add	eax, edx
10003c59: c1 f8 07                     	sar	eax, 0x7
10003c5c: 24 7f                        	and	al, 0x7f
10003c5e: 88 04 37                     	mov	byte ptr [edi + esi], al
10003c61: 8b 01                        	mov	eax, dword ptr [ecx]
10003c63: 40                           	inc	eax
10003c64: 5f                           	pop	edi
10003c65: 89 01                        	mov	dword ptr [ecx], eax
10003c67: 5e                           	pop	esi
10003c68: c2 0c 00                     	ret	0xc
```

## 0x10003cc0–0x10003d09

File start offset: 0x3cc0

```asm
10003cc0: 53                           	push	ebx
10003cc1: 55                           	push	ebp
10003cc2: 56                           	push	esi
10003cc3: 8b 74 24 10                  	mov	esi, dword ptr [esp + 0x10]
10003cc7: 57                           	push	edi
10003cc8: 33 ff                        	xor	edi, edi
10003cca: bd 0c 00 00 00               	mov	ebp, 0xc
10003ccf: 8a 0e                        	mov	cl, byte ptr [esi]
10003cd1: 84 c9                        	test	cl, cl
10003cd3: 75 11                        	jne	0x10003ce6 <.text+0x2ce6>
10003cd5: bf 01 00 00 00               	mov	edi, 0x1
10003cda: c6 06 0a                     	mov	byte ptr [esi], 0xa
10003cdd: 46                           	inc	esi
10003cde: 4d                           	dec	ebp
10003cdf: 75 ee                        	jne	0x10003ccf <.text+0x2ccf>
10003ce1: 5f                           	pop	edi
10003ce2: 5e                           	pop	esi
10003ce3: 5d                           	pop	ebp
10003ce4: 5b                           	pop	ebx
10003ce5: c3                           	ret
10003ce6: 85 ff                        	test	edi, edi
10003ce8: 75 f0                        	jne	0x10003cda <.text+0x2cda>
10003cea: 33 c0                        	xor	eax, eax
10003cec: 0f be c9                     	movsx	ecx, cl
10003cef: 0f bf d0                     	movsx	edx, ax
10003cf2: 33 db                        	xor	ebx, ebx
10003cf4: 8a 9a 60 6f 05 10            	mov	bl, byte ptr [edx + 0x10056f60]
10003cfa: 3b d9                        	cmp	ebx, ecx
10003cfc: 74 09                        	je	0x10003d07 <.text+0x2d07>
10003cfe: 40                           	inc	eax
10003cff: 66 3d 2a 00                  	cmp	ax, 0x2a
10003d03: 7c ea                        	jl	0x10003cef <.text+0x2cef>
10003d05: eb d6                        	jmp	0x10003cdd <.text+0x2cdd>
10003d07: 88 06                        	mov	byte ptr [esi], al
10003d09: eb d2                        	jmp	0x10003cdd <.text+0x2cdd>
```

## 0x10003d10–0x10003f04

File start offset: 0x3d10

```asm
10003d10: 8b 44 24 04                  	mov	eax, dword ptr [esp + 0x4]
10003d14: 8a 54 24 08                  	mov	dl, byte ptr [esp + 0x8]
10003d18: c6 00 f0                     	mov	byte ptr [eax], -0x10
10003d1b: c6 40 01 47                  	mov	byte ptr [eax + 0x1], 0x47
10003d1f: 8a 09                        	mov	cl, byte ptr [ecx]
10003d21: 88 48 02                     	mov	byte ptr [eax + 0x2], cl
10003d24: 88 50 03                     	mov	byte ptr [eax + 0x3], dl
10003d27: c6 40 04 48                  	mov	byte ptr [eax + 0x4], 0x48
10003d2b: b8 05 00 00 00               	mov	eax, 0x5
10003d30: c2 08 00                     	ret	0x8
10003d33: 90                           	nop
10003d34: 90                           	nop
10003d35: 90                           	nop
10003d36: 90                           	nop
10003d37: 90                           	nop
10003d38: 90                           	nop
10003d39: 90                           	nop
10003d3a: 90                           	nop
10003d3b: 90                           	nop
10003d3c: 90                           	nop
10003d3d: 90                           	nop
10003d3e: 90                           	nop
10003d3f: 90                           	nop
10003d40: 51                           	push	ecx
10003d41: 53                           	push	ebx
10003d42: 8b 5c 24 0c                  	mov	ebx, dword ptr [esp + 0xc]
10003d46: 56                           	push	esi
10003d47: 8b 74 24 20                  	mov	esi, dword ptr [esp + 0x20]
10003d4b: 57                           	push	edi
10003d4c: 53                           	push	ebx
10003d4d: 8b f9                        	mov	edi, ecx
10003d4f: 56                           	push	esi
10003d50: c7 44 24 14 00 00 00 00      	mov	dword ptr [esp + 0x14], 0x0
10003d58: e8 b3 ff ff ff               	call	0x10003d10 <.text+0x2d10>
10003d5d: 89 44 24 0c                  	mov	dword ptr [esp + 0xc], eax
10003d61: 8b c3                        	mov	eax, ebx
10003d63: 25 ff 00 00 00               	and	eax, 0xff
10003d68: 83 f8 42                     	cmp	eax, 0x42
10003d6b: 0f 87 82 01 00 00            	ja	0x10003ef3 <.text+0x2ef3>
10003d71: 33 c9                        	xor	ecx, ecx
10003d73: 8a 88 2c 3f 00 10            	mov	cl, byte ptr [eax + 0x10003f2c]
10003d79: ff 24 8d 08 3f 00 10         	jmp	dword ptr [4*ecx + 0x10003f08]
10003d80: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
10003d84: 8d 54 24 0c                  	lea	edx, [esp + 0xc]
10003d88: 52                           	push	edx
10003d89: 56                           	push	esi
10003d8a: 50                           	push	eax
10003d8b: 8b cf                        	mov	ecx, edi
10003d8d: e8 9e fe ff ff               	call	0x10003c30 <.text+0x2c30>
10003d92: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003d96: 5f                           	pop	edi
10003d97: c6 04 31 f7                  	mov	byte ptr [ecx + esi], -0x9
10003d9b: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003d9f: 5e                           	pop	esi
10003da0: 40                           	inc	eax
10003da1: 5b                           	pop	ebx
10003da2: 59                           	pop	ecx
10003da3: c2 1c 00                     	ret	0x1c
10003da6: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
10003daa: 8d 4c 24 0c                  	lea	ecx, [esp + 0xc]
10003dae: 51                           	push	ecx
10003daf: 56                           	push	esi
10003db0: 52                           	push	edx
10003db1: 8b cf                        	mov	ecx, edi
10003db3: e8 78 fe ff ff               	call	0x10003c30 <.text+0x2c30>
10003db8: 8b 44 24 0c                  	mov	eax, dword ptr [esp + 0xc]
10003dbc: 8a 4c 24 1c                  	mov	cl, byte ptr [esp + 0x1c]
10003dc0: 5f                           	pop	edi
10003dc1: 88 0c 30                     	mov	byte ptr [eax + esi], cl
10003dc4: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003dc8: 40                           	inc	eax
10003dc9: 8b c8                        	mov	ecx, eax
10003dcb: 89 44 24 08                  	mov	dword ptr [esp + 0x8], eax
10003dcf: c6 04 31 f7                  	mov	byte ptr [ecx + esi], -0x9
10003dd3: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003dd7: 5e                           	pop	esi
10003dd8: 40                           	inc	eax
10003dd9: 5b                           	pop	ebx
10003dda: 59                           	pop	ecx
10003ddb: c2 1c 00                     	ret	0x1c
10003dde: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
10003de2: 8d 54 24 0c                  	lea	edx, [esp + 0xc]
10003de6: 52                           	push	edx
10003de7: 56                           	push	esi
10003de8: 50                           	push	eax
10003de9: 8b cf                        	mov	ecx, edi
10003deb: e8 40 fe ff ff               	call	0x10003c30 <.text+0x2c30>
10003df0: 8b 4c 24 28                  	mov	ecx, dword ptr [esp + 0x28]
10003df4: 51                           	push	ecx
10003df5: e9 e7 00 00 00               	jmp	0x10003ee1 <.text+0x2ee1>
10003dfa: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
10003dfe: 8d 4c 24 0c                  	lea	ecx, [esp + 0xc]
10003e02: 51                           	push	ecx
10003e03: 56                           	push	esi
10003e04: 52                           	push	edx
10003e05: 8b cf                        	mov	ecx, edi
10003e07: e8 24 fe ff ff               	call	0x10003c30 <.text+0x2c30>
10003e0c: 8b 44 24 0c                  	mov	eax, dword ptr [esp + 0xc]
10003e10: 8a 4c 24 1c                  	mov	cl, byte ptr [esp + 0x1c]
10003e14: 88 0c 30                     	mov	byte ptr [eax + esi], cl
10003e17: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003e1b: 41                           	inc	ecx
10003e1c: 89 4c 24 0c                  	mov	dword ptr [esp + 0xc], ecx
10003e20: 8b 54 24 28                  	mov	edx, dword ptr [esp + 0x28]
10003e24: 8b 44 24 2c                  	mov	eax, dword ptr [esp + 0x2c]
10003e28: 52                           	push	edx
10003e29: 8d 4c 24 10                  	lea	ecx, [esp + 0x10]
10003e2d: 50                           	push	eax
10003e2e: 51                           	push	ecx
10003e2f: e9 b7 00 00 00               	jmp	0x10003eeb <.text+0x2eeb>
10003e34: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
10003e38: 8d 54 24 0c                  	lea	edx, [esp + 0xc]
10003e3c: 52                           	push	edx
10003e3d: 56                           	push	esi
10003e3e: 50                           	push	eax
10003e3f: 8b cf                        	mov	ecx, edi
10003e41: e8 ea fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003e46: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003e4a: 8a 54 24 1c                  	mov	dl, byte ptr [esp + 0x1c]
10003e4e: 8d 44 24 0c                  	lea	eax, [esp + 0xc]
10003e52: 88 14 31                     	mov	byte ptr [ecx + esi], dl
10003e55: 8b 5c 24 0c                  	mov	ebx, dword ptr [esp + 0xc]
10003e59: 8b 4c 24 20                  	mov	ecx, dword ptr [esp + 0x20]
10003e5d: 50                           	push	eax
10003e5e: 56                           	push	esi
10003e5f: 43                           	inc	ebx
10003e60: 51                           	push	ecx
10003e61: 8b cf                        	mov	ecx, edi
10003e63: 89 5c 24 18                  	mov	dword ptr [esp + 0x18], ebx
10003e67: e8 c4 fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003e6c: 8b 44 24 28                  	mov	eax, dword ptr [esp + 0x28]
10003e70: 8d 54 24 0c                  	lea	edx, [esp + 0xc]
10003e74: 52                           	push	edx
10003e75: 56                           	push	esi
10003e76: 50                           	push	eax
10003e77: 8b cf                        	mov	ecx, edi
10003e79: e8 b2 fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003e7e: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003e82: 5f                           	pop	edi
10003e83: c6 04 31 f7                  	mov	byte ptr [ecx + esi], -0x9
10003e87: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003e8b: 5e                           	pop	esi
10003e8c: 40                           	inc	eax
10003e8d: 5b                           	pop	ebx
10003e8e: 59                           	pop	ecx
10003e8f: c2 1c 00                     	ret	0x1c
10003e92: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
10003e96: 8d 4c 24 0c                  	lea	ecx, [esp + 0xc]
10003e9a: 51                           	push	ecx
10003e9b: 56                           	push	esi
10003e9c: 52                           	push	edx
10003e9d: 8b cf                        	mov	ecx, edi
10003e9f: e8 8c fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003ea4: 8b 44 24 0c                  	mov	eax, dword ptr [esp + 0xc]
10003ea8: 8a 4c 24 1c                  	mov	cl, byte ptr [esp + 0x1c]
10003eac: 8d 54 24 0c                  	lea	edx, [esp + 0xc]
10003eb0: 88 0c 30                     	mov	byte ptr [eax + esi], cl
10003eb3: 8b 44 24 0c                  	mov	eax, dword ptr [esp + 0xc]
10003eb7: 40                           	inc	eax
10003eb8: 52                           	push	edx
10003eb9: 89 44 24 10                  	mov	dword ptr [esp + 0x10], eax
10003ebd: 8b 44 24 24                  	mov	eax, dword ptr [esp + 0x24]
10003ec1: 56                           	push	esi
10003ec2: 50                           	push	eax
10003ec3: 8b cf                        	mov	ecx, edi
10003ec5: e8 66 fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003eca: 8b 5c 24 28                  	mov	ebx, dword ptr [esp + 0x28]
10003ece: 8d 4c 24 0c                  	lea	ecx, [esp + 0xc]
10003ed2: 51                           	push	ecx
10003ed3: 56                           	push	esi
10003ed4: 53                           	push	ebx
10003ed5: 8b cf                        	mov	ecx, edi
10003ed7: e8 54 fd ff ff               	call	0x10003c30 <.text+0x2c30>
10003edc: 85 db                        	test	ebx, ebx
10003ede: 74 13                        	je	0x10003ef3 <.text+0x2ef3>
10003ee0: 53                           	push	ebx
10003ee1: 8b 54 24 30                  	mov	edx, dword ptr [esp + 0x30]
10003ee5: 8d 44 24 10                  	lea	eax, [esp + 0x10]
10003ee9: 52                           	push	edx
10003eea: 50                           	push	eax
10003eeb: 56                           	push	esi
10003eec: 8b cf                        	mov	ecx, edi
10003eee: e8 ad fc ff ff               	call	0x10003ba0 <.text+0x2ba0>
10003ef3: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10003ef7: 5f                           	pop	edi
10003ef8: c6 04 31 f7                  	mov	byte ptr [ecx + esi], -0x9
10003efc: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10003f00: 5e                           	pop	esi
10003f01: 40                           	inc	eax
10003f02: 5b                           	pop	ebx
10003f03: 59                           	pop	ecx
10003f04: c2 1c 00                     	ret	0x1c
```

## 0x10006480–0x1000655f

File start offset: 0x6480

```asm
10006480: 53                           	push	ebx
10006481: 8b 5c 24 0c                  	mov	ebx, dword ptr [esp + 0xc]
10006485: 56                           	push	esi
10006486: 57                           	push	edi
10006487: 85 db                        	test	ebx, ebx
10006489: 8b f1                        	mov	esi, ecx
1000648b: 0f 84 b9 00 00 00            	je	0x1000654a <.text+0x554a>
10006491: 6a 40                        	push	0x40
10006493: e8 c8 67 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
10006498: 8b f8                        	mov	edi, eax
1000649a: 83 c4 04                     	add	esp, 0x4
1000649d: 85 ff                        	test	edi, edi
1000649f: 0f 84 8f 00 00 00            	je	0x10006534 <.text+0x5534>
100064a5: 8b 5c 24 10                  	mov	ebx, dword ptr [esp + 0x10]
100064a9: 55                           	push	ebp
100064aa: 6a 00                        	push	0x0
100064ac: 6a 00                        	push	0x0
100064ae: 66 33 c0                     	xor	ax, ax
100064b1: 57                           	push	edi
100064b2: 6a 00                        	push	0x0
100064b4: 8a c3                        	mov	al, bl
100064b6: 6a 00                        	push	0x0
100064b8: 50                           	push	eax
100064b9: 6a 34                        	push	0x34
100064bb: 8d 8e 5c 04 00 00            	lea	ecx, [esi + 0x45c]
100064c1: e8 7a d8 ff ff               	call	0x10003d40 <.text+0x2d40>
100064c6: 6a 40                        	push	0x40
100064c8: 8b e8                        	mov	ebp, eax
100064ca: e8 91 67 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
100064cf: b9 01 00 00 00               	mov	ecx, 0x1
100064d4: 89 68 08                     	mov	dword ptr [eax + 0x8], ebp
100064d7: 89 08                        	mov	dword ptr [eax], ecx
100064d9: 89 48 04                     	mov	dword ptr [eax + 0x4], ecx
100064dc: 89 78 0c                     	mov	dword ptr [eax + 0xc], edi
100064df: 89 78 10                     	mov	dword ptr [eax + 0x10], edi
100064e2: 8b 56 20                     	mov	edx, dword ptr [esi + 0x20]
100064e5: 81 e3 ff 00 00 00            	and	ebx, 0xff
100064eb: 83 c4 04                     	add	esp, 0x4
100064ee: 89 50 14                     	mov	dword ptr [eax + 0x14], edx
100064f1: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
100064f5: 81 c3 00 00 00 34            	add	ebx, 0x34000000
100064fb: c7 40 18 09 2f 00 00         	mov	dword ptr [eax + 0x18], 0x2f09
10006502: 89 50 1c                     	mov	dword ptr [eax + 0x1c], edx
10006505: 89 48 20                     	mov	dword ptr [eax + 0x20], ecx
10006508: c7 40 24 00 00 00 00         	mov	dword ptr [eax + 0x24], 0x0
1000650f: 89 58 28                     	mov	dword ptr [eax + 0x28], ebx
10006512: 8b 8e 68 04 00 00            	mov	ecx, dword ptr [esi + 0x468]
10006518: 50                           	push	eax
10006519: 0f bf 86 70 04 00 00         	movsx	eax, word ptr [esi + 0x470]
10006520: 50                           	push	eax
10006521: 68 fb 2e 00 00               	push	0x2efb
10006526: 51                           	push	ecx
10006527: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000652d: 5d                           	pop	ebp
1000652e: 5f                           	pop	edi
1000652f: 5e                           	pop	esi
10006530: 5b                           	pop	ebx
10006531: c2 08 00                     	ret	0x8
10006534: 68 5b 04 00 00               	push	0x45b
10006539: 68 e8 03 00 00               	push	0x3e8
1000653e: 68 09 2f 00 00               	push	0x2f09
10006543: 53                           	push	ebx
10006544: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000654a: 5f                           	pop	edi
1000654b: 5e                           	pop	esi
1000654c: 5b                           	pop	ebx
1000654d: c2 08 00                     	ret	0x8
10006550: 8b 54 24 04                  	mov	edx, dword ptr [esp + 0x4]
10006554: 8b 01                        	mov	eax, dword ptr [ecx]
10006556: 52                           	push	edx
10006557: 6a 01                        	push	0x1
10006559: ff 90 04 01 00 00            	call	dword ptr [eax + 0x104]
1000655f: c2 04 00                     	ret	0x4
```

## 0x100065b3–0x1000660b

File start offset: 0x65b3

```asm
100065b3: 8b 43 10                     	mov	eax, dword ptr [ebx + 0x10]
100065b6: 8d 54 24 13                  	lea	edx, [esp + 0x13]
100065ba: 52                           	push	edx
100065bb: 50                           	push	eax
100065bc: 8d 8e 5c 04 00 00            	lea	ecx, [esi + 0x45c]
100065c2: e8 a9 d9 ff ff               	call	0x10003f70 <.text+0x2f70>
100065c7: 8a 44 24 13                  	mov	al, byte ptr [esp + 0x13]
100065cb: c7 44 24 34 eb 03 00 00      	mov	dword ptr [esp + 0x34], 0x3eb
100065d3: 3c 16                        	cmp	al, 0x16
100065d5: 0f 85 da 03 00 00            	jne	0x100069b5 <.text+0x59b5>
100065db: 8b 4b 10                     	mov	ecx, dword ptr [ebx + 0x10]
100065de: 80 39 00                     	cmp	byte ptr [ecx], 0x0
100065e1: 0f 85 ce 03 00 00            	jne	0x100069b5 <.text+0x59b5>
100065e7: 8b 43 28                     	mov	eax, dword ptr [ebx + 0x28]
100065ea: c7 44 24 34 00 00 00 00      	mov	dword ptr [esp + 0x34], 0x0
100065f2: 8b d0                        	mov	edx, eax
100065f4: c1 ea 18                     	shr	edx, 0x18
100065f7: 8d 7a ee                     	lea	edi, [edx - 0x12]
100065fa: 83 ff 30                     	cmp	edi, 0x30
100065fd: 0f 87 aa 03 00 00            	ja	0x100069ad <.text+0x59ad>
10006603: 33 c9                        	xor	ecx, ecx
10006605: 8a 8f 6c 6a 00 10            	mov	cl, byte ptr [edi + 0x10006a6c]
1000660b: ff 24 8d 44 6a 00 10         	jmp	dword ptr [4*ecx + 0x10006a44]
```

## 0x10007390–0x100075c3

File start offset: 0x7390

```asm
10007390: 81 ec cc 00 00 00            	sub	esp, 0xcc
10007396: 53                           	push	ebx
10007397: b0 20                        	mov	al, 0x20
10007399: 55                           	push	ebp
1000739a: 56                           	push	esi
1000739b: 8b b4 24 dc 00 00 00         	mov	esi, dword ptr [esp + 0xdc]
100073a2: 88 44 24 0c                  	mov	byte ptr [esp + 0xc], al
100073a6: 88 44 24 0d                  	mov	byte ptr [esp + 0xd], al
100073aa: 88 44 24 0e                  	mov	byte ptr [esp + 0xe], al
100073ae: 88 44 24 0f                  	mov	byte ptr [esp + 0xf], al
100073b2: 88 44 24 10                  	mov	byte ptr [esp + 0x10], al
100073b6: 88 44 24 11                  	mov	byte ptr [esp + 0x11], al
100073ba: 88 44 24 12                  	mov	byte ptr [esp + 0x12], al
100073be: 88 44 24 13                  	mov	byte ptr [esp + 0x13], al
100073c2: 88 44 24 14                  	mov	byte ptr [esp + 0x14], al
100073c6: 88 44 24 15                  	mov	byte ptr [esp + 0x15], al
100073ca: 88 44 24 16                  	mov	byte ptr [esp + 0x16], al
100073ce: 88 44 24 17                  	mov	byte ptr [esp + 0x17], al
100073d2: 57                           	push	edi
100073d3: 8b e9                        	mov	ebp, ecx
100073d5: 33 c0                        	xor	eax, eax
100073d7: 0f bf c8                     	movsx	ecx, ax
100073da: 8a 14 31                     	mov	dl, byte ptr [ecx + esi]
100073dd: 84 d2                        	test	dl, dl
100073df: 74 0b                        	je	0x100073ec <.text+0x63ec>
100073e1: 40                           	inc	eax
100073e2: 88 54 0c 10                  	mov	byte ptr [esp + ecx + 0x10], dl
100073e6: 66 3d 0c 00                  	cmp	ax, 0xc
100073ea: 7c eb                        	jl	0x100073d7 <.text+0x63d7>
100073ec: 8d 44 24 10                  	lea	eax, [esp + 0x10]
100073f0: 50                           	push	eax
100073f1: e8 ca d1 ff ff               	call	0x100045c0 <.text+0x35c0>
100073f6: 8b 4d 58                     	mov	ecx, dword ptr [ebp + 0x58]
100073f9: 83 c4 04                     	add	esp, 0x4
100073fc: 8d 9d 5c 04 00 00            	lea	ebx, [ebp + 0x45c]
10007402: 8d 54 24 10                  	lea	edx, [esp + 0x10]
10007406: 51                           	push	ecx
10007407: 52                           	push	edx
10007408: 8b cb                        	mov	ecx, ebx
1000740a: e8 71 d0 ff ff               	call	0x10004480 <.text+0x3480>
1000740f: 66 3d ff ff                  	cmp	ax, 0xffff
10007413: 0f 85 eb 00 00 00            	jne	0x10007504 <.text+0x6504>
10007419: 8d 44 24 10                  	lea	eax, [esp + 0x10]
1000741d: 50                           	push	eax
1000741e: e8 9d c8 ff ff               	call	0x10003cc0 <.text+0x2cc0>
10007423: 8b 44 24 1c                  	mov	eax, dword ptr [esp + 0x1c]
10007427: b9 30 00 00 00               	mov	ecx, 0x30
1000742c: be 1c 7b 05 10               	mov	esi, 0x10057b1c
10007431: 8d 7c 24 20                  	lea	edi, [esp + 0x20]
10007435: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
10007437: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
1000743b: 89 44 24 2b                  	mov	dword ptr [esp + 0x2b], eax
1000743f: 8b 84 24 e8 00 00 00         	mov	eax, dword ptr [esp + 0xe8]
10007446: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
1000744a: 66 3d 7f 00                  	cmp	ax, 0x7f
1000744e: 89 4c 24 23                  	mov	dword ptr [esp + 0x23], ecx
10007452: 0f 9f c1                     	setg	cl
10007455: 49                           	dec	ecx
10007456: 68 00 02 00 00               	push	0x200
1000745b: 23 c8                        	and	ecx, eax
1000745d: 89 54 24 2b                  	mov	dword ptr [esp + 0x2b], edx
10007461: 88 4c 24 33                  	mov	byte ptr [esp + 0x33], cl
10007465: e8 f6 57 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000746a: 8b f8                        	mov	edi, eax
1000746c: 83 c4 08                     	add	esp, 0x8
1000746f: 85 ff                        	test	edi, edi
10007471: 0f 84 86 00 00 00            	je	0x100074fd <.text+0x64fd>
10007477: 6a 40                        	push	0x40
10007479: e8 e2 57 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000747e: 83 c4 04                     	add	esp, 0x4
10007481: 8d 54 24 1c                  	lea	edx, [esp + 0x1c]
10007485: 8b cb                        	mov	ecx, ebx
10007487: 8b f0                        	mov	esi, eax
10007489: 52                           	push	edx
1000748a: 68 c0 00 00 00               	push	0xc0
1000748f: 57                           	push	edi
10007490: 6a 00                        	push	0x0
10007492: 6a 00                        	push	0x0
10007494: 68 80 00 00 00               	push	0x80
10007499: 6a 07                        	push	0x7
1000749b: e8 a0 c8 ff ff               	call	0x10003d40 <.text+0x2d40>
100074a0: 8b 94 24 e8 00 00 00         	mov	edx, dword ptr [esp + 0xe8]
100074a7: b9 01 00 00 00               	mov	ecx, 0x1
100074ac: 89 0e                        	mov	dword ptr [esi], ecx
100074ae: 89 4e 04                     	mov	dword ptr [esi + 0x4], ecx
100074b1: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
100074b4: 89 7e 0c                     	mov	dword ptr [esi + 0xc], edi
100074b7: 89 7e 10                     	mov	dword ptr [esi + 0x10], edi
100074ba: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
100074bd: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
100074c0: 33 c0                        	xor	eax, eax
100074c2: c7 46 18 0a 2f 00 00         	mov	dword ptr [esi + 0x18], 0x2f0a
100074c9: 89 56 1c                     	mov	dword ptr [esi + 0x1c], edx
100074cc: 89 4e 20                     	mov	dword ptr [esi + 0x20], ecx
100074cf: 89 46 24                     	mov	dword ptr [esi + 0x24], eax
100074d2: 89 46 28                     	mov	dword ptr [esi + 0x28], eax
100074d5: 8b 8d 68 04 00 00            	mov	ecx, dword ptr [ebp + 0x468]
100074db: 0f bf 85 70 04 00 00         	movsx	eax, word ptr [ebp + 0x470]
100074e2: 56                           	push	esi
100074e3: 50                           	push	eax
100074e4: 68 fb 2e 00 00               	push	0x2efb
100074e9: 51                           	push	ecx
100074ea: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
100074f0: 5f                           	pop	edi
100074f1: 5e                           	pop	esi
100074f2: 5d                           	pop	ebp
100074f3: 5b                           	pop	ebx
100074f4: 81 c4 cc 00 00 00            	add	esp, 0xcc
100074fa: c2 0c 00                     	ret	0xc
100074fd: b8 e8 03 00 00               	mov	eax, 0x3e8
10007502: eb 05                        	jmp	0x10007509 <.text+0x6509>
10007504: b8 ef 03 00 00               	mov	eax, 0x3ef
10007509: 0f bf d0                     	movsx	edx, ax
1000750c: 8b 84 24 e8 00 00 00         	mov	eax, dword ptr [esp + 0xe8]
10007513: 68 78 07 00 00               	push	0x778
10007518: 52                           	push	edx
10007519: 68 0a 2f 00 00               	push	0x2f0a
1000751e: 50                           	push	eax
1000751f: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
10007525: 5f                           	pop	edi
10007526: 5e                           	pop	esi
10007527: 5d                           	pop	ebp
10007528: 5b                           	pop	ebx
10007529: 81 c4 cc 00 00 00            	add	esp, 0xcc
1000752f: c2 0c 00                     	ret	0xc
10007532: 90                           	nop
10007533: 90                           	nop
10007534: 90                           	nop
10007535: 90                           	nop
10007536: 90                           	nop
10007537: 90                           	nop
10007538: 90                           	nop
10007539: 90                           	nop
1000753a: 90                           	nop
1000753b: 90                           	nop
1000753c: 90                           	nop
1000753d: 90                           	nop
1000753e: 90                           	nop
1000753f: 90                           	nop
10007540: 56                           	push	esi
10007541: 8b 74 24 0c                  	mov	esi, dword ptr [esp + 0xc]
10007545: 57                           	push	edi
10007546: 8b f9                        	mov	edi, ecx
10007548: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
1000754b: 8d 44 24 10                  	lea	eax, [esp + 0x10]
1000754f: 50                           	push	eax
10007550: 51                           	push	ecx
10007551: 8d 8f 5c 04 00 00            	lea	ecx, [edi + 0x45c]
10007557: e8 14 ca ff ff               	call	0x10003f70 <.text+0x2f70>
1000755c: 80 7c 24 10 16               	cmp	byte ptr [esp + 0x10], 0x16
10007561: 75 5b                        	jne	0x100075be <.text+0x65be>
10007563: 8b 56 10                     	mov	edx, dword ptr [esi + 0x10]
10007566: 80 3a 00                     	cmp	byte ptr [edx], 0x0
10007569: 75 53                        	jne	0x100075be <.text+0x65be>
1000756b: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
1000756e: 8b 07                        	mov	eax, dword ptr [edi]
10007570: 51                           	push	ecx
10007571: 6a 00                        	push	0x0
10007573: 68 ff 00 00 00               	push	0xff
10007578: 8b cf                        	mov	ecx, edi
1000757a: ff 90 3c 01 00 00            	call	dword ptr [eax + 0x13c]
10007580: 8b 7c 24 0c                  	mov	edi, dword ptr [esp + 0xc]
10007584: 85 ff                        	test	edi, edi
10007586: 74 16                        	je	0x1000759e <.text+0x659e>
10007588: 8b 56 1c                     	mov	edx, dword ptr [esi + 0x1c]
1000758b: 6a 00                        	push	0x0
1000758d: 57                           	push	edi
1000758e: 68 0a 2f 00 00               	push	0x2f0a
10007593: 52                           	push	edx
10007594: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000759a: 85 ff                        	test	edi, edi
1000759c: 75 07                        	jne	0x100075a5 <.text+0x65a5>
1000759e: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
100075a1: 85 c0                        	test	eax, eax
100075a3: 74 12                        	je	0x100075b7 <.text+0x65b7>
100075a5: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
100075a8: 50                           	push	eax
100075a9: e8 a8 57 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
100075ae: 56                           	push	esi
100075af: e8 a2 57 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
100075b4: 83 c4 08                     	add	esp, 0x8
100075b7: 8b c7                        	mov	eax, edi
100075b9: 5f                           	pop	edi
100075ba: 5e                           	pop	esi
100075bb: c2 08 00                     	ret	0x8
100075be: bf eb 03 00 00               	mov	edi, 0x3eb
100075c3: eb c3                        	jmp	0x10007588 <.text+0x6588>
```

## 0x100075d0–0x100077f5

File start offset: 0x75d0

```asm
100075d0: 81 ec c4 00 00 00            	sub	esp, 0xc4
100075d6: 66 83 bc 24 cc 00 00 00 63   	cmp	word ptr [esp + 0xcc], 0x63
100075df: 55                           	push	ebp
100075e0: 8b e9                        	mov	ebp, ecx
100075e2: 0f 8f 20 01 00 00            	jg	0x10007708 <.text+0x6708>
100075e8: 68 00 02 00 00               	push	0x200
100075ed: e8 6e 56 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
100075f2: 83 c4 04                     	add	esp, 0x4
100075f5: 89 44 24 04                  	mov	dword ptr [esp + 0x4], eax
100075f9: 85 c0                        	test	eax, eax
100075fb: 0f 84 da 00 00 00            	je	0x100076db <.text+0x66db>
10007601: 53                           	push	ebx
10007602: 56                           	push	esi
10007603: 57                           	push	edi
10007604: 6a 40                        	push	0x40
10007606: e8 55 56 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000760b: 8b d8                        	mov	ebx, eax
1000760d: b9 30 00 00 00               	mov	ecx, 0x30
10007612: be 38 7a 05 10               	mov	esi, 0x10057a38
10007617: 8d 7c 24 18                  	lea	edi, [esp + 0x18]
1000761b: 8d 44 24 3a                  	lea	eax, [esp + 0x3a]
1000761f: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
10007621: 50                           	push	eax
10007622: e8 99 c6 ff ff               	call	0x10003cc0 <.text+0x2cc0>
10007627: 8d 4c 24 56                  	lea	ecx, [esp + 0x56]
1000762b: 51                           	push	ecx
1000762c: e8 8f c6 ff ff               	call	0x10003cc0 <.text+0x2cc0>
10007631: 8d 54 24 72                  	lea	edx, [esp + 0x72]
10007635: 52                           	push	edx
10007636: e8 85 c6 ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000763b: 8d 84 24 8e 00 00 00         	lea	eax, [esp + 0x8e]
10007642: 50                           	push	eax
10007643: e8 78 c6 ff ff               	call	0x10003cc0 <.text+0x2cc0>
10007648: 8b 74 24 24                  	mov	esi, dword ptr [esp + 0x24]
1000764c: 8b 94 24 f0 00 00 00         	mov	edx, dword ptr [esp + 0xf0]
10007653: 8b bc 24 ec 00 00 00         	mov	edi, dword ptr [esp + 0xec]
1000765a: 83 c4 14                     	add	esp, 0x14
1000765d: 8d 4c 24 14                  	lea	ecx, [esp + 0x14]
10007661: 51                           	push	ecx
10007662: 68 c0 00 00 00               	push	0xc0
10007667: 56                           	push	esi
10007668: 6a 00                        	push	0x0
1000766a: 52                           	push	edx
1000766b: 57                           	push	edi
1000766c: 6a 09                        	push	0x9
1000766e: 8d 8d 5c 04 00 00            	lea	ecx, [ebp + 0x45c]
10007674: e8 c7 c6 ff ff               	call	0x10003d40 <.text+0x2d40>
10007679: b9 01 00 00 00               	mov	ecx, 0x1
1000767e: 8b 94 24 e0 00 00 00         	mov	edx, dword ptr [esp + 0xe0]
10007685: 89 0b                        	mov	dword ptr [ebx], ecx
10007687: 89 4b 04                     	mov	dword ptr [ebx + 0x4], ecx
1000768a: 89 43 08                     	mov	dword ptr [ebx + 0x8], eax
1000768d: 89 73 0c                     	mov	dword ptr [ebx + 0xc], esi
10007690: 89 73 10                     	mov	dword ptr [ebx + 0x10], esi
10007693: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
10007696: 89 43 14                     	mov	dword ptr [ebx + 0x14], eax
10007699: c7 43 18 0b 2f 00 00         	mov	dword ptr [ebx + 0x18], 0x2f0b
100076a0: 0f bf c7                     	movsx	eax, di
100076a3: 89 53 1c                     	mov	dword ptr [ebx + 0x1c], edx
100076a6: 89 4b 20                     	mov	dword ptr [ebx + 0x20], ecx
100076a9: c7 43 24 00 00 00 00         	mov	dword ptr [ebx + 0x24], 0x0
100076b0: 89 43 28                     	mov	dword ptr [ebx + 0x28], eax
100076b3: 0f bf 8d 70 04 00 00         	movsx	ecx, word ptr [ebp + 0x470]
100076ba: 8b 95 68 04 00 00            	mov	edx, dword ptr [ebp + 0x468]
100076c0: 53                           	push	ebx
100076c1: 51                           	push	ecx
100076c2: 68 fb 2e 00 00               	push	0x2efb
100076c7: 52                           	push	edx
100076c8: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
100076ce: 5f                           	pop	edi
100076cf: 5e                           	pop	esi
100076d0: 5b                           	pop	ebx
100076d1: 5d                           	pop	ebp
100076d2: 81 c4 c4 00 00 00            	add	esp, 0xc4
100076d8: c2 0c 00                     	ret	0xc
100076db: 8b 8c 24 d4 00 00 00         	mov	ecx, dword ptr [esp + 0xd4]
100076e2: 33 c0                        	xor	eax, eax
100076e4: 66 81 bc 24 cc 00 00 00 ff 00	cmp	word ptr [esp + 0xcc], 0xff
100076ee: 68 d4 07 00 00               	push	0x7d4
100076f3: 68 e8 03 00 00               	push	0x3e8
100076f8: 0f 95 c0                     	setne	al
100076fb: 05 0a 2f 00 00               	add	eax, 0x2f0a
10007700: 50                           	push	eax
10007701: 51                           	push	ecx
10007702: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
10007708: 5d                           	pop	ebp
10007709: 81 c4 c4 00 00 00            	add	esp, 0xc4
1000770f: c2 0c 00                     	ret	0xc
10007712: 90                           	nop
10007713: 90                           	nop
10007714: 90                           	nop
10007715: 90                           	nop
10007716: 90                           	nop
10007717: 90                           	nop
10007718: 90                           	nop
10007719: 90                           	nop
1000771a: 90                           	nop
1000771b: 90                           	nop
1000771c: 90                           	nop
1000771d: 90                           	nop
1000771e: 90                           	nop
1000771f: 90                           	nop
10007720: 55                           	push	ebp
10007721: 56                           	push	esi
10007722: 57                           	push	edi
10007723: 8b 7c 24 14                  	mov	edi, dword ptr [esp + 0x14]
10007727: 8b f1                        	mov	esi, ecx
10007729: 8d 44 24 14                  	lea	eax, [esp + 0x14]
1000772d: 8b 4f 10                     	mov	ecx, dword ptr [edi + 0x10]
10007730: 8b 6f 28                     	mov	ebp, dword ptr [edi + 0x28]
10007733: 50                           	push	eax
10007734: 51                           	push	ecx
10007735: 8d 8e 5c 04 00 00            	lea	ecx, [esi + 0x45c]
1000773b: e8 30 c8 ff ff               	call	0x10003f70 <.text+0x2f70>
10007740: 80 7c 24 14 16               	cmp	byte ptr [esp + 0x14], 0x16
10007745: 0f 85 a5 00 00 00            	jne	0x100077f0 <.text+0x67f0>
1000774b: 8b 57 10                     	mov	edx, dword ptr [edi + 0x10]
1000774e: 80 3a 00                     	cmp	byte ptr [edx], 0x0
10007751: 0f 85 99 00 00 00            	jne	0x100077f0 <.text+0x67f0>
10007757: 81 fd ff 00 00 00            	cmp	ebp, 0xff
1000775d: 75 54                        	jne	0x100077b3 <.text+0x67b3>
1000775f: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
10007762: 8b ce                        	mov	ecx, esi
10007764: 66 c7 00 00 00               	mov	word ptr [eax], 0x0
10007769: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
1000776c: 8b 16                        	mov	edx, dword ptr [esi]
1000776e: 50                           	push	eax
1000776f: 6a 00                        	push	0x0
10007771: 6a 01                        	push	0x1
10007773: ff 92 c8 00 00 00            	call	dword ptr [edx + 0xc8]
10007779: 8b 74 24 10                  	mov	esi, dword ptr [esp + 0x10]
1000777d: 8b 4f 1c                     	mov	ecx, dword ptr [edi + 0x1c]
10007780: 55                           	push	ebp
10007781: 56                           	push	esi
10007782: 68 0a 2f 00 00               	push	0x2f0a
10007787: 51                           	push	ecx
10007788: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000778e: 85 f6                        	test	esi, esi
10007790: 75 07                        	jne	0x10007799 <.text+0x6799>
10007792: 8b 47 20                     	mov	eax, dword ptr [edi + 0x20]
10007795: 85 c0                        	test	eax, eax
10007797: 74 12                        	je	0x100077ab <.text+0x67ab>
10007799: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
1000779c: 51                           	push	ecx
1000779d: e8 b4 55 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
100077a2: 57                           	push	edi
100077a3: e8 ae 55 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
100077a8: 83 c4 08                     	add	esp, 0x8
100077ab: 8b c6                        	mov	eax, esi
100077ad: 5f                           	pop	edi
100077ae: 5e                           	pop	esi
100077af: 5d                           	pop	ebp
100077b0: c2 08 00                     	ret	0x8
100077b3: 8b 74 ae 5c                  	mov	esi, dword ptr [esi + 4*ebp + 0x5c]
100077b7: 85 f6                        	test	esi, esi
100077b9: 74 24                        	je	0x100077df <.text+0x67df>
100077bb: 8b 16                        	mov	edx, dword ptr [esi]
100077bd: 53                           	push	ebx
100077be: 6a 2a                        	push	0x2a
100077c0: 8b ce                        	mov	ecx, esi
100077c2: ff 52 08                     	call	dword ptr [edx + 0x8]
100077c5: 8b d8                        	mov	ebx, eax
100077c7: 8b 06                        	mov	eax, dword ptr [esi]
100077c9: 8d 4b 01                     	lea	ecx, [ebx + 0x1]
100077cc: 51                           	push	ecx
100077cd: 6a 2a                        	push	0x2a
100077cf: 8b ce                        	mov	ecx, esi
100077d1: ff 50 0c                     	call	dword ptr [eax + 0xc]
100077d4: 8b 16                        	mov	edx, dword ptr [esi]
100077d6: 6a 00                        	push	0x0
100077d8: 53                           	push	ebx
100077d9: 8b ce                        	mov	ecx, esi
100077db: ff 52 28                     	call	dword ptr [edx + 0x28]
100077de: 5b                           	pop	ebx
100077df: 8b 74 24 10                  	mov	esi, dword ptr [esp + 0x10]
100077e3: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
100077e6: 55                           	push	ebp
100077e7: 56                           	push	esi
100077e8: 68 0b 2f 00 00               	push	0x2f0b
100077ed: 50                           	push	eax
100077ee: eb 98                        	jmp	0x10007788 <.text+0x6788>
100077f0: be eb 03 00 00               	mov	esi, 0x3eb
100077f5: eb a2                        	jmp	0x10007799 <.text+0x6799>
```

## 0x10008b00–0x10008ef7

File start offset: 0x8b00

```asm
10008b00: 83 ec 18                     	sub	esp, 0x18
10008b03: 53                           	push	ebx
10008b04: 55                           	push	ebp
10008b05: 8b 6c 24 28                  	mov	ebp, dword ptr [esp + 0x28]
10008b09: 8b d9                        	mov	ebx, ecx
10008b0b: 56                           	push	esi
10008b0c: 8b 45 30                     	mov	eax, dword ptr [ebp + 0x30]
10008b0f: 8b 4d 38                     	mov	ecx, dword ptr [ebp + 0x38]
10008b12: 8b 55 3c                     	mov	edx, dword ptr [ebp + 0x3c]
10008b15: 89 44 24 0c                  	mov	dword ptr [esp + 0xc], eax
10008b19: 8b 44 24 28                  	mov	eax, dword ptr [esp + 0x28]
10008b1d: 89 4c 24 14                  	mov	dword ptr [esp + 0x14], ecx
10008b21: 85 c0                        	test	eax, eax
10008b23: 89 54 24 10                  	mov	dword ptr [esp + 0x10], edx
10008b27: 0f 85 d2 00 00 00            	jne	0x10008bff <.text+0x7bff>
10008b2d: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
10008b30: 8d 44 24 2c                  	lea	eax, [esp + 0x2c]
10008b34: 50                           	push	eax
10008b35: 8d 8b 5c 04 00 00            	lea	ecx, [ebx + 0x45c]
10008b3b: 52                           	push	edx
10008b3c: e8 2f b4 ff ff               	call	0x10003f70 <.text+0x2f70>
10008b41: 80 7c 24 2c 05               	cmp	byte ptr [esp + 0x2c], 0x5
10008b46: 0f 85 ea 00 00 00            	jne	0x10008c36 <.text+0x7c36>
10008b4c: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
10008b4f: 8b c8                        	mov	ecx, eax
10008b51: 57                           	push	edi
10008b52: 8b 7b 54                     	mov	edi, dword ptr [ebx + 0x54]
10008b55: c1 e9 02                     	shr	ecx, 0x2
10008b58: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
10008b5a: 8b c8                        	mov	ecx, eax
10008b5c: 83 e1 03                     	and	ecx, 0x3
10008b5f: f3 a4                        	rep		movsb	byte ptr es:[edi], byte ptr [esi]
10008b61: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
10008b65: 8d 41 03                     	lea	eax, [ecx + 0x3]
10008b68: 8b d0                        	mov	edx, eax
10008b6a: 8b 32                        	mov	esi, dword ptr [edx]
10008b6c: 89 74 24 1c                  	mov	dword ptr [esp + 0x1c], esi
10008b70: 8b 7a 04                     	mov	edi, dword ptr [edx + 0x4]
10008b73: 89 7c 24 20                  	mov	dword ptr [esp + 0x20], edi
10008b77: 8b 4a 08                     	mov	ecx, dword ptr [edx + 0x8]
10008b7a: 89 4c 24 24                  	mov	dword ptr [esp + 0x24], ecx
10008b7e: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
10008b82: 85 c9                        	test	ecx, ecx
10008b84: 74 14                        	je	0x10008b9a <.text+0x7b9a>
10008b86: 49                           	dec	ecx
10008b87: c6 44 24 26 2d               	mov	byte ptr [esp + 0x26], 0x2d
10008b8c: f7 d9                        	neg	ecx
10008b8e: 1a c9                        	sbb	cl, cl
10008b90: 80 e1 06                     	and	cl, 0x6
10008b93: 80 c1 4c                     	add	cl, 0x4c
10008b96: 88 4c 24 27                  	mov	byte ptr [esp + 0x27], cl
10008b9a: 8b 54 24 24                  	mov	edx, dword ptr [esp + 0x24]
10008b9e: 89 30                        	mov	dword ptr [eax], esi
10008ba0: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
10008ba3: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
10008ba6: 8b 43 54                     	mov	eax, dword ptr [ebx + 0x54]
10008ba9: 8d 4c 24 1c                  	lea	ecx, [esp + 0x1c]
10008bad: 50                           	push	eax
10008bae: 51                           	push	ecx
10008baf: 8d 8b 5c 04 00 00            	lea	ecx, [ebx + 0x45c]
10008bb5: e8 c6 b8 ff ff               	call	0x10004480 <.text+0x3480>
10008bba: 66 3d ff ff                  	cmp	ax, 0xffff
10008bbe: 5f                           	pop	edi
10008bbf: 7e 2c                        	jle	0x10008bed <.text+0x7bed>
10008bc1: 85 db                        	test	ebx, ebx
10008bc3: 75 04                        	jne	0x10008bc9 <.text+0x7bc9>
10008bc5: 33 c9                        	xor	ecx, ecx
10008bc7: eb 03                        	jmp	0x10008bcc <.text+0x7bcc>
10008bc9: 8b 4b 20                     	mov	ecx, dword ptr [ebx + 0x20]
10008bcc: 8b 13                        	mov	edx, dword ptr [ebx]
10008bce: 55                           	push	ebp
10008bcf: 68 18 2f 00 00               	push	0x2f18
10008bd4: 6a 00                        	push	0x0
10008bd6: 51                           	push	ecx
10008bd7: 50                           	push	eax
10008bd8: 8b cb                        	mov	ecx, ebx
10008bda: ff 92 40 01 00 00            	call	dword ptr [edx + 0x140]
10008be0: 8b 44 24 28                  	mov	eax, dword ptr [esp + 0x28]
10008be4: 5e                           	pop	esi
10008be5: 5d                           	pop	ebp
10008be6: 5b                           	pop	ebx
10008be7: 83 c4 18                     	add	esp, 0x18
10008bea: c2 08 00                     	ret	0x8
10008bed: 55                           	push	ebp
10008bee: 6a 00                        	push	0x0
10008bf0: 8b cb                        	mov	ecx, ebx
10008bf2: e8 49 00 00 00               	call	0x10008c40 <.text+0x7c40>
10008bf7: 85 c0                        	test	eax, eax
10008bf9: 89 44 24 28                  	mov	dword ptr [esp + 0x28], eax
10008bfd: 74 e1                        	je	0x10008be0 <.text+0x7be0>
10008bff: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
10008c02: 50                           	push	eax
10008c03: e8 4e 41 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008c08: 55                           	push	ebp
10008c09: e8 48 41 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008c0e: 8b 74 24 30                  	mov	esi, dword ptr [esp + 0x30]
10008c12: 8b 4c 24 1c                  	mov	ecx, dword ptr [esp + 0x1c]
10008c16: 83 c4 08                     	add	esp, 0x8
10008c19: 68 5d 0c 00 00               	push	0xc5d
10008c1e: 56                           	push	esi
10008c1f: 68 16 2f 00 00               	push	0x2f16
10008c24: 51                           	push	ecx
10008c25: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
10008c2b: 8b c6                        	mov	eax, esi
10008c2d: 5e                           	pop	esi
10008c2e: 5d                           	pop	ebp
10008c2f: 5b                           	pop	ebx
10008c30: 83 c4 18                     	add	esp, 0x18
10008c33: c2 08 00                     	ret	0x8
10008c36: c7 44 24 28 eb 03 00 00      	mov	dword ptr [esp + 0x28], 0x3eb
10008c3e: eb bf                        	jmp	0x10008bff <.text+0x7bff>
10008c40: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
10008c46: 6a ff                        	push	-0x1
10008c48: 68 78 e1 04 10               	push	0x1004e178
10008c4d: 50                           	push	eax
10008c4e: 64 89 25 00 00 00 00         	mov	dword ptr fs:[0x0], esp
10008c55: 83 ec 08                     	sub	esp, 0x8
10008c58: 53                           	push	ebx
10008c59: 55                           	push	ebp
10008c5a: 56                           	push	esi
10008c5b: 8b 74 24 28                  	mov	esi, dword ptr [esp + 0x28]
10008c5f: 8b d9                        	mov	ebx, ecx
10008c61: 8b ee                        	mov	ebp, esi
10008c63: 83 7e 28 14                  	cmp	dword ptr [esi + 0x28], 0x14
10008c67: 75 15                        	jne	0x10008c7e <.text+0x7c7e>
10008c69: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
10008c6c: 8b 6e 30                     	mov	ebp, dword ptr [esi + 0x30]
10008c6f: 50                           	push	eax
10008c70: e8 e1 40 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008c75: 56                           	push	esi
10008c76: e8 db 40 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008c7b: 83 c4 08                     	add	esp, 0x8
10008c7e: 8b 75 34                     	mov	esi, dword ptr [ebp + 0x34]
10008c81: 68 04 01 00 00               	push	0x104
10008c86: 89 74 24 14                  	mov	dword ptr [esp + 0x14], esi
10008c8a: e8 d1 3f 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
10008c8f: 83 c4 04                     	add	esp, 0x4
10008c92: 89 44 24 0c                  	mov	dword ptr [esp + 0xc], eax
10008c96: 85 c0                        	test	eax, eax
10008c98: 0f 84 2c 01 00 00            	je	0x10008dca <.text+0x7dca>
10008c9e: 8b 06                        	mov	eax, dword ptr [esi]
10008ca0: 8d 4c 24 28                  	lea	ecx, [esp + 0x28]
10008ca4: 57                           	push	edi
10008ca5: 51                           	push	ecx
10008ca6: 8b ce                        	mov	ecx, esi
10008ca8: ff 50 20                     	call	dword ptr [eax + 0x20]
10008cab: 8b 54 24 2c                  	mov	edx, dword ptr [esp + 0x2c]
10008caf: 8d 4c 24 2c                  	lea	ecx, [esp + 0x2c]
10008cb3: c7 44 24 20 00 00 00 00      	mov	dword ptr [esp + 0x20], 0x0
10008cbb: 8b 42 f8                     	mov	eax, dword ptr [edx - 0x8]
10008cbe: 50                           	push	eax
10008cbf: e8 f0 42 04 00               	call	0x1004cfb4 <DllRegisterServer+0x1ffd4>
10008cc4: 8b f8                        	mov	edi, eax
10008cc6: 83 c9 ff                     	or	ecx, -0x1
10008cc9: 33 c0                        	xor	eax, eax
10008ccb: f2 ae                        	repne		scasb	al, byte ptr es:[edi]
10008ccd: f7 d1                        	not	ecx
10008ccf: 2b f9                        	sub	edi, ecx
10008cd1: 8b c1                        	mov	eax, ecx
10008cd3: 8b f7                        	mov	esi, edi
10008cd5: 8b 7c 24 10                  	mov	edi, dword ptr [esp + 0x10]
10008cd9: c1 e9 02                     	shr	ecx, 0x2
10008cdc: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
10008cde: 8b c8                        	mov	ecx, eax
10008ce0: 83 e1 03                     	and	ecx, 0x3
10008ce3: f3 a4                        	rep		movsb	byte ptr es:[edi], byte ptr [esi]
10008ce5: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
10008ce9: 85 c9                        	test	ecx, ecx
10008ceb: 74 07                        	je	0x10008cf4 <.text+0x7cf4>
10008ced: 8b 11                        	mov	edx, dword ptr [ecx]
10008cef: 6a 01                        	push	0x1
10008cf1: ff 52 04                     	call	dword ptr [edx + 0x4]
10008cf4: 8b 44 24 10                  	mov	eax, dword ptr [esp + 0x10]
10008cf8: 8b 75 30                     	mov	esi, dword ptr [ebp + 0x30]
10008cfb: 8b 4d 38                     	mov	ecx, dword ptr [ebp + 0x38]
10008cfe: 89 45 34                     	mov	dword ptr [ebp + 0x34], eax
10008d01: 8b 53 54                     	mov	edx, dword ptr [ebx + 0x54]
10008d04: 8d 46 03                     	lea	eax, [esi + 0x3]
10008d07: 50                           	push	eax
10008d08: 89 4c 24 14                  	mov	dword ptr [esp + 0x14], ecx
10008d0c: 66 8b 3a                     	mov	di, word ptr [edx]
10008d0f: 89 75 38                     	mov	dword ptr [ebp + 0x38], esi
10008d12: c6 45 30 00                  	mov	byte ptr [ebp + 0x30], 0x0
10008d16: 89 44 24 18                  	mov	dword ptr [esp + 0x18], eax
10008d1a: e8 a1 af ff ff               	call	0x10003cc0 <.text+0x2cc0>
10008d1f: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
10008d22: 83 c4 04                     	add	esp, 0x4
10008d25: 8d 8b 5c 04 00 00            	lea	ecx, [ebx + 0x45c]
10008d2b: 56                           	push	esi
10008d2c: 68 c0 00 00 00               	push	0xc0
10008d31: 50                           	push	eax
10008d32: 6a 00                        	push	0x0
10008d34: 6a 00                        	push	0x0
10008d36: 57                           	push	edi
10008d37: 6a 0b                        	push	0xb
10008d39: e8 02 b0 ff ff               	call	0x10003d40 <.text+0x2d40>
10008d3e: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
10008d42: 8b f0                        	mov	esi, eax
10008d44: 51                           	push	ecx
10008d45: e8 56 af ff ff               	call	0x10003ca0 <.text+0x2ca0>
10008d4a: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
10008d4d: b8 01 00 00 00               	mov	eax, 0x1
10008d52: 89 55 10                     	mov	dword ptr [ebp + 0x10], edx
10008d55: 8b 54 24 14                  	mov	edx, dword ptr [esp + 0x14]
10008d59: 89 75 08                     	mov	dword ptr [ebp + 0x8], esi
10008d5c: 89 45 00                     	mov	dword ptr [ebp], eax
10008d5f: 89 45 04                     	mov	dword ptr [ebp + 0x4], eax
10008d62: 8b 4b 20                     	mov	ecx, dword ptr [ebx + 0x20]
10008d65: 89 45 20                     	mov	dword ptr [ebp + 0x20], eax
10008d68: 89 4d 14                     	mov	dword ptr [ebp + 0x14], ecx
10008d6b: 0f bf c7                     	movsx	eax, di
10008d6e: c7 45 18 15 2f 00 00         	mov	dword ptr [ebp + 0x18], 0x2f15
10008d75: 89 55 1c                     	mov	dword ptr [ebp + 0x1c], edx
10008d78: c7 45 24 00 00 00 00         	mov	dword ptr [ebp + 0x24], 0x0
10008d7f: 89 45 28                     	mov	dword ptr [ebp + 0x28], eax
10008d82: 0f bf 8b 70 04 00 00         	movsx	ecx, word ptr [ebx + 0x470]
10008d89: 8b 93 68 04 00 00            	mov	edx, dword ptr [ebx + 0x468]
10008d8f: 83 c4 04                     	add	esp, 0x4
10008d92: 55                           	push	ebp
10008d93: 51                           	push	ecx
10008d94: 68 17 2f 00 00               	push	0x2f17
10008d99: 52                           	push	edx
10008d9a: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
10008da0: 8d 4c 24 2c                  	lea	ecx, [esp + 0x2c]
10008da4: c7 44 24 20 ff ff ff ff      	mov	dword ptr [esp + 0x20], 0xffffffff
10008dac: e8 53 40 04 00               	call	0x1004ce04 <DllRegisterServer+0x1fe24>
10008db1: 8b 44 24 28                  	mov	eax, dword ptr [esp + 0x28]
10008db5: 5f                           	pop	edi
10008db6: 5e                           	pop	esi
10008db7: 5d                           	pop	ebp
10008db8: 5b                           	pop	ebx
10008db9: 8b 4c 24 08                  	mov	ecx, dword ptr [esp + 0x8]
10008dbd: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
10008dc4: 83 c4 14                     	add	esp, 0x14
10008dc7: c2 08 00                     	ret	0x8
10008dca: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
10008dce: 5e                           	pop	esi
10008dcf: 5d                           	pop	ebp
10008dd0: b8 e8 03 00 00               	mov	eax, 0x3e8
10008dd5: 5b                           	pop	ebx
10008dd6: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
10008ddd: 83 c4 14                     	add	esp, 0x14
10008de0: c2 08 00                     	ret	0x8
10008de3: 90                           	nop
10008de4: 90                           	nop
10008de5: 90                           	nop
10008de6: 90                           	nop
10008de7: 90                           	nop
10008de8: 90                           	nop
10008de9: 90                           	nop
10008dea: 90                           	nop
10008deb: 90                           	nop
10008dec: 90                           	nop
10008ded: 90                           	nop
10008dee: 90                           	nop
10008def: 90                           	nop
10008df0: 6a ff                        	push	-0x1
10008df2: 68 9a e1 04 10               	push	0x1004e19a
10008df7: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
10008dfd: 50                           	push	eax
10008dfe: 64 89 25 00 00 00 00         	mov	dword ptr fs:[0x0], esp
10008e05: 51                           	push	ecx
10008e06: 53                           	push	ebx
10008e07: 55                           	push	ebp
10008e08: 8b 6c 24 1c                  	mov	ebp, dword ptr [esp + 0x1c]
10008e0c: 56                           	push	esi
10008e0d: 8b 74 24 24                  	mov	esi, dword ptr [esp + 0x24]
10008e11: 57                           	push	edi
10008e12: 85 ed                        	test	ebp, ebp
10008e14: 8b 5e 1c                     	mov	ebx, dword ptr [esi + 0x1c]
10008e17: 8b f9                        	mov	edi, ecx
10008e19: 89 5c 24 10                  	mov	dword ptr [esp + 0x10], ebx
10008e1d: 0f 85 ae 00 00 00            	jne	0x10008ed1 <.text+0x7ed1>
10008e23: 83 7e 3c 01                  	cmp	dword ptr [esi + 0x3c], 0x1
10008e27: 75 7e                        	jne	0x10008ea7 <.text+0x7ea7>
10008e29: 8b 5e 34                     	mov	ebx, dword ptr [esi + 0x34]
10008e2c: 6a 10                        	push	0x10
10008e2e: c7 46 3c 02 00 00 00         	mov	dword ptr [esi + 0x3c], 0x2
10008e35: e8 26 3e 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
10008e3a: 83 c4 04                     	add	esp, 0x4
10008e3d: 89 44 24 28                  	mov	dword ptr [esp + 0x28], eax
10008e41: 33 c9                        	xor	ecx, ecx
10008e43: 3b c1                        	cmp	eax, ecx
10008e45: 89 4c 24 1c                  	mov	dword ptr [esp + 0x1c], ecx
10008e49: 74 10                        	je	0x10008e5b <.text+0x7e5b>
10008e4b: 6a 02                        	push	0x2
10008e4d: 53                           	push	ebx
10008e4e: 8b c8                        	mov	ecx, eax
10008e50: e8 bf 41 04 00               	call	0x1004d014 <DllRegisterServer+0x20034>
10008e55: 89 44 24 28                  	mov	dword ptr [esp + 0x28], eax
10008e59: eb 04                        	jmp	0x10008e5f <.text+0x7e5f>
10008e5b: 89 4c 24 28                  	mov	dword ptr [esp + 0x28], ecx
10008e5f: 53                           	push	ebx
10008e60: c7 44 24 20 ff ff ff ff      	mov	dword ptr [esp + 0x20], 0xffffffff
10008e68: e8 e9 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008e6d: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
10008e70: 8b 5e 38                     	mov	ebx, dword ptr [esi + 0x38]
10008e73: 50                           	push	eax
10008e74: e8 dd 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008e79: 56                           	push	esi
10008e7a: e8 d7 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008e7f: 83 c4 0c                     	add	esp, 0xc
10008e82: 85 ff                        	test	edi, edi
10008e84: 75 04                        	jne	0x10008e8a <.text+0x7e8a>
10008e86: 33 c0                        	xor	eax, eax
10008e88: eb 03                        	jmp	0x10008e8d <.text+0x7e8d>
10008e8a: 8b 47 20                     	mov	eax, dword ptr [edi + 0x20]
10008e8d: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
10008e91: 8b 17                        	mov	edx, dword ptr [edi]
10008e93: 6a 02                        	push	0x2
10008e95: 51                           	push	ecx
10008e96: 8b 4c 24 30                  	mov	ecx, dword ptr [esp + 0x30]
10008e9a: 51                           	push	ecx
10008e9b: 53                           	push	ebx
10008e9c: 50                           	push	eax
10008e9d: 8b cf                        	mov	ecx, edi
10008e9f: ff 92 ec 00 00 00            	call	dword ptr [edx + 0xec]
10008ea5: eb 3c                        	jmp	0x10008ee3 <.text+0x7ee3>
10008ea7: 8b 56 34                     	mov	edx, dword ptr [esi + 0x34]
10008eaa: 52                           	push	edx
10008eab: e8 a6 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008eb0: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
10008eb3: 50                           	push	eax
10008eb4: e8 9d 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008eb9: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
10008ebc: 51                           	push	ecx
10008ebd: e8 94 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008ec2: 56                           	push	esi
10008ec3: e8 8e 3e 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
10008ec8: 83 c4 10                     	add	esp, 0x10
10008ecb: 6a 00                        	push	0x0
10008ecd: 6a 00                        	push	0x0
10008ecf: eb 06                        	jmp	0x10008ed7 <.text+0x7ed7>
10008ed1: 68 f1 0c 00 00               	push	0xcf1
10008ed6: 55                           	push	ebp
10008ed7: 68 15 2f 00 00               	push	0x2f15
10008edc: 53                           	push	ebx
10008edd: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
10008ee3: 8b 4c 24 14                  	mov	ecx, dword ptr [esp + 0x14]
10008ee7: 5f                           	pop	edi
10008ee8: 8b c5                        	mov	eax, ebp
10008eea: 5e                           	pop	esi
10008eeb: 5d                           	pop	ebp
10008eec: 5b                           	pop	ebx
10008eed: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
10008ef4: 83 c4 10                     	add	esp, 0x10
10008ef7: c2 08 00                     	ret	0x8
```

## 0x1000a040–0x1000a2a4

File start offset: 0xa040

```asm
1000a040: 81 ec cc 00 00 00            	sub	esp, 0xcc
1000a046: 53                           	push	ebx
1000a047: 55                           	push	ebp
1000a048: 8b e9                        	mov	ebp, ecx
1000a04a: 56                           	push	esi
1000a04b: 57                           	push	edi
1000a04c: 8b 45 00                     	mov	eax, dword ptr [ebp]
1000a04f: ff 90 e0 00 00 00            	call	dword ptr [eax + 0xe0]
1000a055: 66 3d ff 00                  	cmp	ax, 0xff
1000a059: 0f 84 ad 01 00 00            	je	0x1000a20c <.text+0x920c>
1000a05f: 8b 8c 24 e0 00 00 00         	mov	ecx, dword ptr [esp + 0xe0]
1000a066: 8b 7c 8d 5c                  	mov	edi, dword ptr [ebp + 4*ecx + 0x5c]
1000a06a: 85 ff                        	test	edi, edi
1000a06c: 0f 84 9a 01 00 00            	je	0x1000a20c <.text+0x920c>
1000a072: 8b b4 24 e4 00 00 00         	mov	esi, dword ptr [esp + 0xe4]
1000a079: b0 20                        	mov	al, 0x20
1000a07b: 88 44 24 10                  	mov	byte ptr [esp + 0x10], al
1000a07f: 88 44 24 11                  	mov	byte ptr [esp + 0x11], al
1000a083: 88 44 24 12                  	mov	byte ptr [esp + 0x12], al
1000a087: 88 44 24 13                  	mov	byte ptr [esp + 0x13], al
1000a08b: 88 44 24 14                  	mov	byte ptr [esp + 0x14], al
1000a08f: 88 44 24 15                  	mov	byte ptr [esp + 0x15], al
1000a093: 88 44 24 16                  	mov	byte ptr [esp + 0x16], al
1000a097: 88 44 24 17                  	mov	byte ptr [esp + 0x17], al
1000a09b: 88 44 24 18                  	mov	byte ptr [esp + 0x18], al
1000a09f: 88 44 24 19                  	mov	byte ptr [esp + 0x19], al
1000a0a3: 88 44 24 1a                  	mov	byte ptr [esp + 0x1a], al
1000a0a7: 88 44 24 1b                  	mov	byte ptr [esp + 0x1b], al
1000a0ab: 33 c0                        	xor	eax, eax
1000a0ad: 0f bf c8                     	movsx	ecx, ax
1000a0b0: 8a 14 31                     	mov	dl, byte ptr [ecx + esi]
1000a0b3: 84 d2                        	test	dl, dl
1000a0b5: 74 0b                        	je	0x1000a0c2 <.text+0x90c2>
1000a0b7: 40                           	inc	eax
1000a0b8: 88 54 0c 10                  	mov	byte ptr [esp + ecx + 0x10], dl
1000a0bc: 66 3d 0c 00                  	cmp	ax, 0xc
1000a0c0: 7c eb                        	jl	0x1000a0ad <.text+0x90ad>
1000a0c2: 8d 54 24 10                  	lea	edx, [esp + 0x10]
1000a0c6: 52                           	push	edx
1000a0c7: e8 f4 a4 ff ff               	call	0x100045c0 <.text+0x35c0>
1000a0cc: 8b 45 58                     	mov	eax, dword ptr [ebp + 0x58]
1000a0cf: 83 c4 04                     	add	esp, 0x4
1000a0d2: 8d 4c 24 10                  	lea	ecx, [esp + 0x10]
1000a0d6: 8d 9d 5c 04 00 00            	lea	ebx, [ebp + 0x45c]
1000a0dc: 50                           	push	eax
1000a0dd: 51                           	push	ecx
1000a0de: 8b cb                        	mov	ecx, ebx
1000a0e0: e8 9b a3 ff ff               	call	0x10004480 <.text+0x3480>
1000a0e5: 66 3d ff ff                  	cmp	ax, 0xffff
1000a0e9: 0f 85 fc 00 00 00            	jne	0x1000a1eb <.text+0x91eb>
1000a0ef: 8d 54 24 10                  	lea	edx, [esp + 0x10]
1000a0f3: 52                           	push	edx
1000a0f4: e8 c7 9b ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000a0f9: 8b 07                        	mov	eax, dword ptr [edi]
1000a0fb: 83 c4 04                     	add	esp, 0x4
1000a0fe: 8b cf                        	mov	ecx, edi
1000a100: ff 50 18                     	call	dword ptr [eax + 0x18]
1000a103: b9 30 00 00 00               	mov	ecx, 0x30
1000a108: 8b f0                        	mov	esi, eax
1000a10a: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
1000a10e: 8d 7c 24 1c                  	lea	edi, [esp + 0x1c]
1000a112: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
1000a114: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
1000a118: 89 44 24 27                  	mov	dword ptr [esp + 0x27], eax
1000a11c: 8b 84 24 e8 00 00 00         	mov	eax, dword ptr [esp + 0xe8]
1000a123: 8b 54 24 14                  	mov	edx, dword ptr [esp + 0x14]
1000a127: 66 3d 7f 00                  	cmp	ax, 0x7f
1000a12b: 89 4c 24 1f                  	mov	dword ptr [esp + 0x1f], ecx
1000a12f: 0f 9f c1                     	setg	cl
1000a132: 49                           	dec	ecx
1000a133: 68 00 02 00 00               	push	0x200
1000a138: 23 c8                        	and	ecx, eax
1000a13a: 89 54 24 27                  	mov	dword ptr [esp + 0x27], edx
1000a13e: 88 4c 24 2f                  	mov	byte ptr [esp + 0x2f], cl
1000a142: e8 19 2b 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000a147: 8b f8                        	mov	edi, eax
1000a149: 83 c4 04                     	add	esp, 0x4
1000a14c: 85 ff                        	test	edi, edi
1000a14e: 0f 84 90 00 00 00            	je	0x1000a1e4 <.text+0x91e4>
1000a154: 6a 40                        	push	0x40
1000a156: e8 05 2b 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000a15b: 83 c4 04                     	add	esp, 0x4
1000a15e: 8d 54 24 1c                  	lea	edx, [esp + 0x1c]
1000a162: 8b cb                        	mov	ecx, ebx
1000a164: 8b f0                        	mov	esi, eax
1000a166: 52                           	push	edx
1000a167: 68 c0 00 00 00               	push	0xc0
1000a16c: 57                           	push	edi
1000a16d: 6a 00                        	push	0x0
1000a16f: 6a 00                        	push	0x0
1000a171: 68 80 00 00 00               	push	0x80
1000a176: 6a 07                        	push	0x7
1000a178: e8 c3 9b ff ff               	call	0x10003d40 <.text+0x2d40>
1000a17d: b9 01 00 00 00               	mov	ecx, 0x1
1000a182: 8b 94 24 ec 00 00 00         	mov	edx, dword ptr [esp + 0xec]
1000a189: 89 0e                        	mov	dword ptr [esi], ecx
1000a18b: 89 4e 04                     	mov	dword ptr [esi + 0x4], ecx
1000a18e: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
1000a191: 89 7e 0c                     	mov	dword ptr [esi + 0xc], edi
1000a194: 89 7e 10                     	mov	dword ptr [esi + 0x10], edi
1000a197: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
1000a19a: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
1000a19d: 33 c0                        	xor	eax, eax
1000a19f: 89 46 24                     	mov	dword ptr [esi + 0x24], eax
1000a1a2: 89 46 28                     	mov	dword ptr [esi + 0x28], eax
1000a1a5: 8b 84 24 e0 00 00 00         	mov	eax, dword ptr [esp + 0xe0]
1000a1ac: c7 46 18 1e 2f 00 00         	mov	dword ptr [esi + 0x18], 0x2f1e
1000a1b3: 89 56 1c                     	mov	dword ptr [esi + 0x1c], edx
1000a1b6: 89 4e 20                     	mov	dword ptr [esi + 0x20], ecx
1000a1b9: 89 46 30                     	mov	dword ptr [esi + 0x30], eax
1000a1bc: 8b 95 68 04 00 00            	mov	edx, dword ptr [ebp + 0x468]
1000a1c2: 0f bf 8d 70 04 00 00         	movsx	ecx, word ptr [ebp + 0x470]
1000a1c9: 56                           	push	esi
1000a1ca: 51                           	push	ecx
1000a1cb: 68 fb 2e 00 00               	push	0x2efb
1000a1d0: 52                           	push	edx
1000a1d1: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a1d7: 5f                           	pop	edi
1000a1d8: 5e                           	pop	esi
1000a1d9: 5d                           	pop	ebp
1000a1da: 5b                           	pop	ebx
1000a1db: 81 c4 cc 00 00 00            	add	esp, 0xcc
1000a1e1: c2 10 00                     	ret	0x10
1000a1e4: b8 e8 03 00 00               	mov	eax, 0x3e8
1000a1e9: eb 05                        	jmp	0x1000a1f0 <.text+0x91f0>
1000a1eb: b8 ef 03 00 00               	mov	eax, 0x3ef
1000a1f0: 8b 8c 24 ec 00 00 00         	mov	ecx, dword ptr [esp + 0xec]
1000a1f7: 68 dd 10 00 00               	push	0x10dd
1000a1fc: 0f bf c0                     	movsx	eax, ax
1000a1ff: 50                           	push	eax
1000a200: 68 1e 2f 00 00               	push	0x2f1e
1000a205: 51                           	push	ecx
1000a206: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a20c: 5f                           	pop	edi
1000a20d: 5e                           	pop	esi
1000a20e: 5d                           	pop	ebp
1000a20f: 5b                           	pop	ebx
1000a210: 81 c4 cc 00 00 00            	add	esp, 0xcc
1000a216: c2 10 00                     	ret	0x10
1000a219: 90                           	nop
1000a21a: 90                           	nop
1000a21b: 90                           	nop
1000a21c: 90                           	nop
1000a21d: 90                           	nop
1000a21e: 90                           	nop
1000a21f: 90                           	nop
1000a220: 56                           	push	esi
1000a221: 8b 74 24 0c                  	mov	esi, dword ptr [esp + 0xc]
1000a225: 57                           	push	edi
1000a226: 8b f9                        	mov	edi, ecx
1000a228: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
1000a22b: 8d 44 24 10                  	lea	eax, [esp + 0x10]
1000a22f: 50                           	push	eax
1000a230: 51                           	push	ecx
1000a231: 8d 8f 5c 04 00 00            	lea	ecx, [edi + 0x45c]
1000a237: e8 34 9d ff ff               	call	0x10003f70 <.text+0x2f70>
1000a23c: 80 7c 24 10 16               	cmp	byte ptr [esp + 0x10], 0x16
1000a241: 75 61                        	jne	0x1000a2a4 <.text+0x92a4>
1000a243: 8b 56 10                     	mov	edx, dword ptr [esi + 0x10]
1000a246: 80 3a 00                     	cmp	byte ptr [edx], 0x0
1000a249: 75 59                        	jne	0x1000a2a4 <.text+0x92a4>
1000a24b: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
1000a24e: 8b 07                        	mov	eax, dword ptr [edi]
1000a250: 33 d2                        	xor	edx, edx
1000a252: 51                           	push	ecx
1000a253: 8a 56 30                     	mov	dl, byte ptr [esi + 0x30]
1000a256: 6a 00                        	push	0x0
1000a258: 68 ff 00 00 00               	push	0xff
1000a25d: 52                           	push	edx
1000a25e: 8b cf                        	mov	ecx, edi
1000a260: ff 90 54 01 00 00            	call	dword ptr [eax + 0x154]
1000a266: 8b 7c 24 0c                  	mov	edi, dword ptr [esp + 0xc]
1000a26a: 85 ff                        	test	edi, edi
1000a26c: 74 16                        	je	0x1000a284 <.text+0x9284>
1000a26e: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
1000a271: 6a 00                        	push	0x0
1000a273: 57                           	push	edi
1000a274: 68 1e 2f 00 00               	push	0x2f1e
1000a279: 50                           	push	eax
1000a27a: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a280: 85 ff                        	test	edi, edi
1000a282: 75 07                        	jne	0x1000a28b <.text+0x928b>
1000a284: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
1000a287: 85 c0                        	test	eax, eax
1000a289: 74 12                        	je	0x1000a29d <.text+0x929d>
1000a28b: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
1000a28e: 51                           	push	ecx
1000a28f: e8 c2 2a 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
1000a294: 56                           	push	esi
1000a295: e8 bc 2a 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
1000a29a: 83 c4 08                     	add	esp, 0x8
1000a29d: 8b c7                        	mov	eax, edi
1000a29f: 5f                           	pop	edi
1000a2a0: 5e                           	pop	esi
1000a2a1: c2 08 00                     	ret	0x8
1000a2a4: bf eb 03 00 00               	mov	edi, 0x3eb
```

## 0x1000a2b0–0x1000a536

File start offset: 0xa2b0

```asm
1000a2b0: 8b 44 24 04                  	mov	eax, dword ptr [esp + 0x4]
1000a2b4: 81 ec c4 00 00 00            	sub	esp, 0xc4
1000a2ba: 55                           	push	ebp
1000a2bb: 8b e9                        	mov	ebp, ecx
1000a2bd: 56                           	push	esi
1000a2be: 57                           	push	edi
1000a2bf: 8b 4c 85 5c                  	mov	ecx, dword ptr [ebp + 4*eax + 0x5c]
1000a2c3: 85 c9                        	test	ecx, ecx
1000a2c5: 0f 84 5b 01 00 00            	je	0x1000a426 <.text+0x9426>
1000a2cb: 8b bc 24 dc 00 00 00         	mov	edi, dword ptr [esp + 0xdc]
1000a2d2: 8b 11                        	mov	edx, dword ptr [ecx]
1000a2d4: 57                           	push	edi
1000a2d5: ff 52 24                     	call	dword ptr [edx + 0x24]
1000a2d8: 8b f0                        	mov	esi, eax
1000a2da: 85 f6                        	test	esi, esi
1000a2dc: 0f 84 44 01 00 00            	je	0x1000a426 <.text+0x9426>
1000a2e2: 66 83 ff 63                  	cmp	di, 0x63
1000a2e6: 0f 8f 3a 01 00 00            	jg	0x1000a426 <.text+0x9426>
1000a2ec: 68 00 02 00 00               	push	0x200
1000a2f1: e8 6a 29 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000a2f6: 83 c4 04                     	add	esp, 0x4
1000a2f9: 89 44 24 0c                  	mov	dword ptr [esp + 0xc], eax
1000a2fd: 85 c0                        	test	eax, eax
1000a2ff: 0f 84 f4 00 00 00            	je	0x1000a3f9 <.text+0x93f9>
1000a305: 53                           	push	ebx
1000a306: 6a 40                        	push	0x40
1000a308: e8 53 29 04 00               	call	0x1004cc60 <DllRegisterServer+0x1fc80>
1000a30d: 8b d8                        	mov	ebx, eax
1000a30f: 8b 06                        	mov	eax, dword ptr [esi]
1000a311: 83 c4 04                     	add	esp, 0x4
1000a314: 8b ce                        	mov	ecx, esi
1000a316: ff 50 20                     	call	dword ptr [eax + 0x20]
1000a319: b9 30 00 00 00               	mov	ecx, 0x30
1000a31e: 8b f0                        	mov	esi, eax
1000a320: 8d 7c 24 14                  	lea	edi, [esp + 0x14]
1000a324: f3 a5                        	rep		movsd	dword ptr es:[edi], dword ptr [esi]
1000a326: 8d 4c 24 36                  	lea	ecx, [esp + 0x36]
1000a32a: 51                           	push	ecx
1000a32b: e8 90 99 ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000a330: 8d 54 24 52                  	lea	edx, [esp + 0x52]
1000a334: 52                           	push	edx
1000a335: e8 86 99 ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000a33a: 8d 44 24 6e                  	lea	eax, [esp + 0x6e]
1000a33e: 50                           	push	eax
1000a33f: e8 7c 99 ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000a344: 8d 8c 24 8a 00 00 00         	lea	ecx, [esp + 0x8a]
1000a34b: 51                           	push	ecx
1000a34c: e8 6f 99 ff ff               	call	0x10003cc0 <.text+0x2cc0>
1000a351: 8b 74 24 20                  	mov	esi, dword ptr [esp + 0x20]
1000a355: 8b 84 24 f0 00 00 00         	mov	eax, dword ptr [esp + 0xf0]
1000a35c: 8b bc 24 ec 00 00 00         	mov	edi, dword ptr [esp + 0xec]
1000a363: 83 c4 10                     	add	esp, 0x10
1000a366: 8d 54 24 14                  	lea	edx, [esp + 0x14]
1000a36a: 8d 8d 5c 04 00 00            	lea	ecx, [ebp + 0x45c]
1000a370: 52                           	push	edx
1000a371: 68 c0 00 00 00               	push	0xc0
1000a376: 56                           	push	esi
1000a377: 6a 00                        	push	0x0
1000a379: 50                           	push	eax
1000a37a: 57                           	push	edi
1000a37b: 6a 09                        	push	0x9
1000a37d: e8 be 99 ff ff               	call	0x10003d40 <.text+0x2d40>
1000a382: b9 01 00 00 00               	mov	ecx, 0x1
1000a387: 89 43 08                     	mov	dword ptr [ebx + 0x8], eax
1000a38a: 8b 84 24 e4 00 00 00         	mov	eax, dword ptr [esp + 0xe4]
1000a391: 89 0b                        	mov	dword ptr [ebx], ecx
1000a393: 89 4b 04                     	mov	dword ptr [ebx + 0x4], ecx
1000a396: 89 73 0c                     	mov	dword ptr [ebx + 0xc], esi
1000a399: 89 73 10                     	mov	dword ptr [ebx + 0x10], esi
1000a39c: 8b 55 20                     	mov	edx, dword ptr [ebp + 0x20]
1000a39f: 89 43 1c                     	mov	dword ptr [ebx + 0x1c], eax
1000a3a2: 89 4b 20                     	mov	dword ptr [ebx + 0x20], ecx
1000a3a5: 0f bf 84 24 e0 00 00 00      	movsx	eax, word ptr [esp + 0xe0]
1000a3ad: 0f bf cf                     	movsx	ecx, di
1000a3b0: 89 53 14                     	mov	dword ptr [ebx + 0x14], edx
1000a3b3: 8b 94 24 d8 00 00 00         	mov	edx, dword ptr [esp + 0xd8]
1000a3ba: c7 43 18 1f 2f 00 00         	mov	dword ptr [ebx + 0x18], 0x2f1f
1000a3c1: c7 43 24 00 00 00 00         	mov	dword ptr [ebx + 0x24], 0x0
1000a3c8: 89 4b 28                     	mov	dword ptr [ebx + 0x28], ecx
1000a3cb: 89 53 30                     	mov	dword ptr [ebx + 0x30], edx
1000a3ce: 89 43 34                     	mov	dword ptr [ebx + 0x34], eax
1000a3d1: 8b 95 68 04 00 00            	mov	edx, dword ptr [ebp + 0x468]
1000a3d7: 0f bf 8d 70 04 00 00         	movsx	ecx, word ptr [ebp + 0x470]
1000a3de: 53                           	push	ebx
1000a3df: 51                           	push	ecx
1000a3e0: 68 fb 2e 00 00               	push	0x2efb
1000a3e5: 52                           	push	edx
1000a3e6: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a3ec: 5b                           	pop	ebx
1000a3ed: 5f                           	pop	edi
1000a3ee: 5e                           	pop	esi
1000a3ef: 5d                           	pop	ebp
1000a3f0: 81 c4 c4 00 00 00            	add	esp, 0xc4
1000a3f6: c2 10 00                     	ret	0x10
1000a3f9: 8b 8c 24 e0 00 00 00         	mov	ecx, dword ptr [esp + 0xe0]
1000a400: 33 c0                        	xor	eax, eax
1000a402: 66 81 bc 24 d8 00 00 00 ff 00	cmp	word ptr [esp + 0xd8], 0xff
1000a40c: 68 47 11 00 00               	push	0x1147
1000a411: 68 e8 03 00 00               	push	0x3e8
1000a416: 0f 95 c0                     	setne	al
1000a419: 05 1e 2f 00 00               	add	eax, 0x2f1e
1000a41e: 50                           	push	eax
1000a41f: 51                           	push	ecx
1000a420: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a426: 5f                           	pop	edi
1000a427: 5e                           	pop	esi
1000a428: 5d                           	pop	ebp
1000a429: 81 c4 c4 00 00 00            	add	esp, 0xc4
1000a42f: c2 10 00                     	ret	0x10
1000a432: 90                           	nop
1000a433: 90                           	nop
1000a434: 90                           	nop
1000a435: 90                           	nop
1000a436: 90                           	nop
1000a437: 90                           	nop
1000a438: 90                           	nop
1000a439: 90                           	nop
1000a43a: 90                           	nop
1000a43b: 90                           	nop
1000a43c: 90                           	nop
1000a43d: 90                           	nop
1000a43e: 90                           	nop
1000a43f: 90                           	nop
1000a440: 51                           	push	ecx
1000a441: 53                           	push	ebx
1000a442: 55                           	push	ebp
1000a443: 56                           	push	esi
1000a444: 57                           	push	edi
1000a445: 8b 7c 24 1c                  	mov	edi, dword ptr [esp + 0x1c]
1000a449: 8b f1                        	mov	esi, ecx
1000a44b: 8d 4c 24 1c                  	lea	ecx, [esp + 0x1c]
1000a44f: 8b 57 10                     	mov	edx, dword ptr [edi + 0x10]
1000a452: 8b 47 28                     	mov	eax, dword ptr [edi + 0x28]
1000a455: 51                           	push	ecx
1000a456: 52                           	push	edx
1000a457: 8d 8e 5c 04 00 00            	lea	ecx, [esi + 0x45c]
1000a45d: 89 44 24 18                  	mov	dword ptr [esp + 0x18], eax
1000a461: e8 0a 9b ff ff               	call	0x10003f70 <.text+0x2f70>
1000a466: 80 7c 24 1c 16               	cmp	byte ptr [esp + 0x1c], 0x16
1000a46b: 0f 85 bd 00 00 00            	jne	0x1000a52e <.text+0x952e>
1000a471: 8b 47 10                     	mov	eax, dword ptr [edi + 0x10]
1000a474: 80 38 00                     	cmp	byte ptr [eax], 0x0
1000a477: 0f 85 b1 00 00 00            	jne	0x1000a52e <.text+0x952e>
1000a47d: 33 c9                        	xor	ecx, ecx
1000a47f: 33 db                        	xor	ebx, ebx
1000a481: 8a 4f 30                     	mov	cl, byte ptr [edi + 0x30]
1000a484: 8a 5f 34                     	mov	bl, byte ptr [edi + 0x34]
1000a487: 8b e9                        	mov	ebp, ecx
1000a489: 43                           	inc	ebx
1000a48a: 8b 4c ae 5c                  	mov	ecx, dword ptr [esi + 4*ebp + 0x5c]
1000a48e: 85 c9                        	test	ecx, ecx
1000a490: 75 0d                        	jne	0x1000a49f <.text+0x949f>
1000a492: 5f                           	pop	edi
1000a493: 5e                           	pop	esi
1000a494: 5d                           	pop	ebp
1000a495: b8 eb 03 00 00               	mov	eax, 0x3eb
1000a49a: 5b                           	pop	ebx
1000a49b: 59                           	pop	ecx
1000a49c: c2 08 00                     	ret	0x8
1000a49f: 8b 11                        	mov	edx, dword ptr [ecx]
1000a4a1: 53                           	push	ebx
1000a4a2: ff 52 24                     	call	dword ptr [edx + 0x24]
1000a4a5: 85 c0                        	test	eax, eax
1000a4a7: 75 6e                        	jne	0x1000a517 <.text+0x9517>
1000a4a9: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
1000a4ac: 8b ce                        	mov	ecx, esi
1000a4ae: 66 c7 00 00 00               	mov	word ptr [eax], 0x0
1000a4b3: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
1000a4b6: 8b 16                        	mov	edx, dword ptr [esi]
1000a4b8: 50                           	push	eax
1000a4b9: 6a 00                        	push	0x0
1000a4bb: 6a 01                        	push	0x1
1000a4bd: ff 92 c8 00 00 00            	call	dword ptr [edx + 0xc8]
1000a4c3: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
1000a4c7: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
1000a4cb: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
1000a4ce: 51                           	push	ecx
1000a4cf: 52                           	push	edx
1000a4d0: 68 1e 2f 00 00               	push	0x2f1e
1000a4d5: 50                           	push	eax
1000a4d6: ff 15 68 68 05 10            	call	dword ptr [0x10056868]
1000a4dc: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
1000a4df: 8b 16                        	mov	edx, dword ptr [esi]
1000a4e1: 50                           	push	eax
1000a4e2: 8b ce                        	mov	ecx, esi
1000a4e4: ff 92 c4 00 00 00            	call	dword ptr [edx + 0xc4]
1000a4ea: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
1000a4ee: 85 c0                        	test	eax, eax
1000a4f0: 75 07                        	jne	0x1000a4f9 <.text+0x94f9>
1000a4f2: 8b 47 20                     	mov	eax, dword ptr [edi + 0x20]
1000a4f5: 85 c0                        	test	eax, eax
1000a4f7: 74 12                        	je	0x1000a50b <.text+0x950b>
1000a4f9: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
1000a4fc: 51                           	push	ecx
1000a4fd: e8 54 28 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
1000a502: 57                           	push	edi
1000a503: e8 4e 28 04 00               	call	0x1004cd56 <DllRegisterServer+0x1fd76>
1000a508: 83 c4 08                     	add	esp, 0x8
1000a50b: 8b 44 24 18                  	mov	eax, dword ptr [esp + 0x18]
1000a50f: 5f                           	pop	edi
1000a510: 5e                           	pop	esi
1000a511: 5d                           	pop	ebp
1000a512: 5b                           	pop	ebx
1000a513: 59                           	pop	ecx
1000a514: c2 08 00                     	ret	0x8
1000a517: 8b 47 1c                     	mov	eax, dword ptr [edi + 0x1c]
1000a51a: 8b 16                        	mov	edx, dword ptr [esi]
1000a51c: 50                           	push	eax
1000a51d: 53                           	push	ebx
1000a51e: 68 ff 00 00 00               	push	0xff
1000a523: 55                           	push	ebp
1000a524: 8b ce                        	mov	ecx, esi
1000a526: ff 92 54 01 00 00            	call	dword ptr [edx + 0x154]
1000a52c: eb bc                        	jmp	0x1000a4ea <.text+0x94ea>
1000a52e: c7 44 24 18 eb 03 00 00      	mov	dword ptr [esp + 0x18], 0x3eb
1000a536: eb c1                        	jmp	0x1000a4f9 <.text+0x94f9>
```
