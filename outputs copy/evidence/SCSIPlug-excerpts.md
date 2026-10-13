# SCSIPlug static disassembly excerpts

Source identity: 0385e9f145b97beb601a91dad18db9bdc6f6748a650fd7aa629a9c9c7fc239e8

Tool: /usr/bin/objdump -d --x86-asm-syntax=intel. Preferred PE virtual addresses; inferred function boundaries, no execution or decompiler. Data/jump tables can be decoded as instructions in linear output; do not treat them as executable facts.

## 0x100010e0–0x10001191

File start offset: 0x10e0

```asm
100010e0: 6a ff                        	push	-0x1
100010e2: 68 d8 46 00 10               	push	0x100046d8
100010e7: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
100010ed: 50                           	push	eax
100010ee: 64 89 25 00 00 00 00         	mov	dword ptr fs:[0x0], esp
100010f5: 83 ec 0c                     	sub	esp, 0xc
100010f8: 56                           	push	esi
100010f9: 8b f1                        	mov	esi, ecx
100010fb: 89 74 24 04                  	mov	dword ptr [esp + 0x4], esi
100010ff: 8b 4c 24 3c                  	mov	ecx, dword ptr [esp + 0x3c]
10001103: 8b 54 24 40                  	mov	edx, dword ptr [esp + 0x40]
10001107: 89 8e 80 00 00 00            	mov	dword ptr [esi + 0x80], ecx
1000110d: b9 01 00 00 00               	mov	ecx, 0x1
10001112: 88 4c 24 0a                  	mov	byte ptr [esp + 0xa], cl
10001116: 88 4c 24 0b                  	mov	byte ptr [esp + 0xb], cl
1000111a: 89 4e 6c                     	mov	dword ptr [esi + 0x6c], ecx
1000111d: 8b 4c 24 28                  	mov	ecx, dword ptr [esp + 0x28]
10001121: 89 96 84 00 00 00            	mov	dword ptr [esi + 0x84], edx
10001127: 8b 54 24 30                  	mov	edx, dword ptr [esp + 0x30]
1000112b: 89 4e 70                     	mov	dword ptr [esi + 0x70], ecx
1000112e: 8b 4c 24 34                  	mov	ecx, dword ptr [esp + 0x34]
10001132: 89 56 74                     	mov	dword ptr [esi + 0x74], edx
10001135: 8b 54 24 38                  	mov	edx, dword ptr [esp + 0x38]
10001139: 89 4e 78                     	mov	dword ptr [esi + 0x78], ecx
1000113c: 8b 4c 24 2c                  	mov	ecx, dword ptr [esp + 0x2c]
10001140: 89 56 7c                     	mov	dword ptr [esi + 0x7c], edx
10001143: 56                           	push	esi
10001144: 68 fa 2e 00 00               	push	0x2efa
10001149: 8d 54 24 10                  	lea	edx, [esp + 0x10]
1000114d: 33 c0                        	xor	eax, eax
1000114f: 51                           	push	ecx
10001150: 8b 4c 24 2c                  	mov	ecx, dword ptr [esp + 0x2c]
10001154: 52                           	push	edx
10001155: 50                           	push	eax
10001156: 50                           	push	eax
10001157: 89 44 24 30                  	mov	dword ptr [esp + 0x30], eax
1000115b: 88 44 24 21                  	mov	byte ptr [esp + 0x21], al
1000115f: 88 44 24 24                  	mov	byte ptr [esp + 0x24], al
10001163: 88 44 24 25                  	mov	byte ptr [esp + 0x25], al
10001167: 50                           	push	eax
10001168: 8b 44 24 40                  	mov	eax, dword ptr [esp + 0x40]
1000116c: 50                           	push	eax
1000116d: 51                           	push	ecx
1000116e: 8b ce                        	mov	ecx, esi
10001170: c7 06 88 52 00 10            	mov	dword ptr [esi], 0x10005288
10001176: c6 44 24 2c 09               	mov	byte ptr [esp + 0x2c], 0x9
1000117b: e8 70 23 00 00               	call	0x100034f0 <.text+0x24f0>
10001180: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
10001184: 8b c6                        	mov	eax, esi
10001186: 5e                           	pop	esi
10001187: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
1000118e: 83 c4 18                     	add	esp, 0x18
10001191: c2 24 00                     	ret	0x24
```

## 0x10001240–0x10001480

File start offset: 0x1240

```asm
10001240: 83 ec 08                     	sub	esp, 0x8
10001243: 53                           	push	ebx
10001244: 55                           	push	ebp
10001245: 56                           	push	esi
10001246: 57                           	push	edi
10001247: 8b f1                        	mov	esi, ecx
10001249: ff 15 1c 52 00 10            	call	dword ptr [0x1000521c]
1000124f: 8b ce                        	mov	ecx, esi
10001251: e8 8a 23 00 00               	call	0x100035e0 <.text+0x25e0>
10001256: 8b f8                        	mov	edi, eax
10001258: 85 ff                        	test	edi, edi
1000125a: 0f 85 17 02 00 00            	jne	0x10001477 <.text+0x477>
10001260: 8b 46 78                     	mov	eax, dword ptr [esi + 0x78]
10001263: c6 46 04 02                  	mov	byte ptr [esi + 0x4], 0x2
10001267: c7 46 10 88 01 00 00         	mov	dword ptr [esi + 0x10], 0x188
1000126e: 8b 48 0c                     	mov	ecx, dword ptr [eax + 0xc]
10001271: c6 46 07 10                  	mov	byte ptr [esi + 0x7], 0x10
10001275: 89 4e 14                     	mov	dword ptr [esi + 0x14], ecx
10001278: 8b ce                        	mov	ecx, esi
1000127a: c6 46 34 0c                  	mov	byte ptr [esi + 0x34], 0xc
1000127e: c6 46 35 00                  	mov	byte ptr [esi + 0x35], 0x0
10001282: c6 46 36 00                  	mov	byte ptr [esi + 0x36], 0x0
10001286: c6 46 37 01                  	mov	byte ptr [esi + 0x37], 0x1
1000128a: c6 46 38 88                  	mov	byte ptr [esi + 0x38], -0x78
1000128e: c6 46 39 00                  	mov	byte ptr [esi + 0x39], 0x0
10001292: 89 7e 6c                     	mov	dword ptr [esi + 0x6c], edi
10001295: e8 c6 17 00 00               	call	0x10002a60 <.text+0x1a60>
1000129a: 8b f8                        	mov	edi, eax
1000129c: bb 64 00 00 00               	mov	ebx, 0x64
100012a1: 85 ff                        	test	edi, edi
100012a3: 0f 85 ce 01 00 00            	jne	0x10001477 <.text+0x477>
100012a9: 8b 2d 1c 50 00 10            	mov	ebp, dword ptr [0x1000501c]
100012af: 8b 46 70                     	mov	eax, dword ptr [esi + 0x70]
100012b2: 80 38 f0                     	cmp	byte ptr [eax], -0x10
100012b5: 0f 85 a2 00 00 00            	jne	0x1000135d <.text+0x35d>
100012bb: 33 d2                        	xor	edx, edx
100012bd: 8a 50 03                     	mov	dl, byte ptr [eax + 0x3]
100012c0: 8b c2                        	mov	eax, edx
100012c2: 83 e8 7c                     	sub	eax, 0x7c
100012c5: 75 63                        	jne	0x1000132a <.text+0x32a>
100012c7: 8b 06                        	mov	eax, dword ptr [esi]
100012c9: 8d 4c 24 10                  	lea	ecx, [esp + 0x10]
100012cd: 51                           	push	ecx
100012ce: 8b ce                        	mov	ecx, esi
100012d0: ff 50 3c                     	call	dword ptr [eax + 0x3c]
100012d3: 8b f8                        	mov	edi, eax
100012d5: 85 ff                        	test	edi, edi
100012d7: 0f 85 9a 01 00 00            	jne	0x10001477 <.text+0x477>
100012dd: 83 7c 24 10 06               	cmp	dword ptr [esp + 0x10], 0x6
100012e2: 74 24                        	je	0x10001308 <.text+0x308>
100012e4: 57                           	push	edi
100012e5: 57                           	push	edi
100012e6: 57                           	push	edi
100012e7: 57                           	push	edi
100012e8: ff 15 34 50 00 10            	call	dword ptr [0x10005034]
100012ee: 8b f8                        	mov	edi, eax
100012f0: 85 ff                        	test	edi, edi
100012f2: 74 5a                        	je	0x1000134e <.text+0x34e>
100012f4: 68 fa 00 00 00               	push	0xfa
100012f9: 57                           	push	edi
100012fa: ff d5                        	call	ebp
100012fc: 57                           	push	edi
100012fd: ff 15 10 50 00 10            	call	dword ptr [0x10005010]
10001303: 4b                           	dec	ebx
10001304: 74 39                        	je	0x1000133f <.text+0x33f>
10001306: eb bf                        	jmp	0x100012c7 <.text+0x2c7>
10001308: 8b 16                        	mov	edx, dword ptr [esi]
1000130a: 8d 44 24 14                  	lea	eax, [esp + 0x14]
1000130e: 50                           	push	eax
1000130f: 6a 06                        	push	0x6
10001311: 8b ce                        	mov	ecx, esi
10001313: c7 44 24 1c 00 00 00 00      	mov	dword ptr [esp + 0x1c], 0x0
1000131b: ff 52 40                     	call	dword ptr [edx + 0x40]
1000131e: 8b f8                        	mov	edi, eax
10001320: 85 ff                        	test	edi, edi
10001322: 0f 85 4f 01 00 00            	jne	0x10001477 <.text+0x477>
10001328: eb 85                        	jmp	0x100012af <.text+0x2af>
1000132a: 48                           	dec	eax
1000132b: 74 12                        	je	0x1000133f <.text+0x33f>
1000132d: 48                           	dec	eax
1000132e: 75 3c                        	jne	0x1000136c <.text+0x36c>
10001330: bf f1 03 00 00               	mov	edi, 0x3f1
10001335: 8b c7                        	mov	eax, edi
10001337: 5f                           	pop	edi
10001338: 5e                           	pop	esi
10001339: 5d                           	pop	ebp
1000133a: 5b                           	pop	ebx
1000133b: 83 c4 08                     	add	esp, 0x8
1000133e: c3                           	ret
1000133f: bf f2 03 00 00               	mov	edi, 0x3f2
10001344: 8b c7                        	mov	eax, edi
10001346: 5f                           	pop	edi
10001347: 5e                           	pop	esi
10001348: 5d                           	pop	ebp
10001349: 5b                           	pop	ebx
1000134a: 83 c4 08                     	add	esp, 0x8
1000134d: c3                           	ret
1000134e: bf 07 00 00 00               	mov	edi, 0x7
10001353: 8b c7                        	mov	eax, edi
10001355: 5f                           	pop	edi
10001356: 5e                           	pop	esi
10001357: 5d                           	pop	ebp
10001358: 5b                           	pop	ebx
10001359: 83 c4 08                     	add	esp, 0x8
1000135c: c3                           	ret
1000135d: bf eb 03 00 00               	mov	edi, 0x3eb
10001362: 8b c7                        	mov	eax, edi
10001364: 5f                           	pop	edi
10001365: 5e                           	pop	esi
10001366: 5d                           	pop	ebp
10001367: 5b                           	pop	ebx
10001368: 83 c4 08                     	add	esp, 0x8
1000136b: c3                           	ret
1000136c: 85 ff                        	test	edi, edi
1000136e: 0f 85 03 01 00 00            	jne	0x10001477 <.text+0x477>
10001374: 68 00 00 01 00               	push	0x10000
10001379: e8 ce 2c 00 00               	call	0x1000404c <DllRegisterServer+0x15c>
1000137e: 8b d8                        	mov	ebx, eax
10001380: 83 c4 04                     	add	esp, 0x4
10001383: 85 db                        	test	ebx, ebx
10001385: 0f 84 e3 00 00 00            	je	0x1000146e <.text+0x46e>
1000138b: 8b 8e 80 00 00 00            	mov	ecx, dword ptr [esi + 0x80]
10001391: 8b 11                        	mov	edx, dword ptr [ecx]
10001393: ff 52 38                     	call	dword ptr [edx + 0x38]
10001396: 8b 8e 84 00 00 00            	mov	ecx, dword ptr [esi + 0x84]
1000139c: 89 44 24 10                  	mov	dword ptr [esp + 0x10], eax
100013a0: 85 c9                        	test	ecx, ecx
100013a2: 74 78                        	je	0x1000141c <.text+0x41c>
100013a4: 85 c0                        	test	eax, eax
100013a6: 0f 84 b5 00 00 00            	je	0x10001461 <.text+0x461>
100013ac: 3d 00 00 01 00               	cmp	eax, 0x10000
100013b1: 76 05                        	jbe	0x100013b8 <.text+0x3b8>
100013b3: b8 00 00 01 00               	mov	eax, 0x10000
100013b8: 8b 8e 80 00 00 00            	mov	ecx, dword ptr [esi + 0x80]
100013be: 50                           	push	eax
100013bf: 53                           	push	ebx
100013c0: 8b 11                        	mov	edx, dword ptr [ecx]
100013c2: ff 52 3c                     	call	dword ptr [edx + 0x3c]
100013c5: 8b e8                        	mov	ebp, eax
100013c7: 85 ed                        	test	ebp, ebp
100013c9: 0f 84 8d 00 00 00            	je	0x1000145c <.text+0x45c>
100013cf: 8b be 84 00 00 00            	mov	edi, dword ptr [esi + 0x84]
100013d5: 4f                           	dec	edi
100013d6: 81 ff 00 80 00 00            	cmp	edi, 0x8000
100013dc: 7d 1d                        	jge	0x100013fb <.text+0x3fb>
100013de: b8 01 80 00 00               	mov	eax, 0x8001
100013e3: 8b cb                        	mov	ecx, ebx
100013e5: 2b c7                        	sub	eax, edi
100013e7: 8d 14 7b                     	lea	edx, [ebx + 2*edi]
100013ea: d1 e8                        	shr	eax
100013ec: 66 8b 3a                     	mov	di, word ptr [edx]
100013ef: 83 c2 04                     	add	edx, 0x4
100013f2: 66 89 39                     	mov	word ptr [ecx], di
100013f5: 83 c1 02                     	add	ecx, 0x2
100013f8: 48                           	dec	eax
100013f9: 75 f1                        	jne	0x100013ec <.text+0x3ec>
100013fb: 8b 06                        	mov	eax, dword ptr [esi]
100013fd: 8b cd                        	mov	ecx, ebp
100013ff: d1 e9                        	shr	ecx
10001401: 53                           	push	ebx
10001402: 51                           	push	ecx
10001403: 8b ce                        	mov	ecx, esi
10001405: ff 50 48                     	call	dword ptr [eax + 0x48]
10001408: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
1000140c: 8b f8                        	mov	edi, eax
1000140e: 2b cd                        	sub	ecx, ebp
10001410: 85 ff                        	test	edi, edi
10001412: 89 4c 24 10                  	mov	dword ptr [esp + 0x10], ecx
10001416: 75 49                        	jne	0x10001461 <.text+0x461>
10001418: 8b c1                        	mov	eax, ecx
1000141a: eb 88                        	jmp	0x100013a4 <.text+0x3a4>
1000141c: 85 c0                        	test	eax, eax
1000141e: 74 41                        	je	0x10001461 <.text+0x461>
10001420: 3d 00 80 00 00               	cmp	eax, 0x8000
10001425: 76 05                        	jbe	0x1000142c <.text+0x42c>
10001427: b8 00 80 00 00               	mov	eax, 0x8000
1000142c: 8b 8e 80 00 00 00            	mov	ecx, dword ptr [esi + 0x80]
10001432: 50                           	push	eax
10001433: 53                           	push	ebx
10001434: 8b 11                        	mov	edx, dword ptr [ecx]
10001436: ff 52 3c                     	call	dword ptr [edx + 0x3c]
10001439: 8b e8                        	mov	ebp, eax
1000143b: 85 ed                        	test	ebp, ebp
1000143d: 74 1d                        	je	0x1000145c <.text+0x45c>
1000143f: 8b 06                        	mov	eax, dword ptr [esi]
10001441: 53                           	push	ebx
10001442: 55                           	push	ebp
10001443: 8b ce                        	mov	ecx, esi
10001445: ff 50 48                     	call	dword ptr [eax + 0x48]
10001448: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
1000144c: 8b f8                        	mov	edi, eax
1000144e: 2b cd                        	sub	ecx, ebp
10001450: 85 ff                        	test	edi, edi
10001452: 89 4c 24 10                  	mov	dword ptr [esp + 0x10], ecx
10001456: 75 09                        	jne	0x10001461 <.text+0x461>
10001458: 8b c1                        	mov	eax, ecx
1000145a: eb c0                        	jmp	0x1000141c <.text+0x41c>
1000145c: bf d2 04 00 00               	mov	edi, 0x4d2
10001461: 53                           	push	ebx
10001462: e8 eb 2b 00 00               	call	0x10004052 <DllRegisterServer+0x162>
10001467: 83 c4 04                     	add	esp, 0x4
1000146a: 85 ff                        	test	edi, edi
1000146c: 75 09                        	jne	0x10001477 <.text+0x477>
1000146e: 8b 16                        	mov	edx, dword ptr [esi]
10001470: 8b ce                        	mov	ecx, esi
10001472: ff 52 44                     	call	dword ptr [edx + 0x44]
10001475: 8b f8                        	mov	edi, eax
10001477: 8b c7                        	mov	eax, edi
10001479: 5f                           	pop	edi
1000147a: 5e                           	pop	esi
1000147b: 5d                           	pop	ebp
1000147c: 5b                           	pop	ebx
1000147d: 83 c4 08                     	add	esp, 0x8
10001480: c3                           	ret
```

