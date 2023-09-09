;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Define the "data structure" of a note symbol.
; Define lexical check methods and
;  translation methods to intermediate token list.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Symbolized voice absolute mode example:
;; '(
;;  Pattern is like: note-name octave duration
;;    c^^^4
;;  And for rest/silence notes
;;    r4.
;;  Chords
;;    c+e+g_8
;;  Xuplets
;;    g-c-e^2
;;)
;; Same for relative mode.

;; Generated intermediate symbol list
;; '(c ^^^ 4)
;; '(c 4)
;; '(r 4.)
;; '(+ ((c) (e) (g _)) 8)
;; '(- ((g) (c) (e ^)) 2)

(load "algorithm.scm")

;; (make-rest-or-silence-note-intermediate* list_char) => list symbol
(define (make-rest-or-silence-note-intermediate* li)
  (list (string->symbol (string (car li))) (list->string (cdr li))))

;; (make-single-note-intermediate* list_char) => list symbol
(define (make-single-note-intermediate* li)
  (let (
      (notename-sublist (filter-list char-alphabetic? li))
      (octave-sublist (filter-list (lambda (x) (or (eqv? x #\_) (eqv? x #\^))) li))
      (duration-sublist (filter-list (lambda (x) (or (eqv? x #\.) (char-numeric? x))) li))
    )
    (cond
      ((null? octave-sublist)
        (list
          (string->symbol (list->string notename-sublist))
          (string->symbol (list->string duration-sublist))
        )
      )
      (else
        (list
          (string->symbol (list->string notename-sublist))
          (string->symbol (list->string octave-sublist))
          (string->symbol (list->string duration-sublist))
        )
      )
    )
  )
)

;; (make-chord-or-xuplet-note-intermediate* seperator list) => list
;; Example: c+e+g_8 => '(+ ((c) (e) (g _)) 8)
;;          g-c-e^2 => '(- ((g) (c) (e ^)) 8)
(define (make-chord-or-xuplet-note-intermediate* sep li)
  (define (make-note-leaf* li) ;; make a list (leaf) of one single note => list:symbol
    (let (
      (note-name-list (filter-list char-alphabetic? li))
      (octave-list (filter-list (lambda (x) (or (eqv? x #\^) (eqv? x #\_))) li))
      )
      (cond
      ((null? octave-list) (list (list-char->symbol note-name-list)))
      (else (list (list-char->symbol note-name-list)
                  (list-char->symbol octave-list)))
      )
    )
  )
  (define (process-notes-group* li sep) ;; process note group
    (let ((note-group (split-list li sep)))
      (map string->list (map list->string note-group))
    )
  )

  (let* (
    (isduration? (lambda (x) (or (char-numeric? x) (eqv? x #\.))))
    (note-group-char-list (remove-list isduration? li))
    (duration-char-list (filter-list isduration? li))
    (separator-symbol (cond ((eqv? sep #\+) '+) ((eqv? sep #\-) '-) (else #f)))
    (splitted-note-group-list (split-list note-group-char-list sep))
    )
    (list separator-symbol
          (map make-note-leaf* splitted-note-group-list)
          (list-char->symbol duration-char-list))
  )
)


;; TODO
(define (filter-note note)
  (let
    (
      (maybe-chord-note? (lambda (n)
        (cond ((memv #\+ (tokenize-any n)) #t) (else #f))))
      (maybe-xuplet-note? (lambda (n)
        (cond ((memv #\- (tokenize-any n)) #t) (else #f))))
      (maybe-rest-note? (lambda (n)
        (cond
          ((memv #\r (tokenize-any n)) #t)
          ((memv #\R (tokenize-any n)) #t)
          (else #f))))
      (maybe-silence-note? (lambda (n)
        (cond
          ((memv #\S (tokenize-any n)) #t)
          ((memv #\S (tokenize-any n)) #t)
          (else #f))))
      (filter-rest-note (lambda (li)
        (list (string->symbol (string (car li))) (list->string (cdr li)))))
      (filter-silence-note (lambda (li)
        (list (string->symbol (string (car li))) (list->string (cdr li)))))
    )

    (cond
      ((maybe-rest-note? note) (filter-rest-note (tokenize-any note)))
      ((maybe-silence-note? note) (filter-silence-note (tokenize-any note)))
      (else '())
    )
  )
)

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

)