# Hautbois

### The Hautbois Project

The "**H**ybrid **a**nd **U**niversal **T**ext-**B**ased **O**rchestral **I**nstruments **S**imulator" project, aka Hautbois, as the name indicates, aimes to create a text-based simulator for classical music.

<img src="https://raw.githubusercontent.com/Leethine/hautbois/c5dd6a35552d5d72adc3361fe90f631e63f6956c/icon.svg" width="120" height="120">

### Components

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

    (notation) Basic notation system definition.

    (typesetting) Typesetter or engraver that generate PDF and SVG files.

 - Conductor

    (interp) Text-based sequence creator.
 
 - Instrument player

    (instruments) Instrument modeller based on [FAUST](https://faust.grame.fr/ "Functional Programming Language for Real Time Signal Processing")

    (filter) Filter components
    


### Release Names and Version Control

Release that involves major break-through should use the name borrowed from classical music pieces.

Within each major release, versions are numbered by No.X, i.e., _**ReleaseName**_ **No.X**. 

For example:

#### Currently under development:
#### _Sonate par ordinateur n° 0_

#### Completed release:
#### _None_
