

;; Filter the list
;; (filter-list predicate list) ==> list
(define (filter-list pred? li)
  (cond
    ((null? li) '())
    ((pred? (car li)) (cons (car li) (filter-list pred? (cdr li))))
    (else (filter-list pred? (cdr li)))
  )
)

;; Tokenize symbol or string into a list of char
;; (tokenize-any symbol) ==> list char
(define (tokenize-any sym)
  (cond
    ((symbol? sym) (string->list (symbol->string sym)))
    ((string? sym) (string->list note))
    (else '())
  )
)

;; Merge list of things into string, merge the elements satisfying the predicate
;; (merge-list-element predicate? list_char) => list_string
;; Example:
;;  (merge-list-element char-numeric? '(#\0 #\1 #\2 #\a #\b)) => '("012" "a" "b")
(define (merge-list-element pred? li)

)

;; Returns the last element of the list
;; (list-last list) => atom
(define (list-last li) (car (reverse li)))


;; Tests