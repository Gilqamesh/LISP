(define list (lambda (. args) args))
(define append (lambda (. lists)
  (define append-two (lambda (l1 l2)
    (if (eq? l1 '())
        l2
        (cons (car l1) (append-two (cdr l1) l2)))))
  (if (eq? '() lists)
      '()
      (if (eq? '() (car lists))
          '()
          (if (eq? (cdr lists) '())
              (car lists)
              (begin (display "hello: " (cdr lists))
                     (append-two (car lists) (apply append (cdr lists)))))))))
(define and (macro (. args)
  (define and-helper (lambda (rem)
    (if (eq? type-nil (typeof rem))
        #t
        (if (eval (car rem))
            (and-helper (cdr rem))
            #f))))
  (and-helper args)))
(define or (macro (. args)
  (define or-helper (lambda (rem)
    (if (eq? type-nil (typeof rem))
        #f
        (if (eval (car rem))
            #t
            (or-helper (cdr rem))))))
  (or-helper args)))
(define map
  (lambda (f l)
    (if (eq? type-nil (typeof l))
        '()
        (cons (f (car l)) (map f (cdr l))))))

(define quasiquote (macro (x)
  (if (eq? type-cons (typeof x))
      (append (list 'quasiquote) (map quasiquote x))
; (define call
;   (lambda (symbol-name ret-type param-type-arg-pairs)
;     (ffi-call (ffi ret-type