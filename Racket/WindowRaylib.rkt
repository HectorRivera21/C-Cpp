#lang racket

(require raylib/2d/unsafe)

(define FRAME (/ 1 60))
(define dt FRAME)
(define screen-width 800)
(define screen-height 600)

(define (initialize-game)
  ;; Initialize game resources and variables here
  (InitWindow screen-width screen-height "Moonshot")
  (SetTargetFPS 60))

(define (clamp value min-value max-value)
  (min max-value (max min-value value)))

(define (cleanup-game)
  ;; Unload game resources and close the window
  (CloseWindow))

(define (game-loop)
  (let loop ()
    (when (not (WindowShouldClose))
      (update-game)  ; Update game state
      (draw-game)    ; Draw game
      (sleep (/ 1 60.0))
      (loop))))

(define (update-square square-pos dt)
  ;; Update square position based on user input
  (let* ((speed 5))
    (cond [(IsKeyDown KEY_A)
      (set-Vector2-x! square-pos (- (Vector2-x square-pos) (* speed dt)))])
    ([(IsKeyDown KEY_D)
      (set-Vector2-x! square-pos (+ (Vector2-x square-pos) (* speed dt)))])
    ([(IsKeyDown KEY_W)
      (set-Vector2-y! square-pos (- (Vector2-y square-pos) (* speed dt)))])
    ([(IsKeyDown KEY_S)
      (set-Vector2-y! square-pos (+ (Vector2-y square-pos) (* speed dt)))])

    ;; Ensure the square stays within the screen bounds
    (set-Vector2-x! square-pos (clamp (Vector2-x square-pos) 0.0 (- screen-width 50.0)))
    (set-Vector2-y! square-pos (clamp (Vector2-y square-pos) 0.0 (- screen-height 50.0)))))


(define (update-game)
  ;; Update game state
  (set! dt (min FRAME (GetFrameTime)))
  (define x 1)
  (when (<= x 0)
    (update-square (make-Vector2 100.0 100.0) dt))  ; Update square position
  (set! x 15)
  ; Other game logic...
  )

(define (draw-game)
  ;; Draw game
  (BeginDrawing)
  (ClearBackground BLACK)

  ;; Draw the square
  (let ((square-pos (make-Vector2 100.0 100.0))
        (square-size (make-Vector2 50.0 50.0))
        (square-color WHITE))
    (DrawRectangleV (make-Vector2 (Vector2-x square-pos) (Vector2-y square-pos))
                    (make-Vector2 (Vector2-x square-size) (Vector2-y square-size))
                    square-color))

  (EndDrawing))

(define (main)
  (initialize-game)  ; Initialize the game

  (game-loop)  ; Enter the game loop

  (cleanup-game))  ; Clean up and close the game

(main)  ; Start the game
