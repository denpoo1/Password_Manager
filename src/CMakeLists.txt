cmake_minimum_required(VERSION 3.25)
project(untitled3)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled3 main.cpp User/User.cpp User/User.h Password_Strength_Checker/Password_Strength_Checker.cpp Password_Strength_Checker/Password_Strength_Checker.h Password/Password.cpp Password/Password.h FileEncryptor/FileEncryptor.cpp FileEncryptor/FileEncryptor.h PasswordManager/PasswordManager.cpp PasswordManager/PasswordManager.h LoginManager/LoginManager.cpp LoginManager/LoginManager.h UserManager/UserManager.cpp UserManager/UserManager.h)
