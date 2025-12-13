# NOTES
starting as monosynth, eventually polysynth
polysynth - each Voice will need its own Oscillators
    as they each need their own .nextSample()
    Voice and Osc both have .nextSample() - inherit from common class?
std::vector<Voice> Voices

## Task list
- Parameters - allow recording automation from sliders using SliderAttachment or ParameterAttachment

## Notes

### MIDI input
Polyphony - ways to approach:
- map of midi key values and Voices?
- set of midi key values down?
- loop through Voices to see if midi key is down?