## 0x10001490–0x100014e3

File start offset: 0x1490

```asm
10001490: 8b 44 24 04                  	mov	eax, dword ptr [esp + 0x4]
10001494: 56                           	push	esi
10001495: 8b f1                        	mov	esi, ecx
10001497: 8b d0                        	mov	edx, eax
10001499: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
1000149d: 57                           	push	edi
1000149e: 8b 7e 70                     	mov	edi, dword ptr [esi + 0x70]
100014a1: 89 4e 14                     	mov	dword ptr [esi + 0x14], ecx
100014a4: c1 fa 10                     	sar	edx, 0x10
100014a7: 88 56 36                     	mov	byte ptr [esi + 0x36], dl
100014aa: 33 c9                        	xor	ecx, ecx
100014ac: 8b d0                        	mov	edx, eax
100014ae: 88 4e 35                     	mov	byte ptr [esi + 0x35], cl
100014b1: c1 fa 08                     	sar	edx, 0x8
100014b4: 89 4e 70                     	mov	dword ptr [esi + 0x70], ecx
100014b7: 8b ce                        	mov	ecx, esi
100014b9: c7 46 6c 01 00 00 00         	mov	dword ptr [esi + 0x6c], 0x1
100014c0: c6 46 04 02                  	mov	byte ptr [esi + 0x4], 0x2
100014c4: 89 46 10                     	mov	dword ptr [esi + 0x10], eax
100014c7: c6 46 07 10                  	mov	byte ptr [esi + 0x7], 0x10
100014cb: c6 46 34 0c                  	mov	byte ptr [esi + 0x34], 0xc
100014cf: 88 56 37                     	mov	byte ptr [esi + 0x37], dl
100014d2: 88 46 38                     	mov	byte ptr [esi + 0x38], al
100014d5: c6 46 39 80                  	mov	byte ptr [esi + 0x39], -0x80
100014d9: e8 82 15 00 00               	call	0x10002a60 <.text+0x1a60>
100014de: 89 7e 70                     	mov	dword ptr [esi + 0x70], edi
100014e1: 5f                           	pop	edi
100014e2: 5e                           	pop	esi
100014e3: c2 08 00                     	ret	0x8
```

## 0x100027e0–0x1000292c

File start offset: 0x27e0

