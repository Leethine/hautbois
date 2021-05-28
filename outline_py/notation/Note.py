"""
Note.py

Definition of the Note class, representing an individual musical note.

Licenced under GPL 3.0

"""


class Note:
    
    # Notation system
    __sysName = ""
    
    # Note name and its index of the note on keyboard
    __Name = ""
    __NoteIndex = 0
    
    # Duration, 1/4, 3/4
    __Duration = 0
    
    # Ornament Type: "Glissando", "Trill"...etc
    __OrnamentType = ""
    
    # Parameter for the Ornament 
    __OrnamentParam = ""
    
    # Force of the Note, e.g. pp ff..
    __Force
    
    # More properties maybe ...
    
    
    def __init__(self):
        pass
        
    def __SciName2Index(self):
        pass
    
    def __Latin2Index(self):
        pass
    
    def __Helm2Index(self):
        pass
        
    def __Latin2Sci(self):
        pass
        
    def __Sci2Latin(self):
        pass
    
    def __checkNameType(self):
        pass
