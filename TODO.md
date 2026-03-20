# NOTES

## Task list
- Check all range-based for loops - const, value/ref
- Can I change shared_ptr<ModulationSignalBlock> to ModulationSignalBlock& in function calls?
- Bitcrusher
    - Check if it processes values outside of [-1, 1]
    - Check if other bitcrushers ever result in silence at low resolutions
- Mod Matrix
    - Single routing
        - Route osc1 env to osc1 tune using mod matrix
    - Minimal matrix
        - Choose 2 signal inputs and 2 signal outputs
        - Manually make sliders and parameters
        - Modulate using mod matrix
    - Full matrix
        - Add all signal inputs and outputs to mod matrix
        - Dynamically make sliders and parameters
    - Naming
        - Decide on either input/output or source/destination? Or when to use one or the other?
    - Parameter Consistency
        - parameter order in modulation functions (e.g. sourceID, shared_ptr<source>?)
- SignalBlocks (and anything which contains a signal block)
    - What happens if one block is larger than usual, then the next is the usual size? Is the larger size still passed around?
    - Should reserve space change to setSize()?
## Notes