```asm
100027e0: 8b 44 24 04                  	mov	eax, dword ptr [esp + 0x4]
100027e4: 56                           	push	esi
100027e5: 89 81 d8 02 00 00            	mov	dword ptr [ecx + 0x2d8], eax
100027eb: 8b 44 24 0c                  	mov	eax, dword ptr [esp + 0xc]
100027ef: 33 f6                        	xor	esi, esi
100027f1: 85 c0                        	test	eax, eax
100027f3: 74 14                        	je	0x10002809 <.text+0x1809>
100027f5: 8a 50 30                     	mov	dl, byte ptr [eax + 0x30]
100027f8: 84 d2                        	test	dl, dl
100027fa: 74 13                        	je	0x1000280f <.text+0x180f>
100027fc: 6a 10                        	push	0x10
100027fe: 56                           	push	esi
100027ff: 68 94 72 00 10               	push	0x10007294
10002804: e8 5d 19 00 00               	call	0x10004166 <DllRegisterServer+0x276>
10002809: 8b c6                        	mov	eax, esi
1000280b: 5e                           	pop	esi
1000280c: c2 08 00                     	ret	0x8
1000280f: 50                           	push	eax
10002810: e8 0b 00 00 00               	call	0x10002820 <.text+0x1820>
10002815: 5e                           	pop	esi
10002816: c2 08 00                     	ret	0x8
10002819: 90                           	nop
1000281a: 90                           	nop
1000281b: 90                           	nop
1000281c: 90                           	nop
1000281d: 90                           	nop
1000281e: 90                           	nop
1000281f: 90                           	nop
10002820: 55                           	push	ebp
10002821: 8b ec                        	mov	ebp, esp
10002823: 6a ff                        	push	-0x1
10002825: 68 4c 49 00 10               	push	0x1000494c
1000282a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
10002830: 50                           	push	eax
10002831: 64 89 25 00 00 00 00         	mov	dword ptr fs:[0x0], esp
10002838: 83 ec 24                     	sub	esp, 0x24
1000283b: 53                           	push	ebx
1000283c: 56                           	push	esi
1000283d: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
10002840: 57                           	push	edi
10002841: 8b f9                        	mov	edi, ecx
10002843: 33 c0                        	xor	eax, eax
10002845: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
10002848: 8b 5e 34                     	mov	ebx, dword ptr [esi + 0x34]
1000284b: 89 4d e0                     	mov	dword ptr [ebp - 0x20], ecx
1000284e: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
10002851: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
10002854: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
10002857: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
1000285a: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
1000285d: e8 40 19 00 00               	call	0x100041a2 <DllRegisterServer+0x2b2>
10002862: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
10002869: 6a 10                        	push	0x10
1000286b: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
1000286f: e8 d8 17 00 00               	call	0x1000404c <DllRegisterServer+0x15c>
10002874: 8b c8                        	mov	ecx, eax
10002876: 83 c4 04                     	add	esp, 0x4
10002879: 89 4d dc                     	mov	dword ptr [ebp - 0x24], ecx
1000287c: 85 c9                        	test	ecx, ecx
1000287e: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
10002882: 74 0c                        	je	0x10002890 <.text+0x1890>
10002884: 6a 02                        	push	0x2
10002886: 53                           	push	ebx
10002887: e8 10 19 00 00               	call	0x1000419c <DllRegisterServer+0x2ac>
1000288c: 8b d8                        	mov	ebx, eax
1000288e: eb 20                        	jmp	0x100028b0 <.text+0x18b0>
10002890: 33 db                        	xor	ebx, ebx
10002892: eb 1c                        	jmp	0x100028b0 <.text+0x18b0>
10002894: 8b 55 d8                     	mov	edx, dword ptr [ebp - 0x28]
10002897: c7 45 ec ff ff ff ff         	mov	dword ptr [ebp - 0x14], 0xffffffff
1000289e: 89 55 d4                     	mov	dword ptr [ebp - 0x2c], edx
100028a1: b8 a7 28 00 10               	mov	eax, 0x100028a7
100028a6: c3                           	ret
100028a7: 8b 7d e8                     	mov	edi, dword ptr [ebp - 0x18]
100028aa: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
100028ad: 8b 5d e4                     	mov	ebx, dword ptr [ebp - 0x1c]
100028b0: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
100028b7: e8 da 18 00 00               	call	0x10004196 <DllRegisterServer+0x2a6>
100028bc: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
100028bf: 85 c0                        	test	eax, eax
100028c1: 75 6c                        	jne	0x1000292f <.text+0x192f>
100028c3: 68 88 00 00 00               	push	0x88
100028c8: e8 7f 17 00 00               	call	0x1000404c <DllRegisterServer+0x15c>
100028cd: 83 c4 04                     	add	esp, 0x4
100028d0: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
100028d3: 85 c0                        	test	eax, eax
100028d5: c7 45 fc 04 00 00 00         	mov	dword ptr [ebp - 0x4], 0x4
100028dc: 74 39                        	je	0x10002917 <.text+0x1917>
100028de: 8b 97 d8 02 00 00            	mov	edx, dword ptr [edi + 0x2d8]
100028e4: 8d 0c d2                     	lea	ecx, [edx + 8*edx]
100028e7: 8d 14 4a                     	lea	edx, [edx + 2*ecx]
100028ea: 8b 4d e0                     	mov	ecx, dword ptr [ebp - 0x20]
100028ed: 51                           	push	ecx
100028ee: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
100028f1: 53                           	push	ebx
100028f2: 51                           	push	ecx
100028f3: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
100028f6: 56                           	push	esi
100028f7: 51                           	push	ecx
100028f8: 8b 4f 20                     	mov	ecx, dword ptr [edi + 0x20]
100028fb: 51                           	push	ecx
100028fc: 8b 0d 2c 74 00 10            	mov	ecx, dword ptr [0x1000742c]
10002902: 8d 14 57                     	lea	edx, [edi + 2*edx]
10002905: 51                           	push	ecx
10002906: 8a 4a 6e                     	mov	cl, byte ptr [edx + 0x6e]
10002909: 8a 52 6d                     	mov	dl, byte ptr [edx + 0x6d]
1000290c: 51                           	push	ecx
1000290d: 52                           	push	edx
1000290e: 8b c8                        	mov	ecx, eax
10002910: e8 cb e7 ff ff               	call	0x100010e0 <.text+0xe0>
10002915: eb 02                        	jmp	0x10002919 <.text+0x1919>
10002917: 33 c0                        	xor	eax, eax
10002919: 85 c0                        	test	eax, eax
1000291b: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
10002922: 74 08                        	je	0x1000292c <.text+0x192c>
10002924: 50                           	push	eax
10002925: 8b cf                        	mov	ecx, edi
10002927: e8 34 f0 ff ff               	call	0x10001960 <.text+0x960>
1000292c: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
```

## 0x10002990–0x10002a4b

File start offset: 0x2990

