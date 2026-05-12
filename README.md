# 42sh

Our project 42SH is a recreation of a Unix SHELL based on **TCSH**, coded entirely in **C**.  
We implemented all the **TCSH** supported features, except for **command group** and **command substitution**.  

This project was completed over the course of 5 weeks by our team of 5, divided into groups.


-----------------
## Usage

Compile our project with :

```bash
make
```

And run our shell with :

```bash
./42sh
```

Once inside the shell, you can try classic TCSH supported command and our builtin commands.  


--- 
## Builtin commands

- cd
- env
- setenv
- unsetenv
- alias
- history


We implemented bonus builtin commands in our shell as well.

#### Accessible by :

Compiling with :

```bash
make bonus
```

And running with :
```bash
./42
```

## Bonus builtin commands

Below you will find a table containing the command and it's description.

| Commands   |          Description          |
|----------|:-----------------------------:|
| pelophylax | short description about frogs |
| flipcoin |        coin simulation        |
| throwdice |        dice simulation        |
| hangman |         play hangman          |
| tictactoe |       play Tic Tac Toe        |
| guessnumber |     guess a random number     |
| mambo |       play mambo sound        |
| yippee |       play yippee sound       |


## Tests

Unit tests are available as well, see the coverage by :

```bash
make tests_run
```

### For more help:
Try the command with help flag to have a longer help about the command.

```bash
the_command -h
```
or 
```bash
the_command --help
```

## Authors

name 1  
name 2  
name 3  
name 4  
name 5  

-----------