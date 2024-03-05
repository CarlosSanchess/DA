#include "App.h"
#include <iostream>
#include "reader.h"

int main() {

    Reader r;
    r.readAndParsePS();
    r.readAndParseWR();
    r.readAndParsePipes();
    return 0;
}