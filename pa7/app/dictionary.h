#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QSet>
#include <QList>
#include <QString>

/**
 * @brief Helper class for throwing exception when Dictionary cannot be initialized
 */
class DictionaryException: public std::exception
{
private:
    std::string msg;
public:
    DictionaryException(const std::string& msg): msg(msg) {}
    const char* what() const _NOEXCEPT
    {
        return msg.c_str();
    }
};

/**
 * @brief Stores a list of words of given length.
 * Read words of given length from .txt file into a set.
 * The set is used for extracting a random word as well as checking if given word is in set.
 *
 * Bonus Task 5: Also read a separate set of words with frequency from .csv file into a list.
 * Answer word is taken from this list, and count determines how likely the word is picked.
 */
class Dictionary
{
    friend class TestBonusTask5;
    /**
     * @brief Helper struct for storing a word with frequency count
     */
    struct WordFrequency {
        QString word;
        unsigned long long count;
    };

    int word_length;
    QSet<QString> words {};
    QList<WordFrequency> answers {};
    unsigned long long answerCount {0};

public:
    Dictionary() = default;
    Dictionary(int word_length);

    /**
     * @brief Selects a random word to be used as answer
     * @return QString: a random word
     *
     * Bonus Task 5: This function should select from the answer list instead of word set
     */
    QString getRandomAnswer() const;

    /**
     * @brief Returns all possible answers for the given word length
     * @return QSet<QString>: a set of all possible answers
     *
     * Bonus Task 5: This function should get answers from the answer list instead of word set
     */
    QSet<QString> getAllAnswers() const;

    /**
     * @brief Check if a word exists in the set of all valid English words
     * @param word: word to be checked
     * @return bool: true if word appears in the set
     */
    bool isValidWord(const QString& word) const;
};

#endif // DICTIONARY_H