```asm
10002990: 6a ff                        	push	-0x1
10002992: 68 68 49 00 10               	push	0x10004968
10002997: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
1000299d: 50                           	push	eax
1000299e: 64 89 25 00 00 00 00         	mov	dword ptr fs:[0x0], esp
100029a5: 83 ec 0c                     	sub	esp, 0xc
100029a8: 56                           	push	esi
100029a9: 8b f1                        	mov	esi, ecx
100029ab: 89 74 24 04                  	mov	dword ptr [esp + 0x4], esi
100029af: 33 c0                        	xor	eax, eax
100029b1: 56                           	push	esi
100029b2: 89 44 24 1c                  	mov	dword ptr [esp + 0x1c], eax
100029b6: 88 44 24 0d                  	mov	byte ptr [esp + 0xd], al
100029ba: 8b 44 24 2c                  	mov	eax, dword ptr [esp + 0x2c]
100029be: 68 fa 2e 00 00               	push	0x2efa
100029c3: 8b c8                        	mov	ecx, eax
100029c5: 8b d0                        	mov	edx, eax
100029c7: c1 e9 10                     	shr	ecx, 0x10
100029ca: 88 4c 24 12                  	mov	byte ptr [esp + 0x12], cl
100029ce: 8b 4c 24 3c                  	mov	ecx, dword ptr [esp + 0x3c]
100029d2: c1 ea 08                     	shr	edx, 0x8
100029d5: 88 54 24 13                  	mov	byte ptr [esp + 0x13], dl
100029d9: 8b d1                        	mov	edx, ecx
100029db: f7 da                        	neg	edx
100029dd: 1a d2                        	sbb	dl, dl
100029df: 89 4e 6c                     	mov	dword ptr [esi + 0x6c], ecx
100029e2: 8b 4c 24 38                  	mov	ecx, dword ptr [esp + 0x38]
100029e6: 81 e2 80 00 00 00            	and	edx, 0x80
100029ec: 88 54 24 15                  	mov	byte ptr [esp + 0x15], dl
100029f0: 8b 54 24 44                  	mov	edx, dword ptr [esp + 0x44]
100029f4: 89 4e 70                     	mov	dword ptr [esi + 0x70], ecx
100029f7: 8b 4c 24 48                  	mov	ecx, dword ptr [esp + 0x48]
100029fb: 89 56 74                     	mov	dword ptr [esi + 0x74], edx
100029fe: 8b 54 24 4c                  	mov	edx, dword ptr [esp + 0x4c]
10002a02: 89 4e 78                     	mov	dword ptr [esi + 0x78], ecx
10002a05: 8b 4c 24 40                  	mov	ecx, dword ptr [esp + 0x40]
10002a09: 89 56 7c                     	mov	dword ptr [esi + 0x7c], edx
10002a0c: 51                           	push	ecx
10002a0d: 8b 4c 24 38                  	mov	ecx, dword ptr [esp + 0x38]
10002a11: 8d 54 24 14                  	lea	edx, [esp + 0x14]
10002a15: 52                           	push	edx
10002a16: 8b 54 24 34                  	mov	edx, dword ptr [esp + 0x34]
10002a1a: 51                           	push	ecx
10002a1b: 88 44 24 20                  	mov	byte ptr [esp + 0x20], al
10002a1f: 50                           	push	eax
10002a20: 8b 44 24 38                  	mov	eax, dword ptr [esp + 0x38]
10002a24: 6a 10                        	push	0x10
10002a26: 52                           	push	edx
10002a27: 50                           	push	eax
10002a28: 8b ce                        	mov	ecx, esi
10002a2a: c7 06 b0 55 00 10            	mov	dword ptr [esi], 0x100055b0
10002a30: c6 44 24 2c 0c               	mov	byte ptr [esp + 0x2c], 0xc
10002a35: e8 b6 0a 00 00               	call	0x100034f0 <.text+0x24f0>
10002a3a: 8b 4c 24 10                  	mov	ecx, dword ptr [esp + 0x10]
10002a3e: 8b c6                        	mov	eax, esi
10002a40: 5e                           	pop	esi
10002a41: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
10002a48: 83 c4 18                     	add	esp, 0x18
10002a4b: c2 28 00                     	ret	0x28
```

## 0x10002a60–0x10002b54

File start offset: 0x2a60

```asm
10002a60: 83 ec 0c                     	sub	esp, 0xc
10002a63: 53                           	push	ebx
10002a64: 8b 1d 1c 52 00 10            	mov	ebx, dword ptr [0x1000521c]
10002a6a: 55                           	push	ebp
10002a6b: 56                           	push	esi
10002a6c: 57                           	push	edi
10002a6d: 8b f1                        	mov	esi, ecx
10002a6f: ff d3                        	call	ebx
10002a71: 8b ce                        	mov	ecx, esi
10002a73: 89 44 24 18                  	mov	dword ptr [esp + 0x18], eax
10002a77: e8 64 0b 00 00               	call	0x100035e0 <.text+0x25e0>
10002a7c: 8b f8                        	mov	edi, eax
10002a7e: 85 ff                        	test	edi, edi
10002a80: 0f 85 c3 00 00 00            	jne	0x10002b49 <.text+0x1b49>
10002a86: 8b 46 70                     	mov	eax, dword ptr [esi + 0x70]
10002a89: 85 c0                        	test	eax, eax
10002a8b: 0f 84 b8 00 00 00            	je	0x10002b49 <.text+0x1b49>
10002a91: 57                           	push	edi
10002a92: 57                           	push	edi
10002a93: 57                           	push	edi
10002a94: 57                           	push	edi
10002a95: 89 7c 24 20                  	mov	dword ptr [esp + 0x20], edi
10002a99: ff 15 34 50 00 10            	call	dword ptr [0x10005034]
10002a9f: 8b e8                        	mov	ebp, eax
10002aa1: 85 ed                        	test	ebp, ebp
10002aa3: 0f 84 9b 00 00 00            	je	0x10002b44 <.text+0x1b44>
10002aa9: 89 7c 24 14                  	mov	dword ptr [esp + 0x14], edi
10002aad: 8b 06                        	mov	eax, dword ptr [esi]
10002aaf: 8d 4c 24 10                  	lea	ecx, [esp + 0x10]
10002ab3: 51                           	push	ecx
10002ab4: 8b ce                        	mov	ecx, esi
10002ab6: ff 50 3c                     	call	dword ptr [eax + 0x3c]
10002ab9: 8b f8                        	mov	edi, eax
10002abb: 85 ff                        	test	edi, edi
10002abd: 75 72                        	jne	0x10002b31 <.text+0x1b31>
10002abf: 8b 44 24 10                  	mov	eax, dword ptr [esp + 0x10]
10002ac3: 85 c0                        	test	eax, eax
10002ac5: 74 23                        	je	0x10002aea <.text+0x1aea>
10002ac7: 8b 16                        	mov	edx, dword ptr [esi]
10002ac9: 8d 4c 24 14                  	lea	ecx, [esp + 0x14]
10002acd: 51                           	push	ecx
10002ace: 50                           	push	eax
10002acf: 8b ce                        	mov	ecx, esi
10002ad1: ff 52 40                     	call	dword ptr [edx + 0x40]
10002ad4: 8b 56 70                     	mov	edx, dword ptr [esi + 0x70]
10002ad7: 8b f8                        	mov	edi, eax
10002ad9: 8b 44 24 14                  	mov	eax, dword ptr [esp + 0x14]
10002add: 80 7c 02 ff f7               	cmp	byte ptr [edx + eax - 0x1], -0x9
10002ae2: 74 4d                        	je	0x10002b31 <.text+0x1b31>
10002ae4: 85 ff                        	test	edi, edi
10002ae6: 75 49                        	jne	0x10002b31 <.text+0x1b31>
10002ae8: eb c3                        	jmp	0x10002aad <.text+0x1aad>
10002aea: 68 fa 00 00 00               	push	0xfa
10002aef: 55                           	push	ebp
10002af0: ff 15 1c 50 00 10            	call	dword ptr [0x1000501c]
10002af6: ff d3                        	call	ebx
10002af8: 8b 16                        	mov	edx, dword ptr [esi]
10002afa: 8b ce                        	mov	ecx, esi
10002afc: 8b f8                        	mov	edi, eax
10002afe: ff 52 20                     	call	dword ptr [edx + 0x20]
10002b01: 8b c8                        	mov	ecx, eax
10002b03: b8 d3 4d 62 10               	mov	eax, 0x10624dd3
10002b08: f7 e1                        	mul	ecx
10002b0a: 8b ca                        	mov	ecx, edx
10002b0c: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
10002b10: 2b fa                        	sub	edi, edx
10002b12: b8 d3 4d 62 10               	mov	eax, 0x10624dd3
10002b17: f7 ef                        	imul	edi
10002b19: c1 fa 06                     	sar	edx, 0x6
10002b1c: 8b c2                        	mov	eax, edx
10002b1e: c1 e8 1f                     	shr	eax, 0x1f
10002b21: c1 e9 06                     	shr	ecx, 0x6
10002b24: 03 d0                        	add	edx, eax
10002b26: 3b d1                        	cmp	edx, ecx
10002b28: 77 02                        	ja	0x10002b2c <.text+0x1b2c>
10002b2a: eb 81                        	jmp	0x10002aad <.text+0x1aad>
10002b2c: bf 06 00 00 00               	mov	edi, 0x6
10002b31: 55                           	push	ebp
10002b32: ff 15 10 50 00 10            	call	dword ptr [0x10005010]
10002b38: ff d3                        	call	ebx
10002b3a: 8b c7                        	mov	eax, edi
10002b3c: 5f                           	pop	edi
10002b3d: 5e                           	pop	esi
10002b3e: 5d                           	pop	ebp
10002b3f: 5b                           	pop	ebx
10002b40: 83 c4 0c                     	add	esp, 0xc
10002b43: c3                           	ret
10002b44: bf 07 00 00 00               	mov	edi, 0x7
10002b49: ff d3                        	call	ebx
10002b4b: 8b c7                        	mov	eax, edi
10002b4d: 5f                           	pop	edi
10002b4e: 5e                           	pop	esi
10002b4f: 5d                           	pop	ebp
10002b50: 5b                           	pop	ebx
10002b51: 83 c4 0c                     	add	esp, 0xc
10002b54: c3                           	ret
```

