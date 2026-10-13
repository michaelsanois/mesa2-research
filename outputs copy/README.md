# SEND PROGRAM TO S2000 research package

13 October 2026. Offline investigation; Bridge unchanged; no hardware transfers.

## Plain-English findings

MESA sends the program and each keygroup as separate 192-byte headers. Header bytes are split into low/high nibbles inside Akai SysEx messages carried by SCSI SEND. For program creation it sends identifier128, waits for an Akai OK response, then sends keygroups to identifier255, which the inherited documentation defines as the last-created program. Sample references in the keygroups are 12-character encoded names, not host pointers or disk addresses.

The examined sample-import routine switches to bulk mode, sends a sample header, consumes a readiness response, then sends raw PCM in blocks. Its mono source-read blocks are at most32768 bytes. The prior original MESA probe transmitted512 bytes identical to the mono16-bit little-endian WAV PCM. It did not nibble-encode or byte-swap those PCM bytes.

Lakai uses an explicit ASPACK command before raw PCM. MESA’s examined header-creation routine does not: the header primes the transfer. Those are distinct paths; the specification does not insert Lakai's sequence into MESA's.

The earlier captures show the same13-byte post-object function after sample import and after program/keygroup creation. Its bytes and expected OK response are established, but its exact S2000 effect is not. It must not be called a verified commit or linking command.

**Original captures are now recovered and reconciled. There is sufficient evidence to begin the offline uploader and captured golden-vector tests.** See [capture reconciliation](05-capture-reconciliation.md) for exact ordering, complete headers, Bridge defaults and remaining limits.

The recovered code and captures are sufficient to specify packet building and a guarded upload state machine locally. It is not sufficient to claim a reliable physical uploader: actual firmware allocation, complete readiness/mode ordering, large-transfer byte accounting, valid header defaults, final residency verification and uncertain-write recovery still need evidence. No complete sample-linked physical program upload was demonstrated by the retained research.

## Deliverables

- [Technical report](01-protocol-report.md): evidence grades, identities, exact addresses, commands, structures and limitations.
- [End-to-end sequence](02-upload-sequence.md): recovered routine pseudocode plus explicitly proposed Bridge ordering and verification.
- [Bridge implementation contract](03-bridge-specification.md): packet codecs, backend requirements, states, errors and acceptance criteria.
- [Unresolved questions](04-unresolved-questions.md): focused evidence requirements and existing guest captures to retrieve first.
- [Golden codec vectors](golden-vectors.json):23 offline vectors and seven block-boundary schedules; synthetic header patterns, not hardware-valid defaults.
- [Documentary header field map](documentary-header-fields.csv):241 source fields with model-applicability caveats; not a write allowlist.
- [Evidence register](evidence/source-register.json), [SCSIPlug excerpts](evidence/SCSIPlug-excerpts.md), [MESASAMPLER excerpts](evidence/MESASAMPLER-excerpts.md), [static tables/templates](evidence/static-data.json), and preserved historical reports.

## Capture-to-code correlation

| Finding | Existing capture/report | Shipped-code corroboration or remaining boundary |
|---|---|---|
| SDATA precedes PCM | H02 UPLOAD2 seq63 then66 | A03 `10001240`, `1000141C`, `10001490`; no ASPACK construction in this bounded routine |
| Raw PCM16LE probe | H02 guest FC/B,512 bytes | A03 copies mono file bytes into raw SEND; other file conversions not proved |
| Mono32768-byte chunk | Prior512 capture cannot prove large chunks | A03 `10001420` compare/limit; STATIC only |
| Header response / special WAIT branches | H02 synthetic header reply allowed seq66 to follow | A03 `100012AF–1000136B`; full readiness capture not retrieved |
| PDATA128 then KDATA255/group0 | H02 PROGRAM_LAB seq58/63, KG_LAB seq58/63 | A04 `10007494`, `10007573`; D01 last-created-program definition |
| Several keygroups sent one after another | Historical capture only group0 | A04 copy path `1000A220`, `1000A2B0`, `1000A440`; STATIC only |
| Group writes require operation16/status0 | H02 synthetic ACKs advanced client | A04 `10007740`, `1000A466`; physical replies unverified |
| Common post-object function1 | H02 UPLOAD2 seq69, KG_LAB seq68 | Earlier H03 callback audit, A04 `10006480`/`10006570`; semantic name unresolved |
| Later list/header readback | H02 FINAL_LAB seq81/84/114 and READBACK_LAB | Fixture population is synthetic; seq103 requested program0, not proof of uploaded program selection |
| Final normal MODE | H02 FINAL_LAB seq116 | A03 successful sample cleanup `10003390`; full outer interleaving remains a trace question |
| Device type3 discovery | H02 corrected synthetic target; H04 imports | Prior A03 addresses `100038D1`/`10001B10` reused; physical endpoint unchanged/unprobed |

No completed loader/startup/effects/import experiment was rerun. Missing MESASAMPLER bytes were restored from the original MSI and matched the previously recorded hash. Work used local parsing/disassembly; REA's native engine was not configured. No new model agents, network research or target execution were used.

## Package checks

Artifact hashes and ISO→MSI byte identity were checked. Excerpt address/file mappings and the relevant virtual dispatch entries were retained. Golden packets were checked against fixed CDB examples,14-bit identifiers, exact envelope lengths and decoded payloads; block schedules total the exact even PCM size. The documentary fields all fit within192 bytes. These checks validate the package's offline encoding/evidence consistency, not S2000 acceptance.

## Recovered capture additions

- [Reconciliation report](05-capture-reconciliation.md)
- [Exact command ordering](upload-order.csv) and [complete transaction records](upload-transactions.json)
- [Captured golden vectors](captured-golden-vectors.json) and [complete header examples](captured-header-examples.json)
- [Bridge byte differences](bridge-default-differences.csv)
- [Raw recovery manifest](recovered-captures/recovery-manifest.json) and [trace integrity results](capture-integrity.json)

The read-only recovery checks1208 trace records and899 recovered files; every referenced payload exists at its recorded size. All three PCM writes match PROBE.WAV exactly. No additional MESA experiment was performed.
