%%%% Author:      Ryan Florida
%%%% Program:     Project 5
%%%% Due Date:    March 29, 2017
%%%% Description: Implement six functions specified by the instructor, as well
%%%%              as attempt to solve a puzzle.


%Problem 1: Test to see if a particular value is in a given list.
%base case:
mymember(Value, [Value|Tail]).
%Recursive step:
mymember(Value, [Head|Tail]):-
    mymember(Value,Tail).

%Problem 2: Test a number to see if it has even parity.
%base case:
myeven(0).
%Recursive step:
myeven(A_number):-
    (A_number > 0 -> New_number is A_number - 2; New_number is -A_number - 2),
    New_number >= 0,
    myeven(New_number).

%Problem 3: Print even member of a list.
%base case:
%myevennumber(A_number, [A_number]).
%Recursive step:
myevennumber(A_number,[Head|Tail]):-
    myeven(Head) -> A_number is Head; myevennumber(A_number, Tail),
    myevennumber(A_number, Tail).

%Problem 4: Identify minimum value in a list.
%base case:
myminlist([Min], Min).
%Recursive steps:
myminlist([Head, Next|Tail], Min):-
    Head =< Next,
    myminlist([Head|Tail], Min).
myminlist([Head, Next|Tail], Min):-
    Head > Next,
    myminlist([Next|Tail], Min).

%Problem 4, alternate version (Because on the program description it says max).
%           Identifies maximum value in a list.
%base case:
mymaxlist([Max], Max).
%Recursive steps:
mymaxlist([Head, Next|Tail], Max):-
    Head >= Next,
    mymaxlist([Head|Tail], Max).
mymaxlist([Head, Next|Tail], Max):-
    Head < Next,
    mymaxlist([Next|Tail], Max).

%Problem 5: Returns true if the entered list was a palindrome, otherwise false.
%base cases:
palindrome([]).
palindrome([_]).
%Recursive step:
palindrome(List):-
    reverseList(List,List).
%The reverseList function will reverse the current list.
reverseList(List1, List2):-
    rvrsList(List1, [], List2).
rvrsList([], List, List).
rvrsList([Head|Tail], X, Y):-
    rvrsList(Tail, [Head|X], Y).

%Problem 6: Count leaf nodes in a given tree.
%base cases:
leafcount(nil,0).
leafcount(t(_,nil,nil),1).
%Recursive steps:
leafcount(t(_,L,nil),N):-
    L = t(_,_,_),
    leafcount(L,N).
leafcount(t(_,nil,R),N):-
    R = t(_,_,_),
    leafcount(R,N).
leafcount(t(_,L,R),N):-
    L = t(_,_,_),
    R = t(_,_,_),
    leafcount(L,NL),
    leafcount(R,NR),
    N is NL + NR.
