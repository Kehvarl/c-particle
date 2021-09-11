# Particle Simulation
## Usage
  * `particles --help` for detailed instructions
  * `particles` to run in interactive mode
  * `particles < input_file` to provide a prepared test file

## Compate to known output (linux/bash)
  * `diff -u input_file <(particles < output_file)`

## Testing
  * `test.sh` is a bash script to run a few simple tests


## Problem Statement
Your goal is to write a small particle simulation in C to show how little rocks would fall in a 2D world. Your program should load a model of the simulation state from STDIN. It should then determine how, under the effects of gravity, any loose rocks would fall. Finally, it should write the resulting state to STDOUT.
Input Format

### Inputs
The first line of input will be two integers, separated by a space. These will specify the number of cells in your simulation (width and height, respectively).

After this, each line of input describes one row of cells in your simulation, using the following text representation.

Each character should be one of the following:
  '.' one single rock
  ':' two rocks
  ' ' empty space, into which rocks may fall
  'T' table, through which rocks may not fall

Tables themselves never fall; they are securely fixed in place. As implied above, rocks may stack up to two into a space.

## Example Input and Output
Input:
7 4
.....::
.T    :
 ..T .:
  .   :

Output:
 .    :
 T .  :
  .T .:
:.: .::
