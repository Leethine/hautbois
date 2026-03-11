;; Lilypond library
;; Tested with TinyScheme
;; @ Hautbois Project


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Procedures for string and char array
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Split a string under the condition char-delimiter?
(define (string-split char-delimiter? string)
  (define (maybe-add a b parts)
    (if (= a b) parts (cons (substring string a b) parts)))
  (let ((n (string-length string)))
    (let loop ((a 0) (b 0) (parts '()))
      (if (< b n)
          (if (not (char-delimiter? (string-ref string b)))
              (loop a (+ b 1) parts)
              (loop (+ b 1) (+ b 1) (maybe-add a b parts)))
          (reverse (maybe-add a b parts))))))

;; Filter list of char, keep all chars where char-delimiter? is fulfilled
(define (list-char-filter char-delimiter? lst)
  (cond
    ((null? lst) '())
    ((char-delimiter? (car lst)) (cons (car lst) (list-char-filter char-delimiter? (cdr lst))))
    (else (list-char-filter char-delimiter? (cdr lst)))))

;; Filter string, keep the char that fulfills char-delimiter?
(define (string-filter char-delimiter? string)
  (let ((lst (string->list string)))
    (list->string (list-char-filter char-delimiter? lst))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Procedures for parsing lilypond symbols
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Split lilypond single note into 2 tokens
;; e.g. "sol'''4." ==> ("sol'''" "4.")
(define (ly-singlenote-split2 tokenstr)
  (let ((tokenlist (string->list tokenstr))
    (char-pitch? (lambda (a) (if (or (char-alphabetic? a) (char=? a #\,) (char=? a #\')) #t #f)))
    (char-duration? (lambda (a) (if (or (char-numeric? a) (char=? a #\.)) #t #f))))
    (list
      (list->string (list-char-filter char-pitch? tokenlist))
      (list->string (list-char-filter char-duration? tokenlist))
    )))

;; Split lilypond single note into 3 tokens
;; e.g. "sol'''4." ==> ("sol" "'''" "4.")
(define (ly-singlenote-split3 tokenstr)
  (let ((tokenlist (string->list tokenstr))
    (char-octave? (lambda (a) (if (or (char=? a #\,) (char=? a #\')) #t #f)))
    (char-duration? (lambda (a) (if (or (char-numeric? a) (char=? a #\.)) #t #f))))
    (list 
      (list->string (list-char-filter char-alphabetic? tokenlist))
      (list->string (list-char-filter char-octave? tokenlist))
      (list->string (list-char-filter char-duration? tokenlist)))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;
;; Input/Output
;;;;;;;;;;;;;;;;;;;;;

;;; Read from file, returns list of tokens
(define (read-token->list filename)
  (let ((file (open-input-file "test.txt")))
    (let loop ((token (read file)))
      (cond 
        ((eof-object? token) (close-input-port file) '())
        (else (cons token (loop (read file))))))))

