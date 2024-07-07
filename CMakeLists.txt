cmake_minimum_required(VERSION 3.24)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 23)

add_executable(PasswordManager main.cpp Entry.cpp Entry.h PasswordList.cpp PasswordList.h FileEncryptor.cpp FileEncryptor.h UI.cpp UI.h DecryptionException.h)
