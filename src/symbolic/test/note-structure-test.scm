(load "note-structure.scm")

;; Test
(begin

(display
(make-single-note-intermediate* (tokenize-any 'c4.))
)
(display
(make-single-note-intermediate* (tokenize-any 'c___4.))
)
(display
(make-single-note-intermediate* (tokenize-any 'f^^^4.))
)
(display #\newline)
(display #\newline)

(display 'cf^+ex_+g8.)
(display " ==> ")
(display
(make-chord-or-xuplet-note-intermediate* #\+ (tokenize-any 'cf^+ex_+g8.))
)
(display #\newline)

(display 'cf^-ess^^-g__4)
(display " ==> ")
(display
(make-chord-or-xuplet-note-intermediate* #\- (tokenize-any 'cf^-ess^^-g__4))
)
(display #\newline)
(display #\newline)

(display
(note-symbol->IR 'css^4)
)
(display #\newline)

(display
(note-symbol->IR 'r8.)
)
(display #\newline)

(display
(note-symbol->IR 's2.)
)
(display #\newline)

(display
(note-symbol->IR 'cf^-ess^^-g__4)
)

(display #\newline)

(display
(note-symbol->IR 'css^+ex_+g__4.)
)
(display #\newline)
)