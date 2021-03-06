#include "controllers/highlights/HighlightPhrase.hpp"

namespace chatterino {

bool HighlightPhrase::operator==(const HighlightPhrase &other) const
{
    return std::tie(this->pattern_, this->hasSound_, this->hasAlert_,
                    this->isRegex_, this->isCaseSensitive_, this->soundUrl_,
                    this->color_) == std::tie(other.pattern_, other.hasSound_,
                                              other.hasAlert_, other.isRegex_,
                                              other.isCaseSensitive_,
                                              other.soundUrl_, other.color_);
}

HighlightPhrase::HighlightPhrase(const QString &pattern, bool hasAlert,
                                 bool hasSound, bool isRegex,
                                 bool isCaseSensitive, const QString &soundUrl,
                                 QColor color)
    : pattern_(pattern)
    , hasAlert_(hasAlert)
    , hasSound_(hasSound)
    , isRegex_(isRegex)
    , isCaseSensitive_(isCaseSensitive)
    , soundUrl_(soundUrl)
    , regex_(isRegex_ ? pattern
                      : "\\b" + QRegularExpression::escape(pattern) + "\\b",
             QRegularExpression::UseUnicodePropertiesOption |
                 (isCaseSensitive_ ? QRegularExpression::NoPatternOption
                                   : QRegularExpression::CaseInsensitiveOption))
{
    this->color_ = std::make_shared<QColor>(color);
}

HighlightPhrase::HighlightPhrase(const QString &pattern, bool hasAlert,
                                 bool hasSound, bool isRegex,
                                 bool isCaseSensitive, const QString &soundUrl,
                                 std::shared_ptr<QColor> color)
    : pattern_(pattern)
    , hasAlert_(hasAlert)
    , hasSound_(hasSound)
    , isRegex_(isRegex)
    , isCaseSensitive_(isCaseSensitive)
    , soundUrl_(soundUrl)
    , color_(color)
    , regex_(isRegex_ ? pattern
                      : "\\b" + QRegularExpression::escape(pattern) + "\\b",
             QRegularExpression::UseUnicodePropertiesOption |
                 (isCaseSensitive_ ? QRegularExpression::NoPatternOption
                                   : QRegularExpression::CaseInsensitiveOption))
{
}

const QString &HighlightPhrase::getPattern() const
{
    return this->pattern_;
}

bool HighlightPhrase::hasAlert() const
{
    return this->hasAlert_;
}

bool HighlightPhrase::hasSound() const
{
    return this->hasSound_;
}

bool HighlightPhrase::hasCustomSound() const
{
    return !this->soundUrl_.isEmpty();
}

bool HighlightPhrase::isRegex() const
{
    return this->isRegex_;
}

bool HighlightPhrase::isValid() const
{
    return !this->pattern_.isEmpty() && this->regex_.isValid();
}

bool HighlightPhrase::isMatch(const QString &subject) const
{
    return this->isValid() && this->regex_.match(subject).hasMatch();
}

bool HighlightPhrase::isCaseSensitive() const
{
    return this->isCaseSensitive_;
}

const QUrl &HighlightPhrase::getSoundUrl() const
{
    return this->soundUrl_;
}

const std::shared_ptr<QColor> HighlightPhrase::getColor() const
{
    return this->color_;
}

}  // namespace chatterino
