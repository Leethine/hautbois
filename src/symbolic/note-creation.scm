;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Takes scheme style notes and create hautbois C++ style code
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(load "note-structure.scm")
(load "note-symbols-en.scm")

;; Define language 
(define language)


;; Set language for lilypond-style notation
;; Ex:
;;   (set-lang! 'en)
;;   (set-lang! 'it)
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

;; Convert lilypond-style symbol to hautbois-style string
;; (note-symbol->str symbol) => str
;; Ex:
;;  (note-symbol->str 'c) ==> "C"
(define (note-symbol->str symbol)
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
  (cond
    ((eq? language 'en) (note-symbol->str* symbol en-note-name-map))
    ((eq? language 'it) (note-symbol->str* symbol it-note-name-map))
    ((eq? language 'fr) (note-symbol->str* symbol fr-note-name-map))
    ;; more languages
    (else #f)
  )
)

;; Convert lilypond-scheme-style octave symbol to numeric string
;; (octave-symbol->str symbol) => str
;; Ex:
;;  (octave-symbol->str '^) ==> "4"
;;  (octave-symbol->str '()) ==> "3"
;;  (octave-symbol->str '__) ==> "1"
(define (octave-symbol->str symbol)
'()
)

;; Check if a symbol is note
(define (is-note-symbol? symbol)
  (define (is-note-symbol?* sym all-note-name)
    (let*
      ((sublist (memq sym all-note-name)))
      (cond
        ((null? sublist) #f)
        ((eq? sublist #f) #f)
        (else #t)
      )
    )
  )
  (cond
    ((not (symbol? symbol)) #f)
    ((eq? language 'en) (is-note-symbol?* symbol all-en-note-name))
    ((eq? language 'it) (is-note-symbol?* symbol all-it-note-name))
    ((eq? language 'fr) (is-note-symbol?* symbol all-fr-note-name))
    ;; more languages
    (else #f)
  )
)

;; Check if a symbol represents octave
(define (is-octave-symbol? symbol)
  (define (compare-list? ch li)
    (cond
      ((null? (cdr li)) (eqv? (car li) ch))
      ((not (eqv? ch (car li))) #f)
      (else (compare-list? ch (cdr li)))
    )
  )
  (let*
    (
      (tokenized-list (tokenize-any symbol))
      (first-char (if (null? tokenized-list) '() (car tokenized-list)))
    )
    (cond
      ((null? first-char) #f)
      ((and (eqv? first-char #\_) (> (length tokenized-list) 3)) #f)
      ((and (eqv? first-char #\^) (> (length tokenized-list) 5)) #f)
      ((eqv? first-char #\^) (compare-list? #\^ tokenized-list))
      ((eqv? first-char #\_) (compare-list? #\_ tokenized-list))
      (else #f)
    )
  )
)
