# RISC-V Simulator

## Build
````
cmake -B build
cmake --build build
````

## Riscv compiler
```
sudo apt install gcc-riscv64-unknown-elf
sudo apt install binutils-riscv64-unknown-elf
```

## Compile tests
````
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -c test.c -o test.elf
````


## Objdump tests
````
riscv64-unknown-elf-objdump -d test.elf > test.dump
````

## Run
````
./simulator test.elf
````