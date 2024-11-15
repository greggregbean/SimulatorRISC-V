#include "elf_loader.hpp"

int main() {
    Hart hart;
    ELFLoader elfik ("../test/test.elf");

    elfik.load (hart);
    hart.memory_dump ();
    hart.run_pipeline ();
}