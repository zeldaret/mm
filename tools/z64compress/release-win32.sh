# build compression functions (slow)
i686-w64-mingw32.static-gcc -DNDEBUG -s -Ofast -flto -lm -c -Wall src/enc/*.c src/enc/lzo/*.c src/enc/ucl/comp/*.c src/enc/apultra/*.c
mkdir -p o
mv *.o o

# build everything else
i686-w64-mingw32.static-gcc -o z64compress.exe -DNDEBUG src/*.c o/*.o src/enc/libdeflate/lib/deflate_compress.c src/enc/libdeflate/lib/utils.c -Isrc/enc/libdeflate -Wall -Wextra -s -Os -flto -lpthread -lz -mconsole -municode

# move to bin directory
mkdir -p bin/win32
mv z64compress.exe bin/win32

