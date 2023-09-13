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


;; Convert number+dot notation of duration to rational notation
;; (number+dot->rat duration-list) ==> rational number
;;  Ex: (number+dot->rat '(#\4 #\.)) ==> 3/8
(define (number+dot->rat duration-li)
  (define (number+dot->rat* denom dots)
    (if (null? dots)
      (/ 1 denom)
      (+ (/ 1 denom) (number+dot->rat* (* 2 denom) (cdr dots)))
    )
  )
  (let
    ((denom (string->number (list->string (remove-list (lambda (x) (eqv? x #\.)) duration-li))))
    (dots (filter-list (lambda (x) (eqv? x #\.)) duration-li)))
    (number+dot->rat* denom dots)
  )
)

;; (make-rest-or-silence-note-intermediate* list_char) => list symbol
(define (make-rest-or-silence-note-intermediate* li)
  (list (string->symbol (string (car li))) (number+dot->rat (cdr li))))

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
          (number+dot->rat duration-sublist)
        )
      )
      (else
        (list
          (string->symbol (list->string notename-sublist))
          (string->symbol (list->string octave-sublist))
          (number+dot->rat duration-sublist)
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
          (number+dot->rat duration-char-list))
  )
)

;; Take any note symbol and convert to intermediate note representation
;; (note-symbol->IR note-symbol)
;; Ex:
;;  (note-symbol->IR 'css^4) ==> '(css ^ 4)
;;  (note-symbol->IR 'r8.) ==> (r 8.)
;;  (note-symbol->IR 's2.) ==> (s 2.)
;;  (note-symbol->IR 'cf^-ess^^-g__4) ==> (- ((cf ^) (ess ^^) (g __)) 4)
;;  (note-symbol->IR 'css^+ex_+g__4.) ==> (+ ((css ^) (ex _) (g __)) 4.)
(define (note-symbol->IR note)
  (let*
    (
      (tokenized-note (tokenize-any note))
      (maybe-chord-note? (lambda (n)
        (cond ((memv #\+ n) #t) (else #f))))
      (maybe-xuplet-note? (lambda (n)
        (cond ((memv #\- n) #t) (else #f))))
      (maybe-rest-or-silence-note? (lambda (n)
        (cond
          ((eqv? #\r (car n)) #t)
          ((eqv? #\R (car n)) #t)
          ((eqv? #\s (car n)) #t)
          ((eqv? #\S (car n)) #t)
          (else #f))))
    )
    (cond
      ((maybe-rest-or-silence-note? tokenized-note)
        (make-rest-or-silence-note-intermediate* tokenized-note))
      ((maybe-chord-note? tokenized-note)
        (make-chord-or-xuplet-note-intermediate* #\+ tokenized-note))
      ((maybe-xuplet-note? tokenized-note)
        (make-chord-or-xuplet-note-intermediate* #\- tokenized-note))
      (else
        (make-single-note-intermediate* tokenized-note)
      )
    )
  )
)
