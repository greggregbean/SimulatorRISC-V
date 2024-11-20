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
./configure --prefix=/opt/riscv --with-arch=rv64ia --with-abi=lp64
```

## Compile tests
````
riscv64-unknown-linux-gnu-gcc -march=rv64i -mabi=lp64 -c test.c -o test.elf
````


## Objdump tests
````
riscv64-unknown-linux-gnu-objdump -d test.elf > test.dump
````

## Run
````
./simulator test.elf
````