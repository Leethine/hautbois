;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Takes scheme style notes and create hautbois C++ style code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(load "note-structure.scm")
(load "note-symbols-en.scm")

;; Define language here 
(define language)

(define (set-lang! newlang)
  (let ((available-lang '(en))) ;; can add more languages in the list
    (cond
      ((memq newlang available-lang) (set! language newlang))
      (else
        (begin
          (display 
            (string-append
              "Language \"" (symbol->string newlang) "\" is not supported yet!" (make-string 1 #\newline)
            )
          )
        (exit)
        )
      )
    )
  )
)

(define (note-symbol->str* symbol symbol-map)
  (letrec
    ((get-val
      (lambda (elem alist)
        (if (eq? (car (car alist)) elem)
          (cdr (car alist))
          (get-val elem (cdr alist)))))
    (has-val
      (lambda (elem alist)
        (cond ((eq? alist '()) #f)
            ((eq? (car (car alist)) elem) #t)
            (else (has-val elem (cdr alist)))))))
    (if
      (has-val symbol symbol-map)
      (get-val symbol symbol-map)
      ""
    )
  )
)

(define (note-symbol->str symbol)
  (cond
    ((eq? language 'en) (note-symbol->str* symbol en-note-name-map))
    ;; more languages
    (else #f)
  )
)

(define (is-note-symbol? symbol)
  (define (is-note-symbol?* symbol all-note-name)
    (letrec* (
      (getsublist (lambda (x)
        (cond
          ((symbol? x) (memq x all-note-name))
          (else '()))
        )))
      (cond
        ((null? (getsublist symbol)) #f)
        (else #t)
      )
    )
  )

  (cond
    ((eq? language 'en) (is-note-symbol?* symbol all-en-note-name))
    ;; more languages
    (else #f)
  )
)

(define (is-octave-symbol? symbol)
  (define (compare-list? ch li)
    (cond
      ((> (length li) 5) #f)
      ((null? (cdr li)) (eqv? (car li) ch))
      ((not (eqv? ch (car li))) #f)
      (else (compare-list? ch (cdr li)))
    )
  )
  (letrec*
    (
      (tokenized-list (tokenize-any symbol))
      (first-char (car tokenized-list))
    )
    (cond
      ((eqv? first-char #\^) (compare-list? #\^ tokenized-list))
      ((eqv? first-char #\_) (compare-list? #\_ tokenized-list))
      (else #f)
    )
  )
)

;; Test
(begin

(set-lang! 'en)

(display
(symbol? (car (filter-note 'r4)))
)

(display
(is-note-symbol? (car (filter-note 'r4)))
)

(display
(note-symbol->str (car (filter-note 'r4)))
)

(display
(filter-note 'r4.)
)

(display #\newline)

)