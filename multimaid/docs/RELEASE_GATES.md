# MultiMaid Release Gates

## Must-pass before release

### DSP
- [ ] Crossover recombination validated
- [ ] Gain reduction behavior validated
- [ ] Threshold/ratio timing logic verified
- [ ] No audible zipper noise on smoothed params

### RT Safety
- [ ] No allocations in processBlock
- [ ] No locks in processBlock
- [ ] Stable under 32 buffer stress
- [ ] Stable under 192 kHz stress

### Host matrix
- [ ] Reaper verified
- [ ] Ableton verified
- [ ] FL Studio verified
- [ ] Logic/AU verified if shipping AU

### Product
- [ ] Resizable layout complete
- [ ] Band meters readable
- [ ] Presets useful and non-destructive
- [ ] Export/import state reliable

### Suite integrity
- [ ] No FreeEQ8 overlap in UI or messaging
- [ ] No GlueMaid overlap in identity
- [ ] No MixMaid overlap in automation logic
