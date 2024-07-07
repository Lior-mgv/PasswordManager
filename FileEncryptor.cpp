#include "FileEncryptor.h"

auto FileEncryptor::encrypt(const std::string& data, const std::string& key) -> std::string {
    return apply_xor(data, key);
}

auto FileEncryptor::decrypt(const std::string &data, const std::string &key) -> std::string {
    return apply_xor(data, key);
}

std::string FileEncryptor::apply_xor(const std::string &data, const std::string &key) {
    std::string result(data);
    for (std::size_t i = 0; i < data.length(); ++i) {
        result[i] ^= key[i % key.length()];
    }
    return result;
}
