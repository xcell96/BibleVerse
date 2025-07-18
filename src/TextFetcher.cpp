//
// Created by xcell on 17.07.2025.
//

#include "TextFetcher.h"

#include <swmgr.h>
#include <swmodule.h>

TextFetcher::TextFetcher(
    const std::string &bible,
    std::unique_ptr<sword::VerseKey> passageStart,
    std::unique_ptr<sword::VerseKey> passageEnd)
: bible_(bible), passageStart_(std::move(passageStart)), passageEnd_(std::move(passageEnd)){}

std::string TextFetcher::fetchModules() {
    sword::SWMgr manager_;
    std::string result;
    for (const auto& module : manager_.getModules()) {
        result += module.second->getName();
        result += '\n';
    }
    return result;
}

std::string TextFetcher::fetchVerse() const {
    sword::SWMgr manager;
    const auto bible = manager.getModule(bible_.c_str());
    bible->setKey(*passageStart_);
    return std::to_string(passageStart_->getVerse()) + ": " + bible->stripText();
}

std::string TextFetcher::fetchRange() const {
    std::string result;

    sword::SWMgr manager;
    const auto bible = manager.getModule(bible_.c_str());

    auto iterator = *passageStart_;
    auto end = *passageEnd_;
    ++end;

    const int target_chapter{iterator.getChapter()};

    while (iterator != end && iterator.getChapter() == target_chapter) {
        bible->setKey(iterator);
        result += std::to_string(iterator.getVerse()) + ": " + bible->stripText() + '\n';
        ++iterator;
    }

    return result;
}

std::string TextFetcher::fetch() const {
    if (bible_.empty()) return fetchModules();
    if (!passageEnd_) return fetchVerse();
    return fetchRange();
}
