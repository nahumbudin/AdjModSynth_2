# AdjModSynth_2
AdjHeart Modular Synthesizer for Raspberry Pi Qt C++ GUI

www.adjheart.com

This is the synthesizer GUI application implemented with Qt.

Concept screenshots samples are provided in the screenshots folder (actual screenshots may be viewd on the AdjHeart website)

## The AdjHeartTM Modular Synthesizer.

The AdjHeart modular musical synthesizer is a software application implementing a comprehensive and features-rich musical-instrument designed and built to run on the low-cost Raspbian (Linux) based Raspberry Pi hardware platforms.

The AdjHeart modular musical synthesizer (ModSynth)  integrates 2 main modules:

  - FluidSynth - an open-source SoundFont based synthesizer 
  - AdjSynth - a multi features polyphonic synthesizer.
  
The AdjHeart ModSynth utilizes the following technologies:

  - JackAudio for low-latency real time audio streaming.
  - ALSA MIDI for interfacing real time external MIDI input devices.
  - OpenMP for CPU multi-cores load-balancing.
  - Bluetooth multiple SPP connections server supporting wireless MIDI streams links. 
  - Qt based comprehensive and reach GUI.

The AdjHeart ModSynth enables various settings and control capabilities:

  - Selecting a program (sound) for any of the 16 MIDI channels.
  - 16 channels MIDI mixer with individual volume, pan and send control for each channel.
  - Saving and loading presets.
  - Incremental interactive editing of sound patches.
  - Mapping any external MIDI keyboard control to any AdjHeart ModSynth control.
  
## The FluidSynth SoundFont Synthesizer.

FluidSynth is a real-time software synthesizer based on the SoundFont 2 specifications and has reached widespread distribution. FluidSynth itself does not have a graphical user interface, but due to its powerful API it was well integrated with the AdjHeart ModSynth control and sound system, as well as with the AdjHeart ModSynth comprehensive GUI. 

## General Description of the AdjSynth Synthesizer.

Each of the AdjSynth synthesizer polyphonic voice implements the following:

  - 2 VCOs, VCO-1 and VCO-2, where VCO-1 provides multiple harmonics mixer to enable Organ like sounds generation.
  - Selectable  multicolored Noise-generator.
  - Karplus Strong String Generator.
  - Morphed-sinus Oscillator.
  - IFFT wave-table based PAD-generator.
  - 2 Filters that each may be individually set to LPF, HPF, BPF or Path-through mode.
  - Distortion effect.
  - 5 ADSR envelope generator.
  - 5 LFOs with delayed trigger capability.
  - Output mixer with control over Volume, Pan and Send levels.

The AdjSynth Synthesizer provides common control and processing capabilities:

  - 10 Bands Graphic Equalizer.
  - 2 Reverberation models.
  - Split-keyboard and Keyboard-Sensitivity control.
  - Portamento (monophonic mode only).

The AdjSynth Synthesizer provides the user with editing, management and configuration capabilities:

  - Full control and editing mode for creating sound-patches.
  - 3 Sketches for incremental patch creation.​ 
  - Saving and loading Patch-files.
  - Saving and loading settings file.
