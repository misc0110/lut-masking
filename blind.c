#include <stdio.h>
#include <stdint.h>
#include <time.h>

//------------------------------------------------------------------
// define the datatype of your lookup-table (default: unsigned char)
#define T unsigned char

// define the number of partitions
#define PARTITIONS 3

// define your lookup-table here
T lut[] = {4, 1, 5, 12, 7, 13, 9, 0, 15, 2, 6, 3, 11, 14, 10, 8};

//------------------------------------------------------------------


//------------------------------------------------------------------
// internal helper function
//------------------------------------------------------------------
void refreshMasks(T out[], T in[], int n) {
    int j;
    out[0] = in[0];
    for(j = 1; j < n; j++) {
      T tmp = rand() % (1 << sizeof(T));
      out[0] = out[0] ^ tmp;
      out[j] = in[j] ^ tmp;
    }
}

//------------------------------------------------------------------
// The masking function. It computes res = LUT(x) where 
// res = res[0], ..., res[n-1] and x = x[0], ..., x[n-1] s.t.
// res[0] ^ ... ^ res[n-1] = LUT(x[0] ^ ... ^ x[n-1])
//------------------------------------------------------------------
void mask(T x[], T* res, int n) {
    T T0[sizeof(lut) / sizeof(T)][PARTITIONS];
    T T1[sizeof(lut) / sizeof(T)][PARTITIONS];
    
    const int lut_size = sizeof(lut) / sizeof(T);
    int u, i, j;
    
    for(u = 0; u < lut_size; u++) {
        T0[u][0] = lut[u];
        for(i = 1; i < n; i++) {
            T0[u][i] = 0;
        }
    }
    
    for(i = 0; i < n - 1; i++) {
        for(u = 0; u < lut_size; u++) {
           for(j = 0; j < n; j++) {
               T1[u][j] = T0[u ^ x[i]][j];   
           }
        }
        for(u = 0; u < lut_size; u++) {
           refreshMasks(T0[u], T1[u], n);
        }
    }
    
    refreshMasks(res, T0[x[n - 1]], n);
}

int main() {
    // test the functions
    srand(time(NULL));
    
    unsigned char in[3];
    unsigned char res[3];
    
    // we want to hide a simplified sbox lookup in the form res = sbox[data ^ key]
    unsigned char data = 3; // the data we want to hide
    int msk, key; // the mask and key
    for(msk = 0; msk < 16; msk++) { // test various masks...
      for(key = 0; key < 16; key++) { // ...and keys
        in[0] = msk ^ key; // first partition is the key masked with the mask
        in[1] = data; // second partition is the data
        in[2] = msk; // third partition is the mask
        // it holds that in[0] xor in[1] xor in[2] = (mask xor key) xor data xor mask = key xor data
        // -> that is what we want to look up
        
        mask(in, res, 3); // do the lookup using 3 partitions
        int r = res[0] ^ res[1] ^ res[2]; // we obtain the lookup result by xor'ing all result partitions
        if(r != lut[key ^ data]) { // result must be the same as unmasked lookup
          printf("Error key: %d, masking: %d: %d != %d!\n", key, msk, r, lut[key ^ data]);   
        }
      }
    }
    printf("OK!\n");

    return 0;
}
