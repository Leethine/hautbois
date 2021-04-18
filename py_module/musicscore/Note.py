"""
Note.py

Definition of the Note class, representing an individual musical note.

Licenced under GPL 3.0

"""


class Note:
    
    # Scientific name, e.g. C5, A6 ...
    self.__Name = ""
    
    # Latin name, e.g. dol2, re6, mi3
    self.__LatinName = ""
    
    # Index of the note on keyboard
    self.__NoteIndex = 0
    
    # Duration, 1/4, 1/3
    self.__Duration = 0
    
    # Ornament Type: "Glissando", "Trill"...etc
    self.__OrnamentType = ""
    
    # Parameter for the Ornament 
    self.__OrnamentParam = ""
    
    # Force of the Note, e.g. pp ff..
    self.__Force
    
    def __init__(self):
        pass
        
    def __SciName2Index(self):
        pass
        
    def __Latin2Sci(self):
        pass
        
    def __Sci2Latin(self):
        pass
    
    def __checkNameType(self):
        pass
