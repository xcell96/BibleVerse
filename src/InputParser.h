//
// Created by xcell on 17.07.2025.
//

/*
 *  INPUT FORMAT:
 *  "verse"                             - shows available translations
 *  "verse" <passage> <translation>     - displays passage according to translation
 *  "verse" <translation> <passage>     - idem
 */

#pragma once
#include <string>
#include <memory>
#include <vector>

#include <versekey.h>

class InputParser {
    std::string bible_;

    // these should be passed on to the fetcher class constructor
    std::unique_ptr<sword::VerseKey> passageStart_;
    std::unique_ptr<sword::VerseKey> passageEnd_;

    static std::vector<std::string> tokenize(const std::string& line);

    // initializes the Bible and VerseKeys according to the input
    void parseInput(const std::string& input);
    void assignPassage(const std::string& book, const std::string& number);
public:
    explicit InputParser(const std::string& input);

    [[nodiscard]] std::string getBible() const;
    std::unique_ptr<sword::VerseKey> getPassageStart();
    std::unique_ptr<sword::VerseKey> getPassageEnd();
};

