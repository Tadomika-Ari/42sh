# 42sh

Our project 42SH is a recreation of a Unix SHELL based on **TCSH**, written entirely in **C**.  
For this project we chose the shell base created by one of our team members, Alcibiade Streit-Soumaila.  
And implemented a large part of **TCSH** supported features, except for **command group** and **command substitution**.  

This project was completed over the course of 5 weeks by our team of 5, divided into groups.


-----------------
## Features

- Command execution
- PATH handling
- Environment variable management
- Pipes
- Redirections
- Command separators (;)
- Job control (&&, ||)
- Parenthesis
- Inhibitors
- History management
- Aliases
- Signal handling
- Builtin commands
- Error handling
- If
- Foreach
- Which
- Where
- Scripting


## Usage

Compile our project with :

```bash
make
```

And run our shell with :

```bash
./42sh
```

Once inside the shell, you can try classic TCSH supported commands and our builtin commands.

---

## Builtin commands

- cd
- env
- setenv
- unsetenv
- alias
- history
- set
- unset
- if
- repeat
- foreach
- where
- which
- jobs
- fg
- bg
- exit

We implemented bonus builtin commands in our shell as well.

#### Accessible by :

Compiling with :

```bash
make bonus
```

And running with :
```bash
./42sh
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


---
## Project structure

Our functions are in a src folder and then divided in folders organized by features :

```text
src  
 |_src/alias  
 |_src/autocompletion/  
 |_src/bonus/  
 |_src/built_in/  
 |_src/command_utilities/  
 |_src/error/  
 |_src/free/  
 |_src/history/  
 |_src/initialisation/  
 |_src/jobs/  
 |_src/loop_tcsh/  
 |_src/redirection/  
 |_src/repeat/  
 |_src/tools/  
 |_src/user/  
 |_src/var_interpreters/  
 ```

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

Alcibiade Streit Soumaila -> dev
Alessendro Paris -> dev, tester  
Galya Packer -> dev, tester  
Ugo Pascallon -> dev, scrum master  
Lucas Eeckhoutte -> dev

-----------