#include "client.h"

char *hash_password(const char *password) {
	static char hash_hex[SHA256_DIGEST_LENGTH * 2 + 1];
	unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256((unsigned char *)password, mx_strlen(password), hash);

	for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		sprintf(hash_hex + (i * 2), "%02x", hash[i]);
	}

	hash_hex[SHA256_DIGEST_LENGTH * 2] = '\0';
	return hash_hex;
}

