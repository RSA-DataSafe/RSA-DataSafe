#ifndef _des_h
#define _des_h

// Typedef
typedef unsigned char u8;
typedef unsigned int u32;
typedef long unsigned u48;
typedef long long unsigned u64;

typedef struct {
  u64 *tab;
  u64 size;
} des_t;

/* Global tab */

extern const int IP[64];
extern const int IP_1[64];
extern const int E[48];
extern const int S1[64];
extern const int S2[64];
extern const int S3[64];
extern const int S4[64];
extern const int S5[64];
extern const int S6[64];
extern const int S7[64];
extern const int S8[64];
extern const int P[32];

/* Macro*/

/**
 * Left rotation for 64 bits number
 * @param x : number to rotate
 * @param y : number of bits to rotate the number x
 * @return the number x rotate
 */
#define lrot64(x, y) ((x << y) ^ (x >> (64 - y)))

/**
 * Right rotation for 64 bits number
 * @param x : number to rotate
 * @param y : number of bits to rotate the number x
 * @return the number x rotate
 */
#define rrot64(x, y) ((x >> y) ^ (x << (64 - y)))

/**
 * Test bit at position size - y
 * @param x : number to test
 * @param y : position
 * @param size : size in bits of number x
 * @return the bit at position size - y
 */
#define des_test_bit(x, y, size) (((u64)x & ((u64)1 << (size - y)))?1:0)

/* Function */

/**
 * Set des_t from string
 * @param s : string
 * @param type : type of encoding (str : normal string, hexa : hexa string(cipher) )
 * @return des_t
 */
des_t *des_set_str(const char *s, const char *type);

/**
 * Set string from des_t
 * @param m : des_t
 * @param type : type of encoding (str : normal string, hexa : hexa string(cipher) )
 * return string
 */
char *des_get_str(des_t *m, const char *type);

/**
 * Init des_t struct with a size
 * @param size : size in bits of des_t to init
 */
des_t *des_init(u64 size);

/**
 * Clear des_t struct
 * @param d : des_t to clear
 */
void des_free(des_t *d);

/**
 * Swap two 32 bits number
 * @param l : 32 bits number
 * @param r : 32 bits number
 */
void swap_32(u32 *l, u32 *r);

/**
 * Swap two 48 bits number
 * @param a : 48 bits number
 * @param b : 48 bits number
 */
void swap_48(u48 *a, u48 *b);

/**
 * Generate the main des key
 * @param s : password
 */
u64 generate_key_des(const char *s);

/**
 * Generate the main 3des keys
 * @param s : password
 */
u64 *generate_key_3des(const char *s);

/**
 * Generate 16 sub keys from main key
 * @param key : main key
 */
u48 *generate_sub_keys(const u64 key);

/**
 * Rotate the place of all sub keys(ex : 0 swap with 15)
 * @param sub_keys : sub keys
 */
void rotate_sub_keys(u48 *sub_keys);

/**
 * Initial permutation
 * @param n : input to permute
 */
u64 initial_permutation(const u64 n);

/**
 * Initial permutation inverse
 * @param n : input to permute
 */
u64 initial_permutation_inverse(const u64 n);

/**
 * Extand a 32 bits number to 48 bits
 * @param n : number to extand
 */
u48 expension(const u32 n);

/**
 * S-box
 * @param n : input of s-box
 */
u32 s_box(const u48 n);

/**
 * Permutation
 * @param n : input to permute
 */
u32 permutation(const u32 n);

/**
 * Function f
 * @param r0 : input of function f
 * @param sub_key : one of sub keys
 */
u32 function_f(const u32 r0, const u48 sub_key);

/**
 * Apply des on one block
 * @param sub_keys : sub keys
 * @param input : one block
 */
u64 des_block(const u48 *sub_keys, const u64 input);

/**
 * Apply des on des_t
 * @param sub_keys : sub keys
 * @param input : des_t
 */
des_t *des(const u48 *sub_keys, des_t *input);

/**
 * Encrypt a string with des
 * @param pw : password
 * @param message : string
 */
char *encrypt_des(const char *pw, const char *message);

/**
 * Decrypt a string with des
 * @param pw : password
 * @param cipher : string
 */
char *decrypt_des(const char *pw, const char *cipher);

/**
 * Encrypt a string with 3des
 * @param pw : password
 * @param message : string
 */
char *encrypt_3des(const char *pw, const char *message);

/**
 * Decrypt a string with 3des
 * @param pw : password
 * @param cipher : string
 */
char *decrypt_3des(const char *pw, const char *cipher);

#endif // !_des_h