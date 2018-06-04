#lang racket
;;;;***************************************************************************
;;;;constant representing an approximation for pi.
(define pi 3.14159)
;;;;Calculates the volume of a sphere with radius r.
(define (sphereVolume r)
    (* (/ 4 3) pi r r r)
)

;;;;***************************************************************************
;;;;Definition of exponentiation. Raises A to the Bth power.
(define (power A B)
    (cond
         [(or (= A 1) (= B 0)) 1]
         [else (* A (power A (- B 1)))]
    )
)

;;;;***************************************************************************
;;;;This function counts the number of zeros in the input list.
(define (countZero list)
    (cond
      [(null? list) 0]
      [(zero? (car list)) (+ 1 (countZero (cdr list)))]
      [else (countZero (cdr list))]
    )
)

;;;;***************************************************************************
;;;;This function reverses the order of the elements in the input list.
(define (reverse list)
    (if (null? list) '()
        [append (reverse (cdr list)) (cons (car list) '())]
    )
)

;;;;***************************************************************************
;;;;This function searches through the list for the maximum and minimum
;;;;elements and then returns them in a new list. Output is (max, min).
(define (findEnds List)
    (cond
        [(null? List) '()]
        [(null? (cdr List)) (list (car List) (car List))]
        [else
            (let ((remainingElements (findEnds (cdr List)))(firstElement (car List)))
                 (cond
                     [(> firstElement (car remainingElements)) (cons firstElement (cdr remainingElements))]
                     [(< firstElement (car remainingElements)) (list (car remainingElements) firstElement)]
                     [else remainingElements]
                 )
             )
         ]
    )
)

;;;;***************************************************************************
;;;;This function searches through a list for a specified atom, atom1 in this
;;;;case, and replaces each instance of said atom with a designated atom, atom2
;;;;in this case.
(define (replace atom1 atome2 List)
    (cond
        [(null? List) List]
        [(eq? (car List) atom1) (cons atome2 (replace atom1 atome2 (cdr List)))]
        [else (cons (car List) (replace atom1 atome2 (cdr List)))]
    )
)
