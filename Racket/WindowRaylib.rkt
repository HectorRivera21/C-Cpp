#lang racket

(require raylib/2d/unsafe)

(define FRAME (/ 1 60))
(define dt FRAME)
(define screen-width 800)
(define screen-height 600)

(define (initialize-game)
  ;; Initialize game resources and variables here
  (InitWindow screen-width screen-height "Window Test")
  (SetTargetFPS 60))

(define (cleanup-game)
  ;; Unload game resources and close the window
  (CloseWindow))

(define (game-loop)
  (define square-pos (make-Vector2 100.0 100.0))  ; Initialize the square position
  (let loop ()
    (when (not (WindowShouldClose))
      (update-game square-pos)  ; Update game state
      (draw-game square-pos)    ; Draw game
      (sleep (/ 1 60.0))
      (loop))))

(define (clamp value min-value max-value)
  (min max-value (max min-value value)))

(define (update-square pos dt)
  ;; Update square position based on user input
  (let* ((speed 250))
    (when (IsKeyDown KEY_A)
      (set-Vector2-x! pos (- (Vector2-x pos) (* speed dt))))
    (when (IsKeyDown KEY_D)
      (set-Vector2-x! pos (+ (Vector2-x pos) (* speed dt))))
    (when (IsKeyDown KEY_W)
      (set-Vector2-y! pos (- (Vector2-y pos) (* speed dt))))
    (when (IsKeyDown KEY_S)
      (set-Vector2-y! pos (+ (Vector2-y pos) (* speed dt))))

    ;; Ensure the square stays within the screen bounds
    (set-Vector2-x! pos (clamp (Vector2-x pos) 0.0 (- screen-width 50.0)))
    (set-Vector2-y! pos (clamp (Vector2-y pos) 0.0 (- screen-height 50.0)))))

(define (update-game square-pos)
  ;; Update game state
  (set! dt (min FRAME (GetFrameTime)))
  (update-square square-pos dt)
  )

(define (draw-game square-pos)
  ;; Draw game
  (BeginDrawing)
  (ClearBackground BLACK)

  ;; Draw the square
  (DrawRectangleV square-pos (make-Vector2 52.0 52.0) WHITE)

  (EndDrawing))

(define (main)
  (initialize-game)  ; Initialize the game

  (game-loop)  ; Enter the game loop

  (cleanup-game))  ; Clean up and close the game

(main)  ; Start the game
