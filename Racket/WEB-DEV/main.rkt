#lang racket
(require web-server/servlet
         web-server/servlet-env
         web-server/formlets)

(define counter (make-parameter 0))

(define (increment)
  (parameterize ([counter (+ (counter) 1)])
    (counter)))

(define (decrement)
  (parameterize ([counter (- (counter) 1)])
    (counter)))

(define (start request)
  (define (make-button label name)
    `(button ((type "submit") (name ,name)) ,label))

  (cond
    ((equal? (request-method request) 'GET)
     (response/xexpr
      `(html (head (title "Counter App"))
             (body ((style "background-color: black; color: white; text-align: center; font-size: 24px;"))
                   (h1 "Counter App")
                   (form ((method "post"))
                         (p "Counter value: " ,(number->string (counter)))
                         ,(make-button "Increment" "action" "increment")
                         ,(make-button "Decrement" "action" "decrement"))))))
    
    ((equal? (request-method request) 'POST)
     (let ((action `(form-value/single 'action request)))
       (cond
         ((string=? action "increment") (increment))
         ((string=? action "decrement") (decrement))
         (else (void))))
     (start request))))

(serve/servlet start
               #:servlet-path "/"
               #:port 8080)