## 0x10002b60–0x10002c9a

File start offset: 0x2b60

```asm
10002b60: 83 ec 58                     	sub	esp, 0x58
10002b63: 8b 44 24 5c                  	mov	eax, dword ptr [esp + 0x5c]
10002b67: 55                           	push	ebp
10002b68: 56                           	push	esi
10002b69: 33 ed                        	xor	ebp, ebp
10002b6b: 8b f1                        	mov	esi, ecx
10002b6d: 57                           	push	edi
10002b6e: 89 28                        	mov	dword ptr [eax], ebp
10002b70: b9 14 00 00 00               	mov	ecx, 0x14
10002b75: 33 c0                        	xor	eax, eax
10002b77: 8d 7c 24 14                  	lea	edi, [esp + 0x14]
10002b7b: f3 ab                        	rep		stosd	dword ptr es:[edi], eax
10002b7d: 8a 4e 06                     	mov	cl, byte ptr [esi + 0x6]
10002b80: 8a 56 0c                     	mov	dl, byte ptr [esi + 0xc]
10002b83: 88 4c 24 16                  	mov	byte ptr [esp + 0x16], cl
10002b87: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
10002b8a: f7 d9                        	neg	ecx
10002b8c: 1a c9                        	sbb	cl, cl
10002b8e: 55                           	push	ebp
10002b8f: 55                           	push	ebp
10002b90: 8d 44 24 14                  	lea	eax, [esp + 0x14]
10002b94: 81 e1 80 00 00 00            	and	ecx, 0x80
10002b9a: 55                           	push	ebp
10002b9b: 55                           	push	ebp
10002b9c: c6 44 24 1c 00               	mov	byte ptr [esp + 0x1c], 0x0
10002ba1: c6 44 24 1d 00               	mov	byte ptr [esp + 0x1d], 0x0
10002ba6: c6 44 24 1e 00               	mov	byte ptr [esp + 0x1e], 0x0
10002bab: c6 44 24 24 02               	mov	byte ptr [esp + 0x24], 0x2
10002bb0: c6 44 24 27 48               	mov	byte ptr [esp + 0x27], 0x48
10002bb5: 88 54 24 2c                  	mov	byte ptr [esp + 0x2c], dl
10002bb9: c7 44 24 30 03 00 00 00      	mov	dword ptr [esp + 0x30], 0x3
10002bc1: 89 44 24 34                  	mov	dword ptr [esp + 0x34], eax
10002bc5: c6 44 24 38 0e               	mov	byte ptr [esp + 0x38], 0xe
10002bca: c6 44 24 39 06               	mov	byte ptr [esp + 0x39], 0x6
10002bcf: c6 44 24 54 0d               	mov	byte ptr [esp + 0x54], 0xd
10002bd4: 88 4c 24 59                  	mov	byte ptr [esp + 0x59], cl
10002bd8: ff 15 34 50 00 10            	call	dword ptr [0x10005034]
10002bde: 8b f8                        	mov	edi, eax
10002be0: 85 ff                        	test	edi, edi
10002be2: 0f 84 a7 00 00 00            	je	0x10002c8f <.text+0x1c8f>
10002be8: 8d 54 24 14                  	lea	edx, [esp + 0x14]
10002bec: 89 7c 24 2c                  	mov	dword ptr [esp + 0x2c], edi
10002bf0: 52                           	push	edx
10002bf1: e8 50 14 00 00               	call	0x10004046 <DllRegisterServer+0x156>
10002bf6: 8a 44 24 19                  	mov	al, byte ptr [esp + 0x19]
10002bfa: 83 c4 04                     	add	esp, 0x4
10002bfd: 84 c0                        	test	al, al
10002bff: 75 11                        	jne	0x10002c12 <.text+0x1c12>
10002c01: 8b 06                        	mov	eax, dword ptr [esi]
10002c03: 8b ce                        	mov	ecx, esi
10002c05: ff 50 20                     	call	dword ptr [eax + 0x20]
10002c08: 50                           	push	eax
10002c09: 57                           	push	edi
10002c0a: ff 15 1c 50 00 10            	call	dword ptr [0x1000501c]
10002c10: eb 04                        	jmp	0x10002c16 <.text+0x1c16>
10002c12: 8b 44 24 68                  	mov	eax, dword ptr [esp + 0x68]
10002c16: 3d 02 01 00 00               	cmp	eax, 0x102
10002c1b: 74 0c                        	je	0x10002c29 <.text+0x1c29>
10002c1d: 83 f8 ff                     	cmp	eax, -0x1
10002c20: 75 0c                        	jne	0x10002c2e <.text+0x1c2e>
10002c22: bd 03 00 00 00               	mov	ebp, 0x3
10002c27: eb 05                        	jmp	0x10002c2e <.text+0x1c2e>
10002c29: bd 02 00 00 00               	mov	ebp, 0x2
10002c2e: 8a 44 24 2a                  	mov	al, byte ptr [esp + 0x2a]
10002c32: 84 c0                        	test	al, al
10002c34: 74 09                        	je	0x10002c3f <.text+0x1c3f>
10002c36: 3c 13                        	cmp	al, 0x13
10002c38: 74 05                        	je	0x10002c3f <.text+0x1c3f>
10002c3a: bd 04 00 00 00               	mov	ebp, 0x4
10002c3f: 8a 44 24 2b                  	mov	al, byte ptr [esp + 0x2b]
10002c43: 84 c0                        	test	al, al
10002c45: 74 05                        	je	0x10002c4c <.text+0x1c4c>
10002c47: bd 05 00 00 00               	mov	ebp, 0x5
10002c4c: 57                           	push	edi
10002c4d: ff 15 10 50 00 10            	call	dword ptr [0x10005010]
10002c53: 85 ed                        	test	ebp, ebp
10002c55: 75 2d                        	jne	0x10002c84 <.text+0x1c84>
10002c57: 8b 4c 24 0c                  	mov	ecx, dword ptr [esp + 0xc]
10002c5b: 8b 54 24 0d                  	mov	edx, dword ptr [esp + 0xd]
10002c5f: 8b 44 24 0e                  	mov	eax, dword ptr [esp + 0xe]
10002c63: 81 e1 ff 00 00 00            	and	ecx, 0xff
10002c69: c1 e1 08                     	shl	ecx, 0x8
10002c6c: 81 e2 ff 00 00 00            	and	edx, 0xff
10002c72: 25 ff 00 00 00               	and	eax, 0xff
10002c77: 03 ca                        	add	ecx, edx
10002c79: 8b 54 24 68                  	mov	edx, dword ptr [esp + 0x68]
10002c7d: c1 e1 08                     	shl	ecx, 0x8
10002c80: 03 c8                        	add	ecx, eax
10002c82: 89 0a                        	mov	dword ptr [edx], ecx
10002c84: 5f                           	pop	edi
10002c85: 8b c5                        	mov	eax, ebp
10002c87: 5e                           	pop	esi
10002c88: 5d                           	pop	ebp
10002c89: 83 c4 58                     	add	esp, 0x58
10002c8c: c2 04 00                     	ret	0x4
10002c8f: 5f                           	pop	edi
10002c90: 5e                           	pop	esi
10002c91: b8 01 00 00 00               	mov	eax, 0x1
10002c96: 5d                           	pop	ebp
10002c97: 83 c4 58                     	add	esp, 0x58
10002c9a: c2 04 00                     	ret	0x4
```

