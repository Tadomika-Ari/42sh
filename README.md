# 42sh

Our project 42SH is a recreation of a Unix shell based on **TCSH**, written entirely in **C**.  
For this project we chose the shell base created by one of our team members, Alcibiade Streit-Soumaila,  
and implemented almost all **TCSH** features, except for **command group** and **command substitution**.  

This project was completed over the course of 5 weeks by our team of 5 members.


-----------------
## Features

#### Core features
- Command execution
- PATH handling
- Environment variable management
- Pipes
- Redirections
- Command separators (;)
- Job control
- Logical operators (&& and ||)
- Parenthesis
- Inhibitors
- History management
- Aliases
- Signal handling
- Builtin commands
- Error handling
- Which
- Where

#### Scripting features
- if
- foreach
- repeat
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

Bonus builtin commands are implemented as well.

#### Bonus usage :

Compile with :

```bash
make bonus
```

And run with :
```bash
./42sh
```

## Bonus builtin commands

Below you will find a table containing the commands and their descriptions.

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
| velkoz |       show velkoz        |
| banana |       show a ... banana       |


---
## Project structure

Our functions are in a src folder and then divided in folders organized by features :

```text
src/  
 |--alias/  
 |--autocompletion/  
 |--bonus/  
 |--built_in/  
 |--command_utilities/  
 |--error/  
 |--free/  
 |--history/  
 |--initialisation/  
 |--jobs/  
 |--loop_tcsh/  
 |--redirection/  
 |--repeat/  
 |--tools/  
 |--user/  
 |__var_interpreters/  
 ```

## Tests

Unit tests and functional tests are available as well.


#### Unit test

Run unit tests with:

```bash
make tests_run
```

#### Functional test

Run functional tests with:

```bash
make 
```

You can find more information in the README file in

++++++++++++++







the test folder.

### For more help:
Use the help flag to display more information about the command.

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