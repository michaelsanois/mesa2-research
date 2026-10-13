# Stage 4 — PiSCSI V2.3B compatibility assessment

10 October 2026. Read-only engineering assessment; web research and existing local evidence inspection only. No Pi connection, deployment, service operation, GPIO/SCSI/MIDI command or sampler interaction.

## Decision: CONDITIONAL GO

The hardware family provides a credible, explicitly supported basis for preparing a first controlled INQUIRY. No demonstrated AmigaKit V2.3B initiator incompatibility was found. Missing supplier schematics are neither proof of incompatibility nor an automatic prerequisite. An exhaustive PCB audit, hardware certification exercise or new electrical isolation board is not justified before one carefully bounded read-only experiment.

Three conditions must be settled in the validation plan before execution: basic actual-board/profile identification, exact isolated runtime/ownership admission, and an operational failure-containment/recovery policy. Preparation may proceed now. This decision does **not** authorise installation, activation, Pi access or the command itself.

## 1. Published hardware facts

Upstream lists akuker revision 2.3 as FULLSPEC, supporting initiator or target operation, tested working, with no known issues in that table. This is a family capability statement, not certification of this individual board/helper. [Official hardware matrix](https://github.com/PiSCSI/piscsi/wiki/Hardware-Versions).

The official device documentation explicitly describes FULLSPEC initiator support and identifies scsidump as an initiator tool. Initiator use is therefore an intended upstream application, not an invented electrical mode. [Official supported-device documentation](https://github.com/piscsi/piscsi/wiki/Supported-Device-Types).

AmigaKit identifies its product as PiSCSI/RaSCSI Adapter Board V2.3 B and points users to upstream documentation. The reviewed listing describes emulation, but supplies no revision-specific electrical equivalence statement or documented initiator-specific change. This review found no published V2.3B direction/enable incompatibility; that limited search result cannot prove absence of differences. [Manufacturer listing](https://amigakit.amiga.store/piscsi-rascsi-adapter-board-p-91280.html).

### GPIO and circuit reference

The retained PiSCSI 24.04.01 FULLSPEC definition is pinned to commit e540da06c428584f77c95082a93deb629db3d88d. The following are **BCM numbers**, not connector positions. [Versioned definition](https://github.com/PiSCSI/piscsi/blob/e540da06c428584f77c95082a93deb629db3d88d/cpp/hal/connection_fullspec.h).

| Function | BCM GPIO | Meaning in upstream 2.3 |
| --- | --- | --- |
| ACT | 4 | Activity indication |
| Legacy ENB | 5 | Debug LED; not transceiver isolation |
| IND | 6 | Initiator-control transceiver DIR |
| TAD | 7 | Target-control transceiver DIR |
| DTD | 8 | Data/parity transceiver DIR |
| D0–D7 | 10–17 | Eight data signals |
| Parity | 18 | Data parity |
| ATN / RST / ACK | 19 / 20 / 21 | Initiator control signals |
| REQ / MSG / C/D / I/O | 22 / 23 / 24 / 25 | Target phase/handshake signals |
| BSY / SEL | 26 / 27 | Arbitration/selection |

Authenticated upstream schematic/netlist evidence maps GPIO6/7/8 to IC4/IC3/IC1+IC2 DIR respectively. All four transceiver enable inputs are grounded; software GPIO5 cannot disable them. Signal lines have separate 10k Pi-side pull-ups to 3.3V; these are not cable termination. [Upstream revision-2.3 hardware files](https://github.com/PiSCSI/piscsi-hw/tree/main/rascsi_2p3); local exact net trace: [NET-TRACE.json](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-board-cleanup-audit-20261010/NET-TRACE.json).

The reference SN74LS641 family is non-inverting, open-collector and direction controlled. Its enable can isolate the two sides, but the upstream board ties enable active. A released/high input does not sink its corresponding open-collector output. [TI device documentation](https://www.ti.com/product/SN74LS641), [datasheet](https://www.ti.com/lit/ds/symlink/sn74ls641.pdf). The PDF web fetch failed in this run; its retained local scanned function-table review is documented in [board audit](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-board-cleanup-audit-20261010/REPORT.md), with the retained PDF. No unseen online table is claimed newly verified.

### Normal operation versus interruption

For the upstream circuit, GPIO6 high selects outward initiator controls; GPIO7 is normally inward and changes for arbitration; GPIO8 low sends data outward and high receives. The helper follows those orientations. During normal cleanup it releases signals, returns signal/control pins to inputs and checks register state. With working upstream signal pull-ups, the steady-state circuit model predicts no SCSI sinking when signal inputs float high, regardless of a transceiver being inward or outward. This is a reasonable engineering inference, not a measurement on the AmigaKit board. Normal cleanup need not globally disable transceivers to work.

A concrete failure counterexample exists: a helper killed while a GPIO is an asserted low output can leave its function/latch unchanged; an enabled outward transceiver can continue sinking that line. Closing mappings or an empty process cgroup does not reset GPIO registers. This is a possible runtime failure with a source/circuit-supported mechanism, not a reproduced electrical fault on this individual board. It chiefly threatens bus availability and restart correctness. Open-collector SCSI behavior does not by itself demonstrate destructive contention; different parts/wiring, wrong power or direction could introduce separate risks, but none is demonstrated here.

## 2. Known versus assumed AmigaKit compatibility

**Known from user reports:** Pi 3, named V2.3B adapter, working disk emulation and successful S2000 disk loads. These support functioning power, termination and target communication. They were not re-tested today and do not independently exercise every initiator-only route.

**Reasonable working assumption:** this named full-size RaSCSI-family product uses the upstream FULLSPEC interface sufficiently closely for its existing PiSCSI operation. Combining the manufacturer designation, official initiator support and working target behavior makes a controlled test reasonable. Exact electrical equivalence is not asserted.

**Still unconfirmed:** actual transceiver markings, unadvertised board modifications and behavior after abrupt helper failure. A photograph/component check and confirmation of the active FULLSPEC profile are proportionate; tracing every PCB net is unnecessary unless they expose a mismatch. Supplier documents are useful if available, but the user reports they are unavailable and this assessment does not require another supplier request.

## 3. Existing architecture and evidence

The corrected frozen controller candidate SHA256 is 5ae21d6cd15222aa43feb4b5a87d72a7e4eaa32724ba9aa6e8c7bcdeced36111. Its [independent acceptance](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-recovery-evidence-review-20261010/ACCEPTANCE-REPORT.md) records six independent methods and 34 regressions passing; 13 reference tests pass and three platform-specific cases skip. Native terminology tests and source preservation are historical evidence, not electrical tests.

| Boundary | Assessment / concrete limitation |
| --- | --- |
| Exclusive bus ownership | Existing transaction lock, target-stop verification, private durable journal and helper identity checks address overlapping owners. Advisory locking cannot stop an arbitrary privileged process; administrative abstention and management exclusion remain necessary. |
| Competing management | Controller fence/broker/local exclusion design addresses remote and ordinary local management; effective runtime bindings must match the reviewed release. Mac fixtures alone do not prove live enforcement. |
| GPIO directions | Helper routing matches retained FULLSPEC and upstream orientation. No enable-pin rewrite is warranted. |
| Command execution | single_inquiry.cpp fixes one 36-byte INQUIRY (12 00 00 00 24 00), validates distinct IDs and request token, disables automatic REQUEST SENSE and timeout reset. No MODE, TUR or PCM path is needed. |
| Completion | Exact successful helper status, empty cgroup, strict ACK, fresh private exact-size output and AKAI/S2000 identity are checked. HTTP success or process exit alone is insufficient. |
| Timeout / crash | Supervisor termination prevents continued execution where ownership is provable; missing ACK/failed completion retains uncertainty. It cannot electrically release a latched GPIO. |
| Recovery | Latest recover() rejects incomplete verified records, is repeatable, keeps pending evidence and always retains electrical-release uncertainty; it does not restart target mode. |
| Normal target restoration | InquiryLinux still marks normal validated completion as gpio_release_unknown=False and normal controller cleanup can restore target. This is an engineering release policy based on successful register cleanup, not an independently measured release. Recovery correction does not silently change that policy. The validation plan must explicitly choose/approve this normal-completion policy and keep failure restoration blocked. |

Direct local source references:
- [GPIO initialization/cleanup](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-gpio-hardening-20261010/helper-source/src/gpio_bus_rpi.cpp:175).
- [Fixed helper](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-gpio-hardening-20261010/helper-source/src/single_inquiry.cpp:9).
- [No autosense/timeout reset binding](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-gpio-hardening-20261010/helper-source/src/transport_gpio.cpp:76).
- [Actual Inquiry boundary](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-recovery-evidence-candidate-20261010/controller-reference/release/candidate/inquiry_linux.py:224).
- [Target restoration guard](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-recovery-evidence-candidate-20261010/controller-reference/release/candidate/controller_linux.py:126).
- [Conservative recovery](${LOCAL_HOME}/Documents/Codex/bridge-scsi/stage4-recovery-evidence-candidate-20261010/controller-reference/release/inquiry_recovery.py:8).

The GPIO timeout is progress based, so the independent bounded supervisor remains important. Unsupported message/disconnect behavior must abort; INQUIRY success would not establish suitability for long sample transfers.

## 4. Minimum proportionate conditions

| Requirement | Specific risk / classification | Existing mitigation | Simplest resolution | When |
| --- | --- | --- | --- | --- |
| Confirm board label, component family and FULLSPEC binding | Wrong profile or materially different transceiver orientation; possible, not demonstrated | Manufacturer identity, working emulation and upstream map | Use existing photos/markings where available; record parts and profile during a separately authorised preflight. Investigate only any actual discrepancy. No exhaustive tracing. | Before first Inquiry |
| Verify exact isolated runtime and ownership admission | Stale helper/controller hash, conflicting target/management owner; established software hazard | Reviewed lock, shutdown/fence/journal/supervision tests | Bind the accepted sources/binary and explicit dispatch; use existing preflight plus missing harmless Linux checks. Do not repeat already satisfied suites without a change. Effective installation remains separately authorised. | Before first Inquiry |
| Define failed-operation containment and return-to-service policy | SIGKILL can leave asserted lines; supported concrete mechanism | No target restart with uncertain cleanup; pending evidence and isolated helper | Keep target stopped/fenced on failure, preserve evidence, stop the experiment and arrange operator-assisted recovery. Identify all power sources/backfeed before approving a recovery method; no invented GPIO reset sequence. On-site operator accepts possible disk-service downtime. | Before first Inquiry |
| Explicit normal-success release policy | Successful register cleanup is not electrical measurement; uncertainty | Upstream circuit model, matched normal cleanup and exact helper completion | Review and explicitly accept upstream-compatible normal-cleanup assumption for this limited test, or choose an instrumented initial validation. If needed, observe bus-idle state with a suitable external instrument; avoid a competing GPIO capture process. No exhaustive crash matrix required now. | Decide in first validation plan |
| Fresh no-conflict baseline and unique IDs | Sampler disk activity/another initiator overlaps selection; possible ordinary operational risk | Whole-session ownership and ID checks | Operator makes bus quiescent; verify target/initiator IDs and preserved configuration under approved preflight. No notes, disk loads or management actions during experiment. | Immediately before command |
| Full timeout/crash electrical characterization | Unattended recovery might falsely restore bus | Conservative failure containment | Defer systematic fault injection, automatic recovery design and long-transfer validation. Do not intentionally crash the helper on the first physical test. | Before unattended operation / broader transfers |

The normal-success policy is a choice requiring explicit review, not a hidden assertion of measured safety. Failure containment can make a first attended experiment proportionate without proving automated electrical recovery. A cold recovery option is only viable after accounting for actual power sources and preserving journal/assignment evidence; this document provides no unplugging, power-cycling or pin instructions.

## 5. Practical milestone

Prepare **FIRST-INQUIRY-CONTROLLED-VALIDATION-PLAN.md** covering the three conditions, exact accepted binary/controller bindings, one-use approval, target/initiator IDs, ownership/stop/fence admission, one fixed command, bounded execution, exact completion/output acceptance, normal restoration policy and fail-closed operator handoff. No automatic retry, reset, autosense, MODE, upload or sampler write. Do not install or execute the plan as part of preparation.

Success proves only one controlled INQUIRY against the actual sampler and the chosen normal-cleanup/restoration behavior. It does not prove MESA upload allocation, PCM transfer phase handling, continuous control or robust unattended recovery. Those belong to later narrowly staged milestones toward SEND PROGRAM.

The previous blanket requirement for unavailable supplier schematics is superseded by this conditional, evidence-based assessment. The earlier physical NO-GO remains applicable to execution **until the specific conditions and separate authorisation are met**; it is no longer a reason to stop preparing controlled validation.
