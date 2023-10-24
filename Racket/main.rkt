#lang racket

(define(fib n)
	(if(or (= n 0) (= n 1))
		n
		(+ (fib(- n 1)) (fib(- n 2)))
	)
)
(define (print_fib n)
  (define (helper current max)
		(print (fib current))
		(when (<= current max)
    	(display ", ")
			(helper (+ current 1) max)
		)
	)
  (helper 0 n)
)

(define (factorial n)
  (if (= n 0)
      1
      (* n (factorial (- n 1)))
	)
)


(for ([i (in-range 1 6)])   ; Loop variable i in the range [1, 6)
  (displayln i))          ; Display each value of i on a new line


(print_fib 12)
(displayln " ")

(define v (vector 1 2 3 4 5))
(define idx (vector-ref v 2))
(println idx)

(define p 6)

(if (< p 10) 
	(displayln "x is less than 10")
	(displayln "x is greater than 10")
)

(set! p 10)

(cond
  [(< p 10) (displayln "x is less than 10")]
  [(= p 10) (displayln "x is equal to 10")]
  [else (displayln "x is greater than 10")])

(define x 5)
(define y 10)

(if (> x y)
	(begin
      (set! x (+ x 5))
      (displayln "Adding 5 to x")
      (displayln x))
    (begin
      (displayln "x is not greater than y")
      (set! x (- x 3))
      (displayln "Subtracting 3 from x")))


(displayln "Updated x: ")
(display x)
