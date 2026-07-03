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

## Error
This happens osc1EnvOutputSubstrings etc.'s type from ParameterNames to ModulationOutputNames:

In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.cpp:9:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.h:11:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/Voice.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInputManager.h:15:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulatableFloat.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInput.h:16:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationOutput.h:14:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationSignalBlock.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/vector:325:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/formatter_bool.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/concepts.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/format_parse_context.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/string_view:941:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/algorithm:1842:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__algorithm/for_each.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__ranges/movable_box.h:21:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/optional:1294:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/memory:940:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/allocator.h:15:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/allocate_at_least.h:13:
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/allocator_traits.h:328:5: error: no matching function for call to '__construct_at'
  328 |     std::__construct_at(__p, std::forward<_Args>(__args)...);
      |     ^~~~~~~~~~~~~~~~~~~
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.cpp:9:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.h:11:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/Voice.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInputManager.h:15:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulatableFloat.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInput.h:16:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationOutput.h:14:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationSignalBlock.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/vector:325:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/formatter_bool.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/concepts.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__format/format_parse_context.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/string_view:941:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/algorithm:1842:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__algorithm/for_each.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__ranges/movable_box.h:21:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/optional:1294:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/memory:944:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/inout_ptr.h:16:
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/shared_ptr.h:266:33: note: in instantiation of function template specialization 'std::allocator_traits<std::allocator<ModulationOutputManager>>::construct<ModulationOutputManager, bool, const ParameterValues::ModulationOutputNames &, void, 0>' requested here
  266 |     allocator_traits<_TpAlloc>::construct(__tmp, __get_elem(), std::forward<_Args>(__args)...);
      |                                 ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/shared_ptr.h:845:51: note: in instantiation of function template specialization 'std::__shared_ptr_emplace<ModulationOutputManager, std::allocator<ModulationOutputManager>>::__shared_ptr_emplace<bool, const ParameterValues::ModulationOutputNames &, std::allocator<ModulationOutputManager>, 0>' requested here
  845 |   ::new ((void*)std::addressof(*__guard.__get())) _ControlBlock(__a, std::forward<_Args>(__args)...);
      |                                                   ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/shared_ptr.h:853:15: note: in instantiation of function template specialization 'std::allocate_shared<ModulationOutputManager, std::allocator<ModulationOutputManager>, bool, const ParameterValues::ModulationOutputNames &, 0>' requested here
  853 |   return std::allocate_shared<_Tp>(allocator<__remove_cv_t<_Tp> >(), std::forward<_Args>(__args)...);
      |               ^
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.cpp:9:
/Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.h:104:74: note: in instantiation of function template specialization 'std::make_shared<ModulationOutputManager, bool, const ParameterValues::ModulationOutputNames &, 0>' requested here
  104 |     std::shared_ptr<ModulationOutputManager> osc1EnvOutputManager = std::make_shared<ModulationOutputManager>(true, osc1EnvOutputSubstrings);
      |                                                                          ^
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.cpp:9:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/PluginProcessor.h:11:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/Voice.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInputManager.h:15:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulatableFloat.h:13:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationInput.h:16:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationOutput.h:14:
In file included from /Volumes/T7_1/Coding/JUCE/shamsynth1/Source/Voice/../Modulation/ModulationSignalBlock.h:16:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/vector:308:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__algorithm/copy.h:12:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__algorithm/copy_move_common.h:18:
In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__string/constexpr_c_functions.h:14:
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/__memory/construct_at.h:47:58: note: candidate template ignored: substitution failure [with _Tp = ModulationOutputManager, _Args = <bool, const ParameterValues::ModulationOutputNames &>]: no matching constructor for initialization of 'ModulationOutputManager'
   46 | template <class _Tp, class... _Args, class = decltype(::new(std::declval<void*>()) _Tp(std::declval<_Args>()...))>
      |                                                                                    ~~~
   47 | _LIBCPP_HIDE_FROM_ABI _LIBCPP_CONSTEXPR_SINCE_CXX20 _Tp* __construct_at(_Tp* __location, _Args&&... __args) {