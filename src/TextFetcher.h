//
// Created by xcell on 17.07.2025.
//

#pragma once
#include <memory>
#include <versekey.h>


class TextFetcher {
    std::string bible_;
    std::unique_ptr<sword::VerseKey> passageStart_;
    std::unique_ptr<sword::VerseKey> passageEnd_;

    static std::string fetchModules();
    std::string fetchVerse() const;
    std::string fetchRange() const;
public:
    explicit TextFetcher(
        const std::string &bible,
        std::unique_ptr<sword::VerseKey> passageStart,
        std::unique_ptr<sword::VerseKey> passageEnd);

    std::string fetch() const;
};
