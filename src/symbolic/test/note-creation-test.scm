(load "note-creation.scm")
;; Test
(begin

(set-lang! 'en)

(display
(map is-note-symbol? '(c cx gzz 4 r i h))
)
(display #\newline)

(display 
(map is-octave-symbol? '(_ ^^^^^^^ ^^^ ^^ ^ ^^^^ ^^^^^ _____ __ ___ ddd e 123 6 : !))
)
(display #\newline)

)