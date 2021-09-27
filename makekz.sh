make -j4 COMPARE=0 all && cd ../kz && make clean && make -j3 all && ./build/makerom-lite ../mm/mm.us.rev1.rom.z64 && cd ../mm
