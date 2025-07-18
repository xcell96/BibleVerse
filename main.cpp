
#include <iostream>

#include "src/InputParser.h"
#include "src/TextFetcher.h"

int main() {
    std::string input;
    std::cout << "Input:\n";
    std::getline(std::cin, input);

    // InputParser passage("verse");
    // InputParser passage("verse John 3:16 RomCor");
    InputParser passage(input);
    const TextFetcher text_fetcher(passage.getBible(), passage.getPassageStart(), passage.getPassageEnd());

    std::cout << text_fetcher.fetch() << '\n';
}