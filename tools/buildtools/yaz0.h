#ifndef YAZ0_H
#define YAZ0_H

void yaz0_decode(uint8_t* src, uint8_t* dst, int uncompressedSize);

int yaz0_encode(uint8_t* src, uint8_t* dest, int srcSize);

#endif // YAZ0_H
