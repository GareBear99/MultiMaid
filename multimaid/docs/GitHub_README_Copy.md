# MultiMaid

**Control your mix where it matters most.**

MultiMaid is a focused multiband dynamics plugin for the Maid suite.
It is built to control **broad frequency regions** cleanly, quickly, and without turning into another EQ, glue compressor, or auto-mix assistant.

## What it does

MultiMaid splits your signal into broad bands and gives each band its own compressor.

Use it to:
- tame boomy lows
- stabilize muddy low-mids
- control harsh upper mids / highs
- smooth region-specific dynamics before glue or mastering

## What it does **not** do

To keep the Maid ecosystem clean, MultiMaid is intentionally restricted.

It is **not**:
- a parametric EQ replacement for FreeEQ8
- a whole-mix glue compressor replacement for GlueMaid
- an assistant / one-click fixer like MixMaid
- a low-end enhancement tool like BassMaid
- a reverb / width / delay tool like SpaceMaid
- a ducking / signal interaction tool like ChainMaid
- a mastering judge like MeterMaid

## Suite role

- **FreeEQ8** → shape
- **MultiMaid** → control
- **GlueMaid** → glue
- **MeterMaid** → judge

## Planned feature set

### v1
- 3-band mode
- clear crossover visualization
- per-band Threshold / Ratio / Attack / Release / Knee / Trim
- Solo / Mute / Bypass per band
- gain reduction + band activity metering
- Input / Output / Dry-Wet

### later
- 4-band mode
- range control
- optional detector modes
- optional per-band character

## Status

This repo package is a **strong architecture baseline** and source-of-truth starter for the real JUCE build.
It is not yet claiming production validation or best-in-class release status.

## Why it exists

Most multibands either:
- feel cluttered
- overlap with EQ workflows
- hide band behavior
- or try to be everything at once

MultiMaid is going the other direction:

> **clear premium multiband control with zero confusion**
