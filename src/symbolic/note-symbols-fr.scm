(define all-it-note-name
  '(
    ut do re mi fa sol la si
    dod red mid fad sold lad sid
    dodd redd midd fadd soldd ladd sidd
    dox rex mix fax solx lax six
    dob reb mib fab solb lab sib
    dobb rebb mibb fabb solbb labb sibb
    r, R, s, S
  )
)

(define it-note-name-map
  '(
    (ut .  "C")
    (do .  "C")
    (re .  "D")
    (mi .  "E")
    (fa .  "F")
    (sol . "G")
    (la .  "A")
    (si .  "B")
    ;; Flats
    (utb .  "Cb")
    (dob .  "Cb")
    (reb .  "Db")
    (mib .  "Eb")
    (fab .  "Fb")
    (solb . "Gb")
    (lab .  "Ab")
    (sib .  "Bb")
    ;; Sharps
    (utd .  "C#")
    (dod .  "C#")
    (red .  "D#")
    (mid .  "E#")
    (fad .  "F#")
    (sold . "G#")
    (lad .  "A#")
    (sid .  "B#")
    ;; Double Sharps
    (utdd .  "Cx")
    (dodd .  "Cx")
    (redd .  "Dx")
    (midd .  "Ex")
    (fadd .  "Fx")
    (soldd . "Gx")
    (ladd .  "Ax")
    (sidd .  "Bx")
    (utx .   "Cx")
    (dox .   "Cx")
    (rex .   "Dx")
    (mix .   "Ex")
    (fax .   "Fx")
    (solx .  "Gx")
    (lax .   "Ax")
    (six .   "Bx")
    ;; Double Flats
    (utbb .  "Cbb")
    (dobb .  "Cbb")
    (rebb .  "Dbb")
    (mibb .  "Ebb")
    (fabb .  "Fbb")
    (solbb . "Gbb")
    (labb .  "Abb")
    (sibb .  "Bbb")
    ;; Rest, silence
    (r . "R")
    (R . "R")
    (s . "S")
    (S . "S")
  )
)
