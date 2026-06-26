# NOTES

## Mod Matrix

## env to tune
Processor::Processor()
    populatemodmatrix()

Processor::prepareToPlay()
    get expected number of samples
        reserve space - all inputManagers and outputManagers
            CLEAR (if using sampleBuffer and not std::vector)

Processor::processBlock()
    reserve space if needed - all inputManagers and outputManagers
    get current scaling values
    (clear all blocks?)
    calculate all outputManager blocks
    send all modulations with current scaling
    all inputManagers applyModulation
    voice processblock


## types of io manager

mono to mono
    o to i

mono to poly
for i in size
    o to i[i]

poly to mono?
get average value? or use last value


poly to poly
for i in size
    o[i] to i[i]



### ModulationSignalBlock

### ModulationSource
LFO1
LFO2
Envelope (PER VOICE)
(wave osc) (PER VOICE)

They all write to a ModulationSignalBlock

### ModulationDestinations
Osc1 level
Osc1 tune

They all read from a ModulationSignalBlock

## ModulationRouting
Modulation source
Modulation destination
Scaling