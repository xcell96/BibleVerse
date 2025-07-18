//
// Created by xcell on 17.07.2025.
//

#include "InputParser.h"

#include <sstream>

#include <swmodule.h>
#include <swmgr.h>

InputParser::InputParser(const std::string& input)
    : passageStart_(nullptr), passageEnd_(nullptr)
{
    if (input.empty()) {
        std::cerr << "BibleVerse: empty input string.\n";
        return;
    }

    parseInput(input);
}

std::string InputParser::getBible() const { return bible_; }

std::unique_ptr<sword::VerseKey> InputParser::getPassageStart() { return std::move(passageStart_); }

std::unique_ptr<sword::VerseKey> InputParser::getPassageEnd() { return std::move(passageEnd_); }

std::vector<std::string> InputParser::tokenize(const std::string &line) {
    std::vector<std::string> tokens;

    std::stringstream ss(line);
    std::string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    return tokens;
}

void InputParser::parseInput(const std::string& input) {
    const auto tokens = tokenize(input);

    // TODO: when there are 2 tokens, the user should be warned.
    if (tokens.size() != 4) return;

    sword::SWMgr manager_;
    bible_ = tokens[1];
    std::string book = tokens[2];
    std::string number = tokens[3];
    auto bible = manager_.getModule(bible_.c_str());
    if (!bible) {
        book = tokens[1];
        number = tokens[2];
        bible_ = tokens[3];
        bible = manager_.getModule(bible_.c_str());
    }

    // if we don't get a proper bible, the function fails
    if (!bible) {
        std::cerr << "Module not found.\n";
        return;
    }

    assignPassage(book, number);
}

void InputParser::assignPassage(const std::string &book, const std::string &number) {
    // this is going to be some string magic
    // 1: book chapter:verse
    // 2: book chapter:verse-verse
    // 3: book chapter

    // if there are no colons in the numbers, then it's a chapter
    if (number.find(":") == std::string::npos) {
        sword::VerseKey start((book + " " + number).c_str());
        passageStart_ = std::make_unique<sword::VerseKey>(start);
        const int targetchapter{start.getChapter()};
        while (start.getChapter() == targetchapter) { ++start; }
        passageEnd_ = std::make_unique<sword::VerseKey>(start);
        return;
    }

    // if there is a dash in the numbers, then it's a range
    if (number.find("-") != std::string::npos) {
        const int chapter = atoi(number.c_str());
        const int start = atoi(number.substr(number.find(":") + 1).c_str());
        const int end = atoi(number.substr(number.find("-") + 1).c_str());

        std::string str_range_start(book + " " + std::to_string(chapter) + ":" + std::to_string(start));
        std::string str_range_end(book + " " + std::to_string(chapter) + ":" + std::to_string(end));

        sword::VerseKey range_start(str_range_start.c_str());
        sword::VerseKey range_end(str_range_end.c_str());

        passageStart_ = std::make_unique<sword::VerseKey>(range_start);
        passageEnd_ = std::make_unique<sword::VerseKey>(range_end);
        return;
    }

    // if none of the cases above, then it's one single verse
    passageStart_ = std::make_unique<sword::VerseKey>((book + " " + number).c_str());
}
