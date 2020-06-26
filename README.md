# calc

A program for evaluating arithmatic expressions.

Supports multiplication, division, addition and subtraction.

## Building

Build the program by running `make`. Binary will be built to `./calc`

## Running tests

Run tests by running `make test`.

## Use

The program will evaluate its arguments:

```
$ ./calc 10*9
90
```

If no arguments are provided, the program will run in REPL mode:

```
$ ./calc
> 100+(20*2)/2
120
> exit
$
```
