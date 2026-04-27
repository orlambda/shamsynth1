# NOTES

## Next
- Test current typical output level of synth
- Find more suitable value

## Task list
- Reduce overall level of synth
- Make noise generator louder
- Check all range-based for loops - const, value/ref
- Can I change shared_ptr<ModulationSignalBlock> to something else e.g. ModulationSignalBlock& in function calls?
- Bitcrusher
    - Check if it processes values outside of [-1, 1]
    - Check if other bitcrushers ever result in silence at low resolutions (probably not)
- Check mod matrix negative scaling on all inputs (pitch, level, bitdepth, etc)
    - Should be fine if it works correctly
    - -1 becomes +1, +1 becomes -1
- Mod Matrix
    - Minimal 2x2 matrix
        - Outputs
            - adsrEnv
            - lfo1
        - Inputs
            - osc1 tune
            - osc1 level
        - Manually make sliders and parameters
        - Modulate using mod matrix
    - Full matrix
        - Add all signal inputs and outputs to mod matrix
        - Things to do dynamically:
            - Parameters
            - Sliders
            - ...
    - Naming
        - Decide on either input/output or source/destination? Or when to use one or the other?
    - Parameter Consistency
        - parameter order in modulation functions (e.g. sourceID, shared_ptr<source>?)
- SignalBlocks (and anything which contains a signal block)
    - What happens if one block is larger than usual, then the next is the usual size? Is the larger size still passed around?
    - Should reserve space change to setSize()?

## Notes

