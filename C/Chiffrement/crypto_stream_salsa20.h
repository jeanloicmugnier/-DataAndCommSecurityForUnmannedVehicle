#ifndef crypto_stream_salsa20_H
#define crypto_stream_salsa20_H

#define crypto_stream_salsa20_amd64_xmm6_KEYBYTES 32
#define crypto_stream_salsa20_amd64_xmm6_NONCEBYTES 8

extern int crypto_stream_salsa20_amd64_xmm6(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_amd64_xmm6_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_amd64_xmm6_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_amd64_xmm6_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_salsa20_amd64_xmm6_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);


#define crypto_stream_salsa20 crypto_stream_salsa20_amd64_xmm6
#define crypto_stream_salsa20_xor crypto_stream_salsa20_amd64_xmm6_xor
#define crypto_stream_salsa20_beforenm crypto_stream_salsa20_amd64_xmm6_beforenm
#define crypto_stream_salsa20_afternm crypto_stream_salsa20_amd64_xmm6_afternm
#define crypto_stream_salsa20_xor_afternm crypto_stream_salsa20_amd64_xmm6_xor_afternm
#define crypto_stream_salsa20_KEYBYTES crypto_stream_salsa20_amd64_xmm6_KEYBYTES
#define crypto_stream_salsa20_NONCEBYTES crypto_stream_salsa20_amd64_xmm6_NONCEBYTES
#define crypto_stream_salsa20_BEFORENMBYTES crypto_stream_salsa20_amd64_xmm6_BEFORENMBYTES
#define crypto_stream_salsa20_IMPLEMENTATION "crypto_stream/salsa20/amd64_xmm6"
#ifndef crypto_stream_salsa20_amd64_xmm6_VERSION
#define crypto_stream_salsa20_amd64_xmm6_VERSION "-"
#endif
#define crypto_stream_salsa20_VERSION crypto_stream_salsa20_amd64_xmm6_VERSION

#endif
