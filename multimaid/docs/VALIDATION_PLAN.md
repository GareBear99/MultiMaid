# MultiMaid Validation Plan

## Technical validation

### 1. Flat recombination integrity
- all bands bypassed
- compressor neutral settings
- verify summed output remains clean and stable

### 2. Crossover correctness
- sweep test through crossover points
- verify no major holes/bumps
- validate automation safety when moving crossovers

### 3. Gain computer validation
- threshold behavior
- ratio behavior
- attack/release envelope timing
- knee curve sanity

### 4. Meter validation
- band activity follows energy changes
- gain reduction meters track actual applied gain

## Realtime validation
- 44.1 / 48 / 96 / 192 kHz
- 32 / 64 / 128 / 256 / 512 / 1024 sample buffers
- aggressive automation tests
- long-session stability tests

## Listening validation
- full mix bus
- drum bus
- vocal bus
- bass-heavy material
- harsh synth material

## Release criteria
The plugin is not considered release-ready until:
- no obvious recombination artifacts
- no clicks on parameter changes
- no allocations in processBlock
- stable in real hosts