## 0x10002ca0–0x10002dd2

File start offset: 0x2ca0

```asm
10002ca0: 8b 44 24 08                  	mov	eax, dword ptr [esp + 0x8]
10002ca4: 83 ec 50                     	sub	esp, 0x50
10002ca7: 8b 10                        	mov	edx, dword ptr [eax]
10002ca9: 53                           	push	ebx
10002caa: 8b 5c 24 58                  	mov	ebx, dword ptr [esp + 0x58]
10002cae: 55                           	push	ebp
10002caf: 56                           	push	esi
10002cb0: 8b f1                        	mov	esi, ecx
10002cb2: 8d 0c 1a                     	lea	ecx, [edx + ebx]
10002cb5: 33 ed                        	xor	ebp, ebp
10002cb7: 81 f9 00 80 00 00            	cmp	ecx, 0x8000
10002cbd: 76 0e                        	jbe	0x10002ccd <.text+0x1ccd>
10002cbf: 5e                           	pop	esi
10002cc0: 5d                           	pop	ebp
10002cc1: b8 08 00 00 00               	mov	eax, 0x8
10002cc6: 5b                           	pop	ebx
10002cc7: 83 c4 50                     	add	esp, 0x50
10002cca: c2 08 00                     	ret	0x8
10002ccd: 57                           	push	edi
10002cce: b9 14 00 00 00               	mov	ecx, 0x14
10002cd3: 33 c0                        	xor	eax, eax
10002cd5: 8d 7c 24 10                  	lea	edi, [esp + 0x10]
10002cd9: f3 ab                        	rep		stosd	dword ptr es:[edi], eax
10002cdb: 8a 46 06                     	mov	al, byte ptr [esi + 0x6]
10002cde: 8a 4e 0c                     	mov	cl, byte ptr [esi + 0xc]
10002ce1: 88 44 24 12                  	mov	byte ptr [esp + 0x12], al
10002ce5: 8b 46 70                     	mov	eax, dword ptr [esi + 0x70]
10002ce8: 03 c2                        	add	eax, edx
10002cea: 88 4c 24 18                  	mov	byte ptr [esp + 0x18], cl
10002cee: 89 44 24 20                  	mov	dword ptr [esp + 0x20], eax
10002cf2: b0 0e                        	mov	al, 0xe
10002cf4: 88 44 24 24                  	mov	byte ptr [esp + 0x24], al
10002cf8: 88 44 24 40                  	mov	byte ptr [esp + 0x40], al
10002cfc: 8b 46 6c                     	mov	eax, dword ptr [esi + 0x6c]
10002cff: 8b cb                        	mov	ecx, ebx
10002d01: 8b d3                        	mov	edx, ebx
10002d03: 6a 00                        	push	0x0
10002d05: c1 e9 10                     	shr	ecx, 0x10
10002d08: c1 ea 08                     	shr	edx, 0x8
10002d0b: f7 d8                        	neg	eax
10002d0d: 1a c0                        	sbb	al, al
10002d0f: 6a 00                        	push	0x0
10002d11: 25 80 00 00 00               	and	eax, 0x80
10002d16: 6a 00                        	push	0x0
10002d18: 6a 00                        	push	0x0
10002d1a: c6 44 24 20 02               	mov	byte ptr [esp + 0x20], 0x2
10002d1f: c6 44 24 23 48               	mov	byte ptr [esp + 0x23], 0x48
10002d24: 89 5c 24 2c                  	mov	dword ptr [esp + 0x2c], ebx
10002d28: c6 44 24 35 06               	mov	byte ptr [esp + 0x35], 0x6
10002d2d: 88 4c 24 52                  	mov	byte ptr [esp + 0x52], cl
10002d31: 88 54 24 53                  	mov	byte ptr [esp + 0x53], dl
10002d35: 88 5c 24 54                  	mov	byte ptr [esp + 0x54], bl
10002d39: 88 44 24 55                  	mov	byte ptr [esp + 0x55], al
10002d3d: ff 15 34 50 00 10            	call	dword ptr [0x10005034]
10002d43: 8b f8                        	mov	edi, eax
10002d45: 85 ff                        	test	edi, edi
10002d47: 74 7b                        	je	0x10002dc4 <.text+0x1dc4>
10002d49: 8d 4c 24 10                  	lea	ecx, [esp + 0x10]
10002d4d: 89 7c 24 28                  	mov	dword ptr [esp + 0x28], edi
10002d51: 51                           	push	ecx
10002d52: e8 ef 12 00 00               	call	0x10004046 <DllRegisterServer+0x156>
10002d57: 8a 44 24 15                  	mov	al, byte ptr [esp + 0x15]
10002d5b: 83 c4 04                     	add	esp, 0x4
10002d5e: 84 c0                        	test	al, al
10002d60: 75 27                        	jne	0x10002d89 <.text+0x1d89>
10002d62: 8b 16                        	mov	edx, dword ptr [esi]
10002d64: 8b ce                        	mov	ecx, esi
10002d66: ff 52 20                     	call	dword ptr [edx + 0x20]
10002d69: 50                           	push	eax
10002d6a: 57                           	push	edi
10002d6b: ff 15 1c 50 00 10            	call	dword ptr [0x1000501c]
10002d71: 3d 02 01 00 00               	cmp	eax, 0x102
10002d76: 74 0c                        	je	0x10002d84 <.text+0x1d84>
10002d78: 83 f8 ff                     	cmp	eax, -0x1
10002d7b: 75 0c                        	jne	0x10002d89 <.text+0x1d89>
10002d7d: bd 03 00 00 00               	mov	ebp, 0x3
10002d82: eb 05                        	jmp	0x10002d89 <.text+0x1d89>
10002d84: bd 02 00 00 00               	mov	ebp, 0x2
10002d89: 8a 44 24 26                  	mov	al, byte ptr [esp + 0x26]
10002d8d: 84 c0                        	test	al, al
10002d8f: 74 05                        	je	0x10002d96 <.text+0x1d96>
10002d91: bd 04 00 00 00               	mov	ebp, 0x4
10002d96: 8a 44 24 27                  	mov	al, byte ptr [esp + 0x27]
10002d9a: 84 c0                        	test	al, al
10002d9c: 74 05                        	je	0x10002da3 <.text+0x1da3>
10002d9e: bd 05 00 00 00               	mov	ebp, 0x5
10002da3: 57                           	push	edi
10002da4: ff 15 10 50 00 10            	call	dword ptr [0x10005010]
10002daa: 85 ed                        	test	ebp, ebp
10002dac: 75 1b                        	jne	0x10002dc9 <.text+0x1dc9>
10002dae: 8b 44 24 68                  	mov	eax, dword ptr [esp + 0x68]
10002db2: 5f                           	pop	edi
10002db3: 5e                           	pop	esi
10002db4: 8b 08                        	mov	ecx, dword ptr [eax]
10002db6: 03 cb                        	add	ecx, ebx
10002db8: 89 08                        	mov	dword ptr [eax], ecx
10002dba: 8b c5                        	mov	eax, ebp
10002dbc: 5d                           	pop	ebp
10002dbd: 5b                           	pop	ebx
10002dbe: 83 c4 50                     	add	esp, 0x50
10002dc1: c2 08 00                     	ret	0x8
10002dc4: bd 01 00 00 00               	mov	ebp, 0x1
10002dc9: 5f                           	pop	edi
10002dca: 8b c5                        	mov	eax, ebp
10002dcc: 5e                           	pop	esi
10002dcd: 5d                           	pop	ebp
10002dce: 5b                           	pop	ebx
10002dcf: 83 c4 50                     	add	esp, 0x50
10002dd2: c2 08 00                     	ret	0x8
```

