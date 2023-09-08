(define all-en-note-name
  '(
    c d e f g a b
    cs ds es fs gs as bs
    css dss ess fss gss ass bss
    cx dx ex fx gx ax bx
    cf df ef ff gf af bf
    cff dff eff fff gff aff bff
    r, R, s, S
  )
)

(define en-note-name-map
  '(
    (c . "C")
    (d . "D")
    (e . "E")
    (f . "F")
    (g . "G")
    (a . "A")
    (b . "B")
    ;; Flats
    (cf . "Cb")
    (df . "Db")
    (ef . "Eb")
    (ff . "Fb")
    (gf . "Gb")
    (af . "Ab")
    (bf . "Bb")
    ;; Sharps
    (cs . "C#")
    (ds . "D#")
    (es . "E#")
    (fs . "F#")
    (gs . "G#")
    (as . "A#")
    (bs . "B#")
    ;; Double Sharps
    (css . "Cx")
    (dss . "Dx")
    (ess . "Ex")
    (fss . "Fx")
    (gss . "Gx")
    (ass . "Ax")
    (bss . "Bx")
    (cx . "Cx")
    (dx . "Dx")
    (ex . "Ex")
    (fx . "Fx")
    (gx . "Gx")
    (ax . "Ax")
    (bx . "Bx")
    ;; Double Flats
    (cff . "Cbb")
    (dff . "Dbb")
    (eff . "Ebb")
    (fff . "Fbb")
    (gff . "Gbb")
    (aff . "Abb")
    (bff . "Bbb")
    ;; Rest, silence
    (r . "R")
    (R . "R")
    (s . "S")
    (S . "S")
  )
)
