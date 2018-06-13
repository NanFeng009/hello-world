#include <openssl/asn1.h>
#include <openssl/x509.h>
#include <openssl/safestack.h>
#include <stdio.h>

#define X509_FILETYPE_PEM 1



static int load_certs_file(STACK_OF(X509) **othercerts, const char *file, int format)
{
    char buf[1024] = "\0";
    STACK_OF(X509_INFO) *allcerts = NULL;
    X509* x = NULL;
    int i,ret = 0;

    BIO *certs = NULL;

    strncpy(buf,file,1024-1);
    if (!(certs = BIO_new_file(buf, "r"))) goto end;

    if (!othercerts||!(*othercerts = sk_X509_new_null())) goto end;
    if (format == X509_FILETYPE_PEM)
    {
        allcerts = PEM_X509_INFO_read_bio(certs, NULL, NULL, NULL);
        for(i = 0; i < sk_X509_INFO_num(allcerts); i++)
        {
            X509_INFO *xi = sk_X509_INFO_value(allcerts, i);
            if (xi->x509)
            {
                sk_X509_push(*othercerts, xi->x509);
                ret++;
                xi->x509 = NULL;

            }

        }

    }
    else if (format == X509_FILETYPE_ASN1)
    {
        x=d2i_X509_bio(certs,NULL);
        if (x == NULL)
            goto end;
        sk_X509_push(*othercerts, x);
        ret++;

    }
end:
    if (ret == 0 || othercerts == NULL)
        fprintf(stderr, "unable to load certificates: %s\n", buf);
    sk_X509_INFO_pop_free(allcerts, X509_INFO_free);
    BIO_free(certs);
    return ret;

}


static int certs_chain_update(STACK_OF(X509) *certs, const char *file)
{
    char * buf = file;
    BIO* out = NULL;
    int num =0;
    X509 *m_cert =NULL;

    num=sk_X509_num(certs);
    out = BIO_new_file(buf,"w+");
    if(out==NULL){
        return -1;
    }
    for (int i=0; i< num; i++){
        printf("%s write the %d certificate\n", __FUNCTION__, i);
        m_cert = sk_X509_value(certs,i);
        //char pubkey_algoname[ 200 ];
        //int pubkey_algonid = OBJ_obj2nid(m_cert->cert_info->key->algor->algorithm);
        //printf("the pubkey_algonid = %d\n", pubkey_algonid);
        EVP_PKEY * my_key = X509_get_pubkey( m_cert );
        if(my_key == NULL)
        {
            printf("ERROR getting public key from m_cert\n");
        } else {
            printf("Start to public key\n");
            for(int i = 0; i < 30; i++)
            {
                printf("%02X ",*((uint8_t *)my_key));
            }
            printf("\n");
        }
        uint8_t * group_cert;
        i2d_X509(group_cert, m_cert);
        printf("Start to print cert\n");
        for(int i = 0; i < 100; i++)
        {
            printf("%02X", (unsigned char*)group_cert);
        }
        printf("\n");

        PEM_write_bio_X509(out,m_cert);
        // get the subject
    }
    BIO_free(out);
    return 0;
}


int main(int argc, char** argv) 
{
    const char * file= "x509_cert_epid.pem";
    const char * new_file = "new_x509_cert_epid.pem";
    STACK_OF(X509) * certs = NULL;

    int ret = load_certs_file(&certs, file, 1);
    printf("load_certs_file ret = %d\n", ret);
    if(certs == NULL)
        printf("ERROR certs == NULL\n");
    ret = certs_chain_update(certs, new_file);


    return ret;

}
