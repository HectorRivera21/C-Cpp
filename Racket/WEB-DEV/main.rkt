#lang web-server/insta

(define (start request)
    (response/xexpr
    '(html (head(title"Example WebSite"))
    (body(h1 "Currently UnderConstruction")))))

