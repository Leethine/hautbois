;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;  Algorithms for hautbois symbolic module
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Filter the list so that all elements satisfy the predicate
;; (filter-list predicate list) ==> list
(define (filter-list pred? li)
  (cond
    ((null? li) '())
    ((pred? (car li)) (cons (car li) (filter-list pred? (cdr li))))
    (else (filter-list pred? (cdr li)))
  )
)

;; Remove all elements satisfying the predicate from the list
;; (remove-list predicate list) ==> list
(define (remove-list pred? li)
  (cond
    ((null? li) '())
    ((not (pred? (car li))) (cons (car li) (remove-list pred? (cdr li))))
    (else (remove-list pred? (cdr li)))
  )
)

;; Tokenize symbol or string into a list of char
;; (tokenize-any symbol) ==> list char
(define (tokenize-any sym)
  (cond
    ((symbol? sym) (string->list (symbol->string sym)))
    ((string? sym) (string->list sym))
    (else '())
  )
)

;; Convert list of characters to symbol
(define (list-char->symbol li)
  (string->symbol (list->string li))
)

;; Returns the last element of the list
;; (list-last list) => atom
(define (list-last li) (car (reverse li)))

;; Split a list based on an atom provided
;; (split-list list delimiter) => list
;; Ex: (split-list '(1 2 + 3 4) '+) => ((1 2) (3 4))
(define (split-list li delim)
  (define (split-first! li delim) ;; split at the first occurance of delimiter
    (letrec (
      (split-first-reversed
        (lambda (li delim)
          (cond
          ((null? li) '())
          ((equal? (car li) delim) (list (cdr li)))
          (else
            (cons (car li) (split-first-reversed (cdr li) delim)))
          )
        )
      ))
      (let ((result (split-first-reversed li delim)))
        (append
          (list (reverse (cdr (reverse result))))
          (list-last result)
        )
      )
    )
  )
  (define (split-first li delim) ;; check if delimiter exists
    (if (eq? (member delim li) #f)
      (list li)
      (split-first! li delim)
    )
  )

  (define (split-list* res li delim) ;; iterative method
    (cond
      ((null? li) res)
      ((list? (car li)) (split-list* (cons (car li) res) (cdr li) delim))
      (else
        (split-list* res (split-first li delim) delim)
      )
    )
  )

  (if (equal? (car li) delim)
    (reverse (split-list* '() (cdr li) delim))
    (reverse (split-list* '() li delim))
  )
)

;; Merge list of things into string, merge the elements satisfying the predicate
;; (merge-list-element predicate? list_char) => list_string
;; Example:
;;  (merge-list-element char-numeric? '(#\0 #\1 #\2 #\a #\b)) => '("012" "a" "b")
(define (merge-list-element pred? li)
;; TODO
'()
)