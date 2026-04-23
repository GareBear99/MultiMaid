> 🎛️ Part of the [TizWildin Plugin Ecosystem](https://garebear99.github.io/TizWildinEntertainmentHUB/) — 19 free audio plugins with a live update dashboard.
>
> [FreeEQ8](https://github.com/GareBear99/FreeEQ8) · [XyloCore](https://github.com/GareBear99/XyloCore) · [Instrudio](https://github.com/GareBear99/Instrudio) · [Therum](https://github.com/GareBear99/Therum_JUCE-Plugin) · [BassMaid](https://github.com/GareBear99/BassMaid) · [SpaceMaid](https://github.com/GareBear99/SpaceMaid) · [GlueMaid](https://github.com/GareBear99/GlueMaid) · [MixMaid](https://github.com/GareBear99/MixMaid) · [MultiMaid](https://github.com/GareBear99/MultiMaid) · [MeterMaid](https://github.com/GareBear99/MeterMaid) · [ChainMaid](https://github.com/GareBear99/ChainMaid) · [PaintMask](https://github.com/GareBear99/PaintMask_Free-JUCE-Plugin) · [WURP](https://github.com/GareBear99/WURP_Toxic-Motion-Engine_JUCE) · [AETHER](https://github.com/GareBear99/AETHER_Choir-Atmosphere-Designer) · [WhisperGate](https://github.com/GareBear99/WhisperGate_Free-JUCE-Plugin) · [RiftWave](https://github.com/GareBear99/RiftWaveSuite_RiftSynth_WaveForm_Lite) · [FreeSampler](https://github.com/GareBear99/FreeSampler_v0.3) · [VF-PlexLab](https://github.com/GareBear99/VF-PlexLab) · [PAP-Forge-Audio](https://github.com/GareBear99/PAP-Forge-Audio)
>
> 🎁 [Free Packs & Samples](#tizwildin-free-sample-packs) — jump to free packs & samples
>
> 🎵 [Awesome Audio](https://github.com/GareBear99/awesome-audio-plugins-dev) — (FREE) Awesome Audio Dev List

# MultiMaid

**Control your mix where it matters most.**

MultiMaid is a focused multiband dynamics plugin for the Maid suite. It is intentionally designed to **not** overlap with FreeEQ8, GlueMaid, MixMaid, BassMaid, SpaceMaid, ChainMaid, or MeterMaid.

## Core role

MultiMaid is the **band-dynamics control engine** of the suite.

It answers one question:

> Which frequency regions are out of control, and how do I tame them cleanly?

It is **not**:
- a parametric EQ
- a glue compressor
- an auto-mix assistant
- a bass enhancement tool
- a space tool
- a sidechain interaction tool
- a metering/judgment tool

## Locked ecosystem boundaries

### FreeEQ8
FreeEQ8 shapes tone precisely.

MultiMaid does **not** include:
- bell/shelf nodes
- Q control
- surgical graph editing
- match EQ

### GlueMaid
GlueMaid handles whole-mix cohesion.

MultiMaid does **not** become a single-band bus glue compressor.

### MixMaid
MixMaid is the assistant/corrector.

MultiMaid does **not** auto-fix mixes or run reference-matching workflows.

### BassMaid
BassMaid enhances low-end character.

MultiMaid only controls low-band dynamics.
It does **not** generate sub harmonics or act as a bass sweetener.

### SpaceMaid
SpaceMaid handles width, depth, delay, and reverb.

MultiMaid does **not** touch space processing.

### ChainMaid
ChainMaid handles interaction and ducking.

MultiMaid does **not** lead with external sidechain routing or ducking identity.

### MeterMaid
MeterMaid judges and validates.

MultiMaid only shows action-state metering:
- band energy
- gain reduction
- crossover view

## Product scope

### v1 focus
- 3-band mode
- Linkwitz-Riley style crossover network
- per-band downward compression
- Threshold / Ratio / Attack / Release / Knee / Trim
- Solo / Mute / Bypass per band
- band energy + gain reduction meters
- input / output / dry-wet
- clear crossover visualization

### Pro path later
- 4-band mode
- range control
- optional per-band character/drive
- optional detector modes

## Repo status

This package is a **serious architecture baseline and source-of-truth repo scaffold**.

It is **not yet** honestly production-ready or validated as best-in-class until:
- built in real JUCE targets
- tested in real hosts
- validated for crossover integrity and automation safety
- RT-audited under hostile settings

## Build

```bash
cmake -B build -DJUCE_DIR=/path/to/JUCE
cmake --build build --config Release
```

## File map

- `Source/PluginProcessor.*` — plugin shell, process loop
- `Source/PluginEditor.*` — product UI
- `Source/Core/Parameters.*` — parameter IDs and layout
- `Source/DSP/` — crossover, detectors, compressor, engine
- `Source/UI/` — band module and crossover view scaffolding
- `docs/ROLE_BOUNDARIES.md` — non-conflict rules
- `docs/VALIDATION_PLAN.md` — real release-gate path
- `docs/RELEASE_GATES.md` — must-pass checklist
- `assets/MultiMaid_UI_Demo.html` — HTML source-of-truth visual demo

## Tagline options
- Control your mix where it matters most.
- Clear multiband control without the clutter.
- Tame lows, mids, and highs with confidence.

## Honest status

MultiMaid is currently positioned as a **core suite pillar** between:
- FreeEQ8 → shape
- MultiMaid → control
- GlueMaid → glue

This package gets you to a strong repo baseline fast, without blurring the ecosystem.
