"""
Note.py

Definition of the Note class, representing an individual musical note.

Licenced under GPL 3.0

"""

class Bar:
    
    # Woodwing, Brass, String, Klavier, etc
    __InstrumentType = ""
    __InstrumentName = ""
    __InstrumentRange = [0,1]
    __InstrumentIndex = "0"
    
    __clef = ""
    # where the clef is centred at (NoteIndex)
    __clefCentre = 0
    
    __scale = ""
    __scaleIndex = 0
    
    __tempo = ""
    
    __tempoChangeFunc = func()
    
    __beat = 1/1
    
    # scale definition (aka key signature)
    __scale = "C"
    # the Index is found at "Théorie de la Musique (Danhauser)"
    __scaleIndex = 0
    
    # associated scale
    __relativeScale = "Am"
    __relativeScaleIndex = 0
    
    
    def __init__(self, clef, ):
        pass
    
    # content in the bar
    __NoteContent = list(Note("C"), Note("D"))
    
    def Instrument2Index(self):
        pass
        
    def checkRange(self):
        pass
    
    def addNote(self):
        pass
        
    def addNoteGroup(self):
        pass
    
    def addPause(self):
        pass
        
    def getRelativeScale(self):
        pass
    
    
    
