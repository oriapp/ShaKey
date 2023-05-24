#include "rsa.h"

/*
void loadRSAKeys(mbedtls_pk_context *private_key, mbedtls_pk_context *public_key)
{
    // Load private key from file
    FILE *file = fopen("private_key.pem", "r");
    mbedtls_pk_init(private_key);
    mbedtls_pk_parse_keyfile(private_key, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA), file, NULL, 0);
    fclose(file);

    // Load public key from file
    file = fopen("public_key.pem", "r");
    mbedtls_pk_init(public_key);
    mbedtls_pk_parse_public_keyfile(public_key, file);
    fclose(file);
}
*/
