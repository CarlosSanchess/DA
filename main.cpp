#include "App.h"
#include <iostream>
#include "reader.h"

int main() {

    Reader r;
    r.readAndParsePS();
    r.readAndParseDS();
    return 0;
}