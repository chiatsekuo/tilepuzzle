# tilepuzzle - Sliding-Block Puzzle and Permutation Inversions

This is a CS3334 - Data Structures course project. It was completed by [Alex McVay](https://github.com/AlexanderLuasan), [Chia-Tse Kuo](https://github.com/chiatsekuo) , and [Andrew Park](https://github.com/psh320).

## Introduction

​	In the traditional 3 by 3 tile puzzle, the number of inversions is used to prove its
solvability. Looking at how each move changes the inversions of the puzzle, it is possible to
find when the tile puzzle can reach any other state. To calculate the inversions, we transform
the tiles row by row from a two-dimensional grid to a one-dimensional list. In this form, it is
easier to solve for the inversions of a state of puzzle. The inversions of the puzzle is a way to
represent how well the puzzle is solved.
Cancel changes
![image-20210819194415968](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_1.PNG)

Fig.1 Transform the 2-dimensional grid into 1-dimensional array

## Original Puzzle

​	Inversion Count for an array indicates that how distant the array is from being sorted. If
the array is already solved then inversion count is 0. If the array is sorted in reverse order, that
inversion count would be the maximum. For example, we assume an array “a[ ]”: If an integer
‘i’ is less than another ‘j’, and if a[i] is greater than a[j], there exist an inversion formed by
a[i] and a[j].
​	In this way, when the tiles are in solved state, the number of inversions is zero, and
when the tiles are in the complete opposite order, the inversions are at the maximum: 36. In
addition, the empty tile is always ignored when calculating the inversions in this game. Now,
we need the concept of polarity to study the solvability of the puzzle. Numbers have the same
polarity when they are both even or odd. A way to calculate this is to check if the mod 2 of
both numbers are the same.

​	These rules help prove the solvability of 3 by 3 puzzle by looking at how each move
changes the number of inversions. When making a move to the left or right, the number of
inversions does not change. Tiles can’t actually move past another tile when making these
horizontal moves. Only the empty tile and that target tile (this is the one clicked on) can be
swapped and they won’t change the number of inversion as the empty tile is ignored.

![image-20210819194724514](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_2.PNG)

Fig.2 No change of inversions when swapping tiles horizontally

​	This just leaves the vertical moves. Vertical moves on the grid translate to the swapping
of an empty tile and a tile 3 steps away, as a result it will move ahead or behind 2 other tiles
and this can change the inversions. However in all three possible cases, something special
happens. If both tiles were greater than the moving tile, then two inversions are removed or
added. If both were less than the moving tile, then two inversions are added. And if one is
greater and the other is less, then the inversion remain the same. As a result, the polarity of
the inversion in this puzzle can never change, because it always changes by two at a time.

![image-20210819194752864](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_3.PNG)

Fig.3 Since 5 and 6 are greater than 4, the inversions added 2, and become 2

![image-20210819194804120](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_4.PNG)

Fig.4 Since 2 and 3 are greater than 1, the inversions added 2, and become 4

## Variant Size and Board Design

​	For a puzzle with different dimension, it would be different specifically if the width is
an even number. In these cases, vertical moves make the tile swap with a different number of
tiles. In an even width game, the polarity changes with each vertical move. It is still possible
to find if the puzzle is solvable by examining which row the empty tile is in and the number
of rows away from the solved position. By counting the difference in rows the blank tile is
away from the correct position the polarity of the number of vertical moves can be calculated
as each vertical moves changes the polarity. With these two values it is possible to prove the
solvability of a state.
​	Now, let's take a look at this new tile sliding game. In this game, the board is filled with
tiles, so instead of moving an empty space around the board, the tiles are moved as a whole
row or column wrapping around the edge as if on a torus. The solvability of this puzzle can be
tackled and proved in a similar way to the original puzzle mentioned above. We will look at
the game of size 3 by 3 as an example.

![image-20210819194844206](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_5.PNG)

Fig.5 Unfold the torus into a flat sheet

![image-20210819194855564](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_6.PNG)

Fig.6 Solved state of the Wrap Around Board mode

​	First, we focus on the horizontal movement. Most tiles stay in the same order except one
tile that jumps past the rest of the tiles, and this particular tile is the one that wraps around the
edge of the board. This row rotation is similar to the vertical moves from the regular puzzle
because each tile move past two, meaning on the board with an odd width, the number of
inversions changes is always even, and therefore the polarity does not change.

![image-20210819194914143](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_7.PNG)

Fig.7 One horizontal move on the Wrap Around Board mode

​	Second, the vertical movement of tiles looks intimidating, but it can be divided into two
simpler steps. First, look at the tiles that don’t leave the board. Each one just moves like the
regular game, passing two other tiles making the change in polarity even. Since there are two
tiles that are performing the movement together simultaneously, they don’t actually change
the polarity. The tile that moves off the board jumps past a number of tiles: ones on the same
row and to the left, all non-moving tiles in the middle row, tiles on the left on the bottom row,
and also both moving tiles. This in 3 by 3 case that is always 6 giving an even number of
inversions or in general (height -1) * width of the board, so as long as the height is odd or the
width is even the move will also maintain polarity.

![image-20210819194933713](https://github.com/chiatsekuo/tilepuzzle/blob/master/assets/fig_8.PNG)

Fig.8 One vertical move on the Wrap Around Board mode

​	When looking at boards of other sizes, it starts to get complicated. For instance,
expanding to a 4 by 4 grid, each move flips the polarity of the inversions. When making
horizontal moves, each move takes one tile past three and vertical moves takes 3 tiles past 3
and 1 tile past 12 this all ensures that each move switches the polarity. From playing around
with the board I have a suspension that every state is possible because there seems to be ways
to solve all but two tiles that are right next to each other. That is normally impossible with
other versions of the game and may be proof that it could be possible to create any format of
the board however I currently don’t have the proof to show each state is possible.

## AI Solving Method

​	As oppose to the solvability of the puzzles, the solutions cannot be determined by the
number of inversions. In order to look into the solution of the puzzle, a small side project in
this program is a way to solve the puzzle automatically. This is handled by a simple search
algorithm. The algorithm uses two lists of game states to search for a possible solution.
Initially an Open list is filled with the starting state then each round of searching begins by
selecting a state in the Open list that is closest to the solved state by Manhattan distance and
also has a low number of moves from the initial position. The chosen state is moved to the
closed list and every move from the state is added to the Open list. This process is repeated
until the solved state is found in the closed list then the algorithm can calculate the states
backwards to find the step by step solution.

## Reference

- Mark Ryan (2004) Solvability of the Tiles Game, Available at:
  https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
- Paul E. Black, "Manhattan distance", in Dictionary of Algorithms and Data Structures
  [online], Paul E. Black, ed. 11 February 2019. (accessed TODAY) Available
  from: https://www.nist.gov/dads/HTML/manhattanDistance.html

