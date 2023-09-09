

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

;; Merge list of things into string, merge the elements satisfying the predicate
;; (merge-list-element predicate? list_char) => list_string
;; Example:
;;  (merge-list-element char-numeric? '(#\0 #\1 #\2 #\a #\b)) => '("012" "a" "b")
(define (merge-list-element pred? li)
;; TODO
'()
)

;; Convert list of characters to symbol
(define (list-char->symbol li)
  (string->symbol (list->string li))
)

;; Returns the last element of the list
;; (list-last list) => atom
(define (list-last li) (car (reverse li)))

;; Split a list based on an atom provided
;; (split-list list separator) => list
;; Ex: (split-list '(1 2 + 3 4) '+) => ((1 2) (3 4))
(define (split-list li sep)
  (define (split-first! li sep) ;; split at the first occurance of separator
    (letrec (
      (split-first-reversed
        (lambda (li sep)
          (cond
          ((null? li) '())
          ((equal? (car li) sep) (list (cdr li)))
          (else
            (cons (car li) (split-first-reversed (cdr li) sep)))
          )
        )
      ))
      (let ((result (split-first-reversed li sep)))
        (append
          (list (reverse (cdr (reverse result))))
          (list-last result)
        )
      )
    )
  )
  (define (split-first li sep) ;; check if separator exists
    (if (eq? (member sep li) #f)
      (list li)
      (split-first! li sep)
    )
  )

  (define (split-list* res li sep) ;; iterative method
    (cond
      ((null? li) res)
      ((list? (car li)) (split-list* (cons (car li) res) (cdr li) sep))
      (else
        (split-list* res (split-first li sep) sep)
      )
    )
  )

  (if (equal? (car li) sep)
  (reverse (split-list* '() (cdr li) sep))
  (reverse (split-list* '() li sep))
  )
)


;; Tests