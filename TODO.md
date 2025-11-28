# NOTES
starting as monosynth, eventually polysynth
polysynth - each Voice will need its own Oscillators
    as they each need their own .nextSample()
    Voice and Osc both have .nextSample() - inherit from common class?
std::vector<Voice> Voices

# Task list
output a constant sine wave
control sine wave frequency with midi input from keyboard component
control sine wave frequency with external midi

# Volume control
Start with 0.0 - 1.0
Research typical ranges
- Dial
- Volume public variable
- sample variable = 0.0
- (add voices)
- add to audio output

# White noise generator
Mono
- Create class
- .nextSample() (abstract Oscillator class?)
- add to audio output
- level dial

# Sine wave oscillator
Mono
- Create class
- .nextSample()
- add to audio output
- level dial

# MIDI input
Start as a monosynth
- vector of notesHeld (frequencies, eventually velocity)
- note on event = add to vector
- note off event = remove from vector
- for every sample / call of processBlock (research which),
    - if notesHeld
        - pitch is last pitch added
    - else sample is 0

# Square wave oscillator

# ADSR 

# Blend sine/triangle/square waves
- Research
- Dial

# Control grid
Arrange dials using a grid object or function

# Possible features
- Graphical envelope representation/control
- output level meter
