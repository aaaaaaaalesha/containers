// Copyright 2021 aaaaaaaalesha

#include <gtest/gtest.h>

#include <string>

#include "unrolled_linked_list.hpp"

struct TestConsoleLogger {
    TestConsoleLogger(const std::string& test_name) {
        std::cout << "Starting test " << test_name << ":" << std::endl;
    }

    ~TestConsoleLogger() {
        std::cout << "----------------[FINISHED]----------------" << std::endl;
    }

    void say(const std::string& statement) const {
        std::cout << statement << std::endl;
    }
};

TEST(unrolled_linked_list, Construct) {
TestConsoleLogger t_log("Construct");

unrolled_linked_list<int, 4> ul_list1;
ASSERT_TRUE(ul_list1.empty());

unrolled_linked_list<int, 4> ul_list2 = {1, 2, 3, 4, 5};

std::cout << ul_list2;

ASSERT_FALSE(ul_list2.empty());
int counter = 1;
for (const auto& e : ul_list2) {
EXPECT_EQ(e, counter);
++counter;
}

// Move semantic check.
ul_list1.swap(ul_list2);

counter = 1;
for (const auto& e : ul_list1) {
EXPECT_EQ(e, counter);
++counter;
}

EXPECT_TRUE(ul_list2.empty());
}

TEST(unrolled_linked_list, CopyAndMoveAssign) {
TestConsoleLogger t_log("CopyAndMoveAssign");

unrolled_linked_list<char, 8> alphabet = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
ASSERT_EQ(alphabet.size(), 26u);
std::cout << "Alphabet list: " << alphabet;

auto oth_alphabet = alphabet;
ASSERT_EQ(oth_alphabet.size(), 26u);
std::cout << "Other alphabet list: " << oth_alphabet;

// Move.
auto another_alphabet(std::move(alphabet));
auto another_one_alphabet = std::move(oth_alphabet);
ASSERT_EQ(another_alphabet.size(), 26u);
ASSERT_EQ(another_one_alphabet.size(), 26u);
}

TEST(unrolled_linked_list, Algorithms) {
TestConsoleLogger t_log("Algorithms");

unrolled_linked_list<float> f_list = {5.54f, -8.08f, 0.f, 1.f, -.97f};

t_log.say("std::find");
EXPECT_EQ(std::find(f_list.begin(), f_list.end(), 10000.f), f_list.end());

EXPECT_EQ(*std::find(f_list.begin(), f_list.end(), 1.f), 1.f);
EXPECT_NE(std::find(f_list.begin(), f_list.end(), -.97f), f_list.end());

t_log.say("std::find_if");
EXPECT_EQ(
        std::find_if(f_list.begin(), f_list.end(), [](float x) { return x > 6; }),
        f_list.end());

EXPECT_EQ(std::find_if(f_list.begin(), f_list.end(),
                       [](float x) { return x < -5; }),
++f_list.begin());
EXPECT_NE(
        std::find_if(f_list.begin(), f_list.end(), [](float x) { return x < 0; }),
        f_list.end());

t_log.say("std::all_of");
EXPECT_TRUE(std::all_of(f_list.begin(), f_list.end(),
                        [](float x) { return x + 9 > 0; }));

t_log.say("std::any_of");
EXPECT_FALSE(
        std::any_of(f_list.begin(), f_list.end(), [](float x) { return x > 6; }));
}

TEST(unrolled_linked_list, PushAndPopBack) {
TestConsoleLogger t_log("PushAndPopBack");

unrolled_linked_list<double> double_list;

t_log.say("Pushing first 8 elements back:");
double_list.push_back(1.9);
EXPECT_EQ(double_list.back(), 1.9);
double_list.push_back(2.8);
EXPECT_EQ(double_list.back(), 2.8);
double_list.push_back(3.7);
EXPECT_EQ(double_list.back(), 3.7);
double_list.push_back(4.6);
EXPECT_EQ(double_list.back(), 4.6);
double_list.push_back(5.5);
EXPECT_EQ(double_list.back(), 5.5);
double_list.push_back(6.4);
EXPECT_EQ(double_list.back(), 6.4);
double_list.push_back(7.3);
EXPECT_EQ(double_list.back(), 7.3);
double_list.push_back(8.2);
EXPECT_EQ(double_list.back(), 8.2);
std::cout << double_list;

t_log.say("And another one:");
double_list.push_back(9.1);
EXPECT_EQ(double_list.back(), 9.1);
std::cout << double_list;

EXPECT_EQ(double_list.size(), 9u);

t_log.say("And now let's pop 1 element back:");
double_list.pop_back();
EXPECT_EQ(double_list.back(), 8.2);
std::cout << double_list;
t_log.say("And another one:");
double_list.pop_back();
EXPECT_EQ(double_list.back(), 7.3);
std::cout << double_list;
t_log.say("Pop all remaining elements:");
double_list.pop_back();
EXPECT_EQ(double_list.back(), 6.4);
double_list.pop_back();
EXPECT_EQ(double_list.back(), 5.5);
double_list.pop_back();
EXPECT_EQ(double_list.back(), 4.6);
double_list.pop_back();
EXPECT_EQ(double_list.back(), 3.7);
double_list.pop_back();
EXPECT_EQ(double_list.back(), 2.8);
double_list.pop_back();
EXPECT_EQ(double_list.back(), 1.9);
double_list.pop_back();

EXPECT_TRUE(double_list.empty());
std::cout << double_list;
}

