#ifndef YAZ0_H
#define YAZ0_H

int yaz0_encode2(uint8_t* src, uint8_t* dest, int uncompressedSize);

void yaz0_decode(uint8_t* src, uint8_t* dst, int uncompressedSize);

int yaz0_encode(uint8_t* src, uint8_t* dest, int srcSize);

#endif // YAZ0_H
