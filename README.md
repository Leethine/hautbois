# Hautbois

### The Hautbois Project

The "**H**ybrid **a**nd **U**niversal **T**ext-**B**ased **O**rchestral **I**nstruments **S**imulator" project, abbreviated as "Hautbois". The initial aim was to create a classical music simulator from text-based scripts. However, this project has grown with time, the features extended beyond a simple simulator, but more of a versatile system.

<img src="https://raw.githubusercontent.com/Leethine/hautbois/c5dd6a35552d5d72adc3361fe90f631e63f6956c/icon.svg" width="180" height="180">

[pipeline]

### Components

 - [kernel] Logical representation kernel [status]

 - [compile] Music script compiler [status]
 
 - [theory] Music theory related definitions [status]

 - [audio] Sound synthesis and audio generation [status]

 - [interp] Music interpretation from the script [status]

 - [analysis] Musical analysis module [status]

 - [composition] Computer-aided composition [status]

 - [gregorian] Gregorian chant module [status]


### Development quick note

 - kernel

    [c][notation] notation system that defines musical notation symbols, elements, etc
    [c][charts] definition of map classes for quick-card look-up

 - compile

    [c][parse] "syntax" checker
    [c][lyutils] lilypond utilities

 - theory
    [c][concepts] definition of musical theory concepts
    [c][rules] rules related to counterpoint, chords, cadence, etc.
 
 - audio

    [c][filter] Filter components
    [c][model] instrument models
    
 - interp

 - analysis

 - composition

 - gregorian


### Release Names and Version Control

Release that involves major break-through should use the name borrowed from classical music pieces.

Within each major release, versions are numbered by `n°X`, i.e., `_**ReleaseName**_ **n°X**`. There is also a global version identifier along with  `_ReleaseName_ n°X pattern`, in the format of _**Op. X.X.X**_

[DATE] The latest release is _Invention n°1, Op. 0.1.1_

See release log for details.

### Contribution

Please star or fork this repository!

Icon design

Architecture review

Code refactoring

Pull request

Musical knowledge support

Donation