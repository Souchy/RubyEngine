/*
 * This source file was generated by the Gradle 'init' task
 */

#include <iostream>
#include <stdlib.h>
#include <RubyEngine.h>

int main () {
    RubyEngine::Greeter greeter;
    std::cout << greeter.greeting() << "!!!!!!!!" << std::endl;

    Ruby ruby;
    ruby.start();
    
    return 0;
}