#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdes.h"

/* Global tab */

const int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17,  9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7};

const int IP_1[64] = {40,  8, 48, 16, 56, 24, 64, 32,
                      39,  7, 47, 15, 55, 23, 63, 31,
                      38,  6, 46, 14, 54, 22, 62, 30,
                      37,  5, 45, 13, 53, 21, 61, 29,
                      36,  4, 44, 12, 52, 20, 60, 28,
                      35,  3, 43, 11, 51, 19, 59, 27,
                      34,  2, 42, 10, 50, 18, 58, 26,
                      33,  1, 41,  9, 49, 17, 57, 25};

const int E[48] = { 32,  1,  2,  3,  4,  5,
                     4,  5,  6,  7,  8,  9,
                     8,  9, 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25,
                    24, 25, 26, 27, 28, 29,
                    28, 29, 30, 31, 32,  1};

const int S1[64] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
                     0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
                     4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
                    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

const int S2[64] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
                     3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
                     0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
                    13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

const int S3[64] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
                    13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
                    13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                     1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

const int S4[64] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
                    13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
                    10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                     3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

const int S5[64] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
                    14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                     4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
                    11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

const int S6[64] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                    10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                     9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                     4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

const int S7[64] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
                    13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
                     1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
                     6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

const int S8[64] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                     1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                     7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                     2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

const int P[32] =  {16,  7, 20, 21,
                    29, 12, 28, 17,
                     1, 15, 23, 26,
                     5, 18, 31, 10,
                     2,  8, 24, 14,
                    32, 27,  3,  9,
                    19, 13, 30,  6,
                    22, 11,  4, 25};

/* Function */

des_t *des_set_str(const char *s, const char *type)
{
  if(strcmp(type, "str") == 0)
  {
    int len = strlen(s);
    des_t *m = malloc(sizeof(des_t));
    
    m->size = len / 8;
    if((len * 8) % 64)
      m->size++;
    m->tab = malloc(sizeof(u64) * m->size);
    
    int count = 0;

    for(int i = 0; i < len; i++)
    {
      count = (i * 8) / 64;
      m->tab[count] <<= 8;
      m->tab[count] ^= s[i];
    }
    m->tab[count] <<= 64 - (len * 8) % 64;
    return m;
  }
  else if(strcmp(type, "hexa") == 0)
  {
    int len = strlen(s);
    des_t *m = malloc(sizeof(des_t));

    m->size = len / 4;
    if((len * 4) % 64)
      m->size++;
    m->tab = malloc(sizeof(u64) * m->size);

    int count = 0;

    for(int i = 0; i < len; i++)
    {
      u64 tmp = s[i];
      if(tmp >= 48 && tmp <= 57) {
        tmp -= 48;
      }
      else if (tmp >= 97 && tmp <= 102) {
        tmp -= (97 - 10);
      }
      else {
        exit(666);
      }
      count = (i * 4) / 64;
      m->tab[count] <<= 4;
      m->tab[count] ^= tmp;
    }
    m->tab[count] <<= 64 - (len * 4) % 64;
    return m;
  }
  else
  {
    printf("Format not supported. Use str or hexa\n");
    exit(666);
  }
}

char *des_get_str(des_t *m, const char *type)
{
  if(strcmp(type, "str") == 0)
  {
    int len = m->size * 8;

    char *ret = malloc(sizeof(char) * (len + 1));
    ret[len] = '\0';

    for(int i = 0; i < m->size; i++)
    {
      for(int j = 0; j < 8; j++)
      {
        ret[i*8+j] = (m->tab[i] >> (64 - (j + 1) * 8)) & 0xFF;
      }
    }
    return ret;
  }
  else if(strcmp(type, "hexa") == 0)
  {
    int len = m->size * 16;

    char *ret = malloc(sizeof(char) * (len + 1));
    ret[len] = '\0';

    for(int i = 0; i < m->size; i++)
    {
      for(int j = 0; j < 16; j++)
      {
        u8 tmp = (m->tab[i] >> (64 - (j + 1) * 4)) & 0xF;
        if(tmp > 15 || tmp < 0) {
          exit(666);
        }
        if(tmp < 10) {
          tmp += 48;
        }
        else {
          tmp += 87;
        }
        ret[i*16+j] = tmp;
      }
    }
    return ret;
  }
  else
  {
    printf("Format not supported. Use str or hexa\n");
    exit(666);
  }
}

des_t *des_init(u64 size)
{
  des_t *m = malloc(sizeof(des_t));
  m->tab = malloc(sizeof(u64) * size);
  m->size = size;
  return m;
}

void des_free(des_t *d) 
{
  free(d->tab);
  free(d);
}

void swap_32(u32 *l, u32 *r)
{
  u32 tmp = *l;
  *l = *r;
  *r = tmp;
}

void swap_48(u48 *a, u48 *b)
{
  u48 tmp = *a;
  *a = *b;
  *b = tmp;
}

u64 generate_key_des(const char *s)
{
  u64 key = 0;
  int length = strlen(s);

  for(int i = 0; i < length; i++)
  {
    key ^= (s[i] << (8 * (i % 8)));
  }

  return key;
}

u64 *generate_key_3des(const char *s)
{
  u64 *key = malloc(sizeof(u64) * 3);
  int length = strlen(s);
  key[0] = 0; key[1] = 0; key[2] = 0;

  for(int i = 0; i < length; i++)
  {
    key[(i%8)%3] ^= (s[i] << (8 * (i % 8)));
  }

  return key;
}

u48 *generate_sub_keys(const u64 key) {
  u48 *sub_keys = malloc(sizeof(u48) * 16);

  sub_keys[0] = key;
  for(int i = 1; i < 16; i++)
  {
    sub_keys[i] = rrot64(key, i*4) % 0xFFFFFFFFFF;
  }

  return sub_keys;
}

void rotate_sub_keys(u48 *sub_keys)
{
  swap_48(&sub_keys[0], &sub_keys[15]);
  swap_48(&sub_keys[1], &sub_keys[14]);
  swap_48(&sub_keys[2], &sub_keys[13]);
  swap_48(&sub_keys[3], &sub_keys[12]);
  swap_48(&sub_keys[4], &sub_keys[11]);
  swap_48(&sub_keys[5], &sub_keys[10]);
  swap_48(&sub_keys[6], &sub_keys[9]);
  swap_48(&sub_keys[7], &sub_keys[8]);
}

u64 initial_permutation(const u64 n)
{
  u64 res = 0;

  for(int i = 0; i < 64; i++)
  {
    res <<= 1;
    res ^= des_test_bit(n, IP[i], 64);
  }

  return res;
}

u64 initial_permutation_inverse(const u64 n)
{
  u64 res = 0;

  for(int i = 0; i < 64; i++)
  {
    res <<= 1;
    res ^= des_test_bit(n, IP_1[i], 64);
  }
  
  return res;
}

u48 expension(const u32 n)
{ 
  u48 res = 0;

  for(int i = 0; i < 48; i++)
  {
    res <<= 1;
    res ^= des_test_bit(n, E[i], 32);
  }

  return res;
}

u32 s_box(const u48 n)
{
  u8 s1 = n >> 42;
  u8 s2 = (n >> 36) & 0x3F;
  u8 s3 = (n >> 30) & 0x3F;
  u8 s4 = (n >> 24) & 0x3F;
  u8 s5 = (n >> 18) & 0x3F;
  u8 s6 = (n >> 12) & 0x3F;
  u8 s7 = (n >>  6) & 0x3F;
  u8 s8 = n & 0x3F;

  u32 res = 0;
  res ^= S1[(s1 >> 4) * 16 + (s1 & 0xF)];
  res <<= 4;
  res ^= S2[(s2 >> 4) * 16 + (s2 & 0xF)];
  res <<= 4;
  res ^= S3[(s3 >> 4) * 16 + (s3 & 0xF)];
  res <<= 4;
  res ^= S4[(s4 >> 4) * 16 + (s4 & 0xF)];
  res <<= 4;
  res ^= S5[(s5 >> 4) * 16 + (s5 & 0xF)];
  res <<= 4;
  res ^= S6[(s6 >> 4) * 16 + (s6 & 0xF)];
  res <<= 4;
  res ^= S7[(s7 >> 4) * 16 + (s7 & 0xF)];
  res <<= 4;
  res ^= S8[(s8 >> 4) * 16 + (s8 & 0xF)];

  return res;
}

