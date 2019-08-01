#ifndef STRING_H
#define STRING_H
#include "../stdint.h"
char*  strcat(char* str1, const char* str2);
int    strcmp(const char* str1, const char* str2);
char*  strcpy(char* str1, const char* str2);
size_t strlen(const char* str);

char* int_to_str  (int32_t value, char* str, int32_t base);
char* float_to_str(float   value, char* str);
int   str_to_int  (char* str);
float str_to_float(char* str);

void* memcpy (void* val1, const void* val2, size_t size);
void* memmove(void* val1, const void* val2, size_t size);
int   memcmp (const void* val1, const void* val2, size_t size);
void  memset (void* src, int val, size_t size);
#endif
