# Hautbois

### The Hautbois Project

The "**H**ybrid **a**nd **U**niversal **T**ext-**B**ased **O**rchestral **I**nstruments **S**imulator" project, aka Hautbois, as the name indicates, aimes to create a text-based simulator for classical music.

<img src="https://raw.githubusercontent.com/Leethine/hautbois/c5dd6a35552d5d72adc3361fe90f631e63f6956c/icon.svg" width="180" height="180">

### Components

If you are a not a developer, please read this paragraph. If you are a developer, please also read the following paragraph **(development)**.

Like in the real world, the program consists of several components:

 - Composer

    Composers use to write on parchment with a quill, but nowadays score engraving software provides the facilities. Some commonly-used formats are ABC, MusicXML, [GUIDO](https://guidodoc.grame.fr/ "Guido Music Notation"), [LilyPond](http://lilypond.org/ "LilyPond Priject"), so on and so forth .

 - Conductor

    The "conductor" of the program, like their role in the real world, is to interpretate the composition into definition of music sequences. They then instruct the players to play the music sequence according to their interpretation.

 - Instrument player

    In the real world, the instrument player tries (possibly) to understand the conductors interpretation, and play out the music sounds. In the program, the "instrument player" is the sound sequence generator, who generate the sound sequence according to (for sure) the instruction from the "conductor".


### Development

The components in the developers' framework.

 - Composer

    (notation) A musical notation system that defines the basic symbols, i.e. musical note, bar, sheet.
    
    (contrepoints) Counterpoint system based on pre-18-cetury contrepoints rules.
    
    (improvisor) Real-time improvisation.
    
    (gregorian) Melodic generator for the Gregorian chant.
    
 - Conductor

    (interp) Text-based sequence creator.
 
 - Instrument player

    (instruments) Instrument modeller based on [FAUST](https://faust.grame.fr/ "Functional Programming Language for Real Time Signal Processing") and the [Synthesis ToolKit](https://ccrma.stanford.edu/software/stk/ "The Synthesis ToolKit in C++ (STK)").

    (filter) Filter components
 
 - Musical engravers

    (typesetting) Typesetter or engraver that generates PDF and SVG files.
    
    (monks) Typesetter for Medieval scripts of Gregorian chant.


### Release Names and Version Control

Release that involves major break-through should use the name borrowed from classical music pieces.

Within each major release, versions are numbered by No.X, i.e., _**ReleaseName**_ **No.X**. There should also be a global version identifier along with **releasename+No.X** pattern, started with _**opus**_ or _**Op.**_

#### The first release will be:
#### _Invention n°1, Op. 0.1.1_ 

