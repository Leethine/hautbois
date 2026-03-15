(load "ly-lib.scm")

(display 
  (read-token->list "test.txt") 
)

(define outfile (open-output-file "test_out.txt"))
(write (ly-singlenote-split3 "do'''4.") outfile)
(close-output-port outfile)

(display #\newline)

(display 
(ly-singlenote-split2 "do'''4.")
)

(display 
(ly-singlenote-split3 "do'''4.")
)

(display #\newline)
