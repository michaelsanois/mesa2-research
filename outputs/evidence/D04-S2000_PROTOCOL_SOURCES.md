# Protocol source and evidence log
Research-only audit, 7 September 2026. No hardware exchange was performed.

## Source register

| ID | Title / origin / version | Location and sections used | Evidence and limitations |
|---|---|---|---|
| P1 | Akai, S2000/S3000XL/S3200XL MIDI System Exclusive Extensions; copyright 2000, revision unspecified | [Preserved PDF](https://thismodernday.com/wp-content/uploads/2021/07/MIDI-System-Exclusive-Extensions.pdf), PDF pp1–4; opening inheritance, Multi Mode, 41/42, named Multi fields | Preserved official document; directly names S2000. Partial reuse statement, not universal S3000 compatibility. |
| P1T | Same document, Frank Neumann transcription, 26 January 2002 | [HTML](https://lakai.sourceforge.net/docs/s2000_sysex.html); matching sections | Cached copy inspected. PDF is preferred when typography differs. |
| P2 | Akai S2800/S3000/S3200 MIDI System Exclusive Extensions; Neumann transcription, 5 February 2002; Akai revision unspecified | [HTML](https://lakai.sourceforge.net/docs/s2800_sysex.html); message header, program/keygroup/sample byte access and field tables; explicitly labelled S2000-family subsections | Preserved official content, not authenticated scan. Transcriber warns of errors. Ancestor-only fields require a separate S2000 applicability decision. Every map row gives section, exact field and cached line. |
| P3 | Akai S1000 MIDI Exclusive Communication; Neumann transcription, 25 January 2002; Akai revision unspecified | [HTML](https://lakai.sourceforge.net/docs/s1000_sysex.html); exclusive message table, RPLIST/PLIST, RPDATA/PDATA, RKDATA/KDATA, REPLY, name alphabet, assembler structures | Preserved official content. Used for explicitly referenced older commands and encoding, not S1000 capacities or obsolete fields. |
| P4 | Akai S2000 Operator's Manual v1.30 | [PDF](https://www.polynominal.com/akai-s2000/akai-s2000-manual.pdf); printed pp67–72 architecture/APM, 77–80 output, 86–94 ranges/zones, 96–103 envelopes/filter, 105–119 optional filter/LFO, 141 sample pitch, 211 SysEx, 221–222 specifications/MIDI | Official manual, third-party mirror. Establishes feature semantics, not byte offsets. Printed page N is PDF page N+7 (one-based) in this 233-page copy. |
| H1 | Michael's four S2000 cutoff captures; OS/date of hardware experiment not independently established | [Preserved files and hashes](evidence/filter-cutoff/README.md); each JSONL contains a complete 15-byte event | Real hardware capture as reported by user. A applies to emitted observations 51,52,64,63 only. Not proof of inbound acceptance, identity or full header. |
| L1 | Frank Neumann, Lakai 0.1 source, Debian orig archive; secondary | Local work/protocol-verification/lakai-0.1.orig/lakai.c: lakai_get_program_list, lakai_get_program, lakai_get_keygroup; lakai.h constants; [archive index](https://lakai.sourceforge.net/documentation.shtml.html) | Cross-checks 02/03, 06/07, 08/09, low-first values and nibble unpacking. Calls sendrecv_scsimidi: not proof of the direct DIN/CoreMIDI path. Buffer sizes and timeout choices are not hardware limits. |
| I1 | Existing Bridge implementation / tests, 6–7 September 2026 | src/S2000/S2000ParameterControl.*, src/S2000ParameterAutomation.h, tests/S2000ParameterTests.cpp, docs/PARAMETER_CONTROL_REPORT.md | Implementation evidence only; fourteen mappings and synthetic tests are not fourteen physical validations. |

## Retrieval and integrity

The archive index was accessible during this audit and identifies the pages as retyped Akai printouts after the original vendor pages disappeared. Direct HTML fetches timed out; previously cached copies were inspected instead. P1 and P4 PDF text was accessible through the web reader; screenshot requests failed with cache-miss errors. No unrelated sampler manual was substituted. Source page numbering comes from extracted page markers, not a fresh visual pagination inspection.

Existing local SHA-256:
- P1 PDF: a08ea5683b4ad19b5a3cad6d56ef008f1f6a35ffa97841d0fb19e8d21b20df41
- P1T: f3386c35ddcc483fc12611a31604d62a59c4e34f616300b6a166a433139e9014
- P2: 7a118bba06477ec0fe3ed6c8d38b969f08bbb94ad9eaad2ecd5d086d93b26fe2
- P3: 2f89292f3bda5cff46c9227d5a49210966b79924dc5cc55f7b3af14b80cbf227
- Lakai archive: 6bd5f3e4a8fae7eeb67dc24569022ea6adcb479e771063612f712bae29c213dc

## Inheritance chain and grade discipline

P1 p1 references S3000 reuse; its p4 footer links the S1000/S1100 and S2800/S3000/S3200 references. P2 explicitly recommends S1000 RPLIST for program-list indexing and RSLIST for sample indexing. These are meaningful inheritance links. However, P1 says only that much of the older system applies, and P2 expressly changes older fields. Neither statement proves every ancestor byte on every S2000 OS.

The pre-existing fourteen-field implementation retains its narrow C documentary basis (with A for observed cutoff emission). New ancestor fields are retained as E applicability candidates rather than automatically promoted. Explicit S2000-family fields in P2 and P1 are B within their stated ownership. D is reserved for code-only evidence; no code-only field has been promoted.

These A–E definitions are the current user's research grades. In the older S2000_PROTOCOL.md, C meant inherited protocol physically verified on S2000. They are different taxonomies; this audit does not silently relabel the historical ledger.
