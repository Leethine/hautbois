#pragma once

#ifndef CORE_TYPES_H
#define CORE_TYPES_H

#define UINT8  unsigned char
#define UINT16 unsigned short int
#define UINT32 unsigned int
#define UINT64 unsigned long

#define CHAR_PITCHNAME_C            'C'
#define CHAR_PITCHNAME_D            'D'
#define CHAR_PITCHNAME_E            'E'
#define CHAR_PITCHNAME_F            'F'
#define CHAR_PITCHNAME_G            'G'
#define CHAR_PITCHNAME_A            'A'
#define CHAR_PITCHNAME_B            'B'
#define CHAR_PITCHNAME_REST         'R'
#define CHAR_PITCHNAME_SILENCE      'S'
#define CHAR_ACCIDENTAL_FLAT        'b'
#define CHAR_ACCIDENTAL_SHARP       '#'
#define CHAR_ACCIDENTAL_DOUBLEFLAT  'B'
#define CHAR_ACCIDENTAL_DOUBLESHARP 'x'
#define CHAR_ACCIDENTAL_NATURAL     'n'  
#define CHAR_ACCIDENTAL_FLAT        'b'
#define CHAR_ACCIDENTAL_SHARP       '#'
#define CHAR_ACCIDENTAL_DOUBLEFLAT  'B'
#define CHAR_ACCIDENTAL_DOUBLESHARP 'x'

#define CHAR_OCTAVE_DEFAULT    '4'

#define CHAR_SINGLENOTE_TYPE   'N'
#define CHAR_CHORD_TYPE        'C'
#define CHAR_TUPLET_TYPE       'T'
#define CHAR_RESTNOTE_TYPE     'R'
#define CHAR_SILENCENOTE_TYPE  'S'
#define CHAR_GRACENOTE_TYPE    'G'
#define CHAR_APPOGGIATURA_TYPE 'P'
#define CHAR_ACCIACCATURA_TYPE 'A'

#endif