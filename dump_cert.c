#include <openssl/asn1.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/bio.h>
#include <openssl/safestack.h>
#include <stdio.h>
#include <string.h>

/*
 * gcc dump_cert.c -lssl -lcrypto -ldl -L/usr/local/lib
 */


int main()
{
    const unsigned char  cert_data[] = {
#include "temp_1.txt"
    };

    int cert_data_size = sizeof( cert_data);
    printf("the size of date = %d\n", cert_data_size);
    char * file_name = "111_epid.pem";

    X509 * px = NULL;


    const unsigned char * my_cert = cert_data;
    px = d2i_X509(NULL, &my_cert, cert_data_size);
    if(px == NULL)
        printf("error to covert to X509\n");
    else
        printf("successfully to cover to x509\n");

    FILE * f  = fopen(file_name, "wb");
    if(f == NULL)
        printf("open file failed\n");
    PEM_write_X509(f, px);

    X509_free(px);

    fclose(f);


    return 0;

}
