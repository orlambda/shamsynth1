# TODO

## Next
- change period to `1.0`?

## Task list

### Bug fixes
- bug: LFO rate 0 depth 1 affects tune and level when scaling != 0
    - could be that LFO is paused on non-0 value
    - could be that 0-value modulation wrongly affects tune
    - could be that env is incorrectly routed/scaled instead of lfo
- memory leak:
    - Reached this when closing the plugin - this doesn't always happen. What causes it? Is anything else other than Timer ever leaked?
    2026-05-02 : 1 leaked Timer caused this
    ~LeakCounter()
    {
        if (numObjects.value > 0)
        {
            DBG ("*** Leaked objects detected: " << numObjects.value << " instance(s) of class " << getLeakedObjectClassName());

            /** If you hit this, then you've leaked one or more objects of the type specified by
                the 'OwnerClass' template parameter - the name should have been printed by the line above.

                Many errors like this are caused by using old-fashioned, non-RAII techniques for
                object management. If you're seeing this, it's a good idea to double-check
                that you're using std::unique_ptrs, OwnedArrays,
                ReferenceCountedObjects, etc, and avoiding manual calls to the 'delete'
                operator at all costs!

                You may also see this error if JUCE's shutdown code is called while an object
                containing a leak detector is still alive (perhaps declared as a namespace-scope
                static).
            */
            jassertfalse;
        }
    }

### Features to add
- Add future features from README

### Parameters, values, design

### Testing

### Optimisation
- General
    - Decide how to measure performance
        - Measure performance of specific sections of code
    - Decide how to track performance e.g. spreadsheet
    - Compare performance between versions
    - Optimise
        - Find slowest code
        - Find code that's easy to improve (e.g. triangle function from wavetable)
    - Create format for users to submit performance reports, system/DAW info etc
- triangle wave could read from a wavetable (is this worth it if I'm interpolating?)
- Voices have duplicate ModulatableFloats for some parameters that affect all voices, e.g. level - can this be made static
    - For
        - Only have to update this param once
        - Only have to store it in one place
    - Against
        - Voices have their own mod outputs that control their own level, e.g. envelope
            - updateLevel() could be made static as could the unmodulated param variable, but each voice will need its own modulation input signal block
- voices that are inactive have their modulation blocks updated every sample
    - active/inactive can change at any sample (starts when midi note hits, ends when adsr ends)
        - 
- near -0.0 mod blocks are still applied to inputs
    - can each mod block have `bool clear = true` at the start of processBlock and only change if a non-zero value is added?
        - `clear` is checked when a modulation signal is sent/applied/read

### Implementation
- change period from `2*pi` `to 1.0`. (sin isn't be called directly but by index in a lookup table so we don't need radians)

### Code improvement, modernisation
- find unnecessary for loops, chances to use algorithm header
- Check all range-based for loops - const, value/ref

### Naming
- rename 'osc1env' - env actually belongs to Voice
- rename 'tune' to osc1 tune - osc2 etc will also have tune

### Research

### other
- Look through code for TODO comments

### sort into categories
- Change sliders to dials
- Make modmatrix dials layout clear (grid, labels on x and y)
- Can I change shared_ptr<ModulationSignalBlock> to something else e.g. ModulationSignalBlock& in function calls?
- Envelope - do I want it to make level louder? Do I want negative scaling to decrease level and positive scaling not to - i.e. positive scaling is the same as 0 value when sustain is at highest value? see TODO
- Bitcrusher
    - compare bitcrusher side by side with bitcrush plugin
        - make version of synth that doesn't scale volume down (so osc volume is final volume) - make this enableable for debugging
    - check how changes in v.1.0.21, v.1.0.22, and v1.0.31 affected behaviour
    - check if it processes values outside of [-1, 1]
    - check if other bitcrushers ever result in silence at low resolutions (probably not..)
    - improve/fix
- Check mod matrix negative scaling on all inputs (pitch, level, bitdepth, etc)
    - Should be fine if it works correctly
    - -1 becomes +1, +1 becomes -1
- Mod Matrix
    - Full matrix
        - Add all signal inputs and outputs to mod matrix
        - Things to do dynamically:
            - Parameters
            - Sliders
            - ...
    - Parameter Consistency
        - parameter order in modulation functions (e.g. sourceID, shared_ptr<source>?)
- SignalBlocks (and anything which contains a signal block)
    - What happens if one block is larger than usual, then the next is the usual size? Is the larger size still passed around?
    - Should reserve space change to setSize()?

### notes