## 0x10003390–0x100033b1

File start offset: 0x3390

```asm
10003390: 33 c0                        	xor	eax, eax
10003392: c6 41 34 09                  	mov	byte ptr [ecx + 0x34], 0x9
10003396: 89 41 10                     	mov	dword ptr [ecx + 0x10], eax
10003399: 89 41 14                     	mov	dword ptr [ecx + 0x14], eax
1000339c: 88 41 07                     	mov	byte ptr [ecx + 0x7], al
1000339f: 88 41 35                     	mov	byte ptr [ecx + 0x35], al
100033a2: 88 41 36                     	mov	byte ptr [ecx + 0x36], al
100033a5: 88 41 37                     	mov	byte ptr [ecx + 0x37], al
100033a8: 88 41 38                     	mov	byte ptr [ecx + 0x38], al
100033ab: 88 41 39                     	mov	byte ptr [ecx + 0x39], al
100033ae: 89 41 6c                     	mov	dword ptr [ecx + 0x6c], eax
100033b1: e9 2a 02 00 00               	jmp	0x100035e0 <.text+0x25e0>
```

## 0x100035e0–0x1000366a

File start offset: 0x35e0

```asm
100035e0: 53                           	push	ebx
100035e1: 56                           	push	esi
100035e2: 8b f1                        	mov	esi, ecx
100035e4: 33 db                        	xor	ebx, ebx
100035e6: 57                           	push	edi
100035e7: 53                           	push	ebx
100035e8: 8a 4e 07                     	mov	cl, byte ptr [esi + 0x7]
100035eb: 53                           	push	ebx
100035ec: 80 c9 40                     	or	cl, 0x40
100035ef: 53                           	push	ebx
100035f0: 53                           	push	ebx
100035f1: 88 4e 07                     	mov	byte ptr [esi + 0x7], cl
100035f4: ff 15 34 50 00 10            	call	dword ptr [0x10005034]
100035fa: 8b f8                        	mov	edi, eax
100035fc: 85 ff                        	test	edi, edi
100035fe: 74 62                        	je	0x10003662 <.text+0x2662>
10003600: 8d 46 04                     	lea	eax, [esi + 0x4]
10003603: 89 7e 1c                     	mov	dword ptr [esi + 0x1c], edi
10003606: 50                           	push	eax
10003607: e8 3a 0a 00 00               	call	0x10004046 <DllRegisterServer+0x156>
1000360c: 8a 46 05                     	mov	al, byte ptr [esi + 0x5]
1000360f: 83 c4 04                     	add	esp, 0x4
10003612: 84 c0                        	test	al, al
10003614: 75 27                        	jne	0x1000363d <.text+0x263d>
10003616: 8b 16                        	mov	edx, dword ptr [esi]
10003618: 8b ce                        	mov	ecx, esi
1000361a: ff 52 20                     	call	dword ptr [edx + 0x20]
1000361d: 50                           	push	eax
1000361e: 57                           	push	edi
1000361f: ff 15 1c 50 00 10            	call	dword ptr [0x1000501c]
10003625: 3d 02 01 00 00               	cmp	eax, 0x102
1000362a: 74 0c                        	je	0x10003638 <.text+0x2638>
1000362c: 83 f8 ff                     	cmp	eax, -0x1
1000362f: 75 0c                        	jne	0x1000363d <.text+0x263d>
10003631: bb 03 00 00 00               	mov	ebx, 0x3
10003636: eb 05                        	jmp	0x1000363d <.text+0x263d>
10003638: bb 02 00 00 00               	mov	ebx, 0x2
1000363d: 8a 46 1a                     	mov	al, byte ptr [esi + 0x1a]
10003640: 84 c0                        	test	al, al
10003642: 74 05                        	je	0x10003649 <.text+0x2649>
10003644: bb 04 00 00 00               	mov	ebx, 0x4
10003649: 8a 46 1b                     	mov	al, byte ptr [esi + 0x1b]
1000364c: 84 c0                        	test	al, al
1000364e: 74 05                        	je	0x10003655 <.text+0x2655>
10003650: bb 05 00 00 00               	mov	ebx, 0x5
10003655: 57                           	push	edi
10003656: ff 15 10 50 00 10            	call	dword ptr [0x10005010]
1000365c: 5f                           	pop	edi
1000365d: 8b c3                        	mov	eax, ebx
1000365f: 5e                           	pop	esi
10003660: 5b                           	pop	ebx
10003661: c3                           	ret
10003662: 5f                           	pop	edi
10003663: 5e                           	pop	esi
10003664: b8 01 00 00 00               	mov	eax, 0x1
10003669: 5b                           	pop	ebx
1000366a: c3                           	ret
```