TEST(unrolled_linked_list, InsertAndErase) {
TestConsoleLogger t_log("InsertAndErase");

unrolled_linked_list<std::string, 5> words_list;
ASSERT_EQ(words_list.begin(), words_list.end());

// Insert to empty list.
auto it = words_list.insert(words_list.begin(), "Hello");
EXPECT_EQ(it, words_list.begin());
std::cout << words_list;

it = words_list.insert(words_list.begin(), "world");
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "world"));
std::cout << words_list;

t_log.say("Fill first bucket to full:");

words_list.push_back("I");
words_list.push_back("am");
words_list.push_back("aaaaaaaalesha");
std::cout << words_list;

t_log.say("Insert \"my\" after \"Hello\" in full bucket:");

it = words_list.insert(words_list.begin(), "my");
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "my"));
std::cout << words_list;

t_log.say("Add the third node:");
words_list.push_back("and");

t_log.say("And fill the second bucket to insert to the fill one:");
words_list.push_back("I");
std::cout << words_list;

auto i_it = std::find(words_list.begin(), words_list.end(), "I");
it = words_list.insert(i_it, "$%^&");
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "$%^&"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "I");
it = words_list.insert(i_it, "{what is that?}");
EXPECT_EQ(it,
        std::find(words_list.begin(), words_list.end(), "{what is that?}"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "I");
it = words_list.insert(i_it, "¯\\_(ツ)_/¯");
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "¯\\_(ツ)_/¯"));
std::cout << words_list;

t_log.say("Insert in full second bucket:");
i_it = std::find(words_list.begin(), words_list.end(), "I");
it = words_list.insert(i_it, "idk");
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "idk"));
std::cout << words_list;

/// Erase.
t_log.say("And now let's erase some rubbish which was inserted:");
i_it = std::find(words_list.begin(), words_list.end(), "$%^&");
it = words_list.erase(i_it);
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "am"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "and");
it = words_list.erase(i_it);
EXPECT_EQ(it,
++std::find(words_list.begin(), words_list.end(), "aaaaaaaalesha"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "aaaaaaaalesha");
++i_it;
it = words_list.erase(i_it);

EXPECT_EQ(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "aaaaaaaalesha");
it = words_list.erase(i_it);
EXPECT_EQ(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "¯\\_(ツ)_/¯");
it = words_list.erase(i_it);
EXPECT_EQ(it,
        std::find(words_list.begin(), words_list.end(), "{what is that?}"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "idk");
it = words_list.erase(i_it);
EXPECT_EQ(it,
        std::find(words_list.begin(), words_list.end(), "{what is that?}"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "{what is that?}");
it = words_list.erase(i_it);
EXPECT_EQ(it, std::find(words_list.begin(), words_list.end(), "am"));
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "am");
it = words_list.erase(i_it);
EXPECT_EQ(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "I");
it = words_list.erase(i_it);
EXPECT_EQ(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "my");
it = words_list.erase(i_it);
EXPECT_NE(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "Hello");
it = words_list.erase(i_it);
EXPECT_NE(it, words_list.end());
std::cout << words_list;

i_it = std::find(words_list.begin(), words_list.end(), "world");
it = words_list.erase(i_it);
EXPECT_EQ(it, words_list.end());
EXPECT_TRUE(words_list.empty());
std::cout << words_list;
}

struct Unit {
    std::string name_;
    bool friendliness_ = true;
    size_t health_ = 100u;
};

std::ostream& operator<<(std::ostream& out, const Unit& unit) {
    out << unit.name_;
    return out;
}

TEST(unrolled_linked_list, AnotherMethods) {
TestConsoleLogger t_logger("AnotherMethods");

unrolled_linked_list<Unit, 4> units = {{"Knight"},
                                       {"Goblin", false},
                                       {"Orc", false, 200u},
                                       {"Healer", true, 50u},
                                       {"Wizard"}};
EXPECT_EQ(units.bucket_capacity(), 4);

std::cout << units;

t_logger.say("front");
units.front() = {"Hero"};
const Unit hero = units.front();
EXPECT_EQ(hero.name_, "Hero");

t_logger.say("back");
units.back() = {"Black_Wizard"};
const Unit wiz = units.back();
EXPECT_EQ(wiz.name_, "Black_Wizard");

t_logger.say("operator[]");
const Unit orc = units[2];
EXPECT_EQ(orc.name_, "Orc");
EXPECT_FALSE(orc.friendliness_);
EXPECT_EQ(orc.health_, 200u);

units[3] = {"White_Wizard", true, 100u};
EXPECT_EQ("White_Wizard", units[3].name_);
std::cout << units;

t_logger.say("at");
EXPECT_THROW(units.at(99u), std::out_of_range);
const Unit goblin = units.at(1);
EXPECT_EQ(goblin.name_, "Goblin");
units.at(1) = {"Hobgoblin", false, 150u};
EXPECT_EQ(units.at(1).name_, "Hobgoblin");
EXPECT_EQ(units.at(1).health_, 150u);

t_logger.say("clear");
EXPECT_FALSE(units.empty());
EXPECT_NE(units.begin(), units.end());
units.clear();
EXPECT_TRUE(units.empty());
EXPECT_EQ(units.begin(), units.end());
}