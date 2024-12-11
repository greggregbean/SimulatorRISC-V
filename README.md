# RISC-V Simulator

## Build
````
cmake -B build
cmake --build build
````

## Riscv toolchain is required

[riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)

[Кросс-компиляция под RISC-V для самых маленьких](https://habr.com/ru/articles/740868/)

You need to configure supported arch and abi in compiler build:  

```
export RISCV=/opt/riscv/
./configure --prefix=$RISCV --with-arch=rv64g --with-abi=lp64
```

## Compile tests
````
riscv64-unknown-linux-gnu-gcc -nostdlib -march=rv64i -mabi=lp64 -static -Wl,-emain 8_queens.c -o 8_queens.o
````


## Objdump tests
````
riscv64-unknown-linux-gnu-objdump -d 8_queens.o > 8_queens.dump
````

## Run
````
./simulator ../test/8_queens.o
````

## Cosimulation with spike
[riscv-isa-sim](https://github.com/riscv-software-src/riscv-isa-sim)

For running spike you need pk:

[riscv-pk](https://github.com/riscv-software-src/riscv-pk)

As we use riscv64-unknown-linux-gnu-gcc, we need explicitly specify pk:
```
spike -d $RISCV/riscv64-unknown-linux-gnu/bin/pk a.out > a.log
```