u32 permutation(const u32 n)
{  
  u32 res = 0;

  for(int i = 0; i < 32; i++)
  {
    res <<= 1;
    res ^= des_test_bit(n, P[i], 32);
  }

  return res;
}

u32 function_f(const u32 r0, const u48 sub_key)
{
  u48 r0_exp = expension(r0);
  r0_exp ^= sub_key;
  u32 res_s_box = s_box(r0_exp);
  u32 res_permutation = permutation(res_s_box);
  return res_permutation;
}

u64 des_block(const u48 *sub_keys, const u64 input)
{
  u64 res = initial_permutation(input);
  u32 l = res >> 32;
  u32 r = res & 0xFFFFFFFF;

  for(int i = 0; i < 16; i++)
  {
    u32 tmp = r;
    r = l ^ function_f(r, sub_keys[i]);
    l = tmp;
  }

  swap_32(&l, &r);
  res = ((u64)l << 32) ^ (u64)r;
  res = initial_permutation_inverse(res);
  return res;
}

des_t *des(const u48 *sub_keys, des_t *input)
{
  des_t *m = des_init(input->size);

  for(int i = 0; i < m->size; i++)
  {
    m->tab[i] = des_block(sub_keys, input->tab[i]);
  }

  return m;
}

char *encrypt_des(const char *pw, const char *message)
{
  u64 key = generate_key_des(pw);
  u48 *sub_keys = generate_sub_keys(key);

  des_t *m = des_set_str(message, "str");
  des_t *c = des(sub_keys, m);

  char *cipher = des_get_str(c, "hexa");

  // Clear
  des_free(m);
  des_free(c);
  free(sub_keys);

  return cipher;
}

char *decrypt_des(const char *pw, const char *cipher)
{
  u64 key = generate_key_des(pw);
  u48 *sub_keys = generate_sub_keys(key);
  rotate_sub_keys(sub_keys);

  des_t *c = des_set_str(cipher, "hexa");
  des_t *d = des(sub_keys, c);

  char *decipher = des_get_str(d, "str");

  // Clear
  des_free(c);
  des_free(d);
  free(sub_keys);

  return decipher;
}

char *encrypt_3des(const char *pw, const char *message)
{
  u64 *key = generate_key_3des(pw);
  des_t *m = des_set_str(message, "str");

  u48 *sub_keys0 = generate_sub_keys(key[0]);
  des_t *c0 = des(sub_keys0, m);

  u48 *sub_keys1 = generate_sub_keys(key[1]);
  rotate_sub_keys(sub_keys1);
  des_t *c1 = des(sub_keys1, c0);

  u48 *sub_keys2 = generate_sub_keys(key[2]);
  des_t *c2 = des(sub_keys2, c1);

  char *cipher = des_get_str(c2, "hexa");

  // Clear
  des_free(m);
  des_free(c0);
  des_free(c1);
  des_free(c2);
  free(key);
  free(sub_keys0);
  free(sub_keys1);
  free(sub_keys2);

  return cipher;
}

char *decrypt_3des(const char *pw, const char *cipher)
{
  u64 *key = generate_key_3des(pw);
  des_t *m = des_set_str(cipher, "hexa");

  u48 *sub_keys2 = generate_sub_keys(key[2]);
  rotate_sub_keys(sub_keys2);
  des_t *d2 = des(sub_keys2, m);
  
  u48 *sub_keys1 = generate_sub_keys(key[1]);
  des_t *d1 = des(sub_keys1, d2);

  u48 *sub_keys0 = generate_sub_keys(key[0]);
  rotate_sub_keys(sub_keys0);
  des_t *d0 = des(sub_keys0, d1);

  char *decipher = des_get_str(d0, "str");

  // Clear
  des_free(m);
  des_free(d0);
  des_free(d1);
  des_free(d2);
  free(key);
  free(sub_keys0);
  free(sub_keys1);
  free(sub_keys2);

  return decipher;
}