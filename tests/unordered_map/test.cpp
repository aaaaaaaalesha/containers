// Copyright 2020 aaaaaaaalesha <sks2311211@mail.ru>

#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <iterator.hpp>
#include <string>
#include <unordered_map.hpp>
#include <unordered_map>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(unorderedMap, InitTest) {
  UnorderedMap<int, std::string> firstContainer;

  ASSERT_TRUE(firstContainer.empty());

  firstContainer[1] = "aaaaaaaalesha";
  firstContainer[6] = "Hamsterrhino";
  firstContainer[3] = "mmmmurad";
  firstContainer[9] = "RKulagin";
  firstContainer[15] = "SergeyShIU814";
  firstContainer[2] = "Farid057";

  ASSERT_EQ(firstContainer[1], "aaaaaaaalesha");
  EXPECT_EQ(firstContainer[6], "Hamsterrhino");
  EXPECT_EQ(firstContainer[3], "mmmmurad");
  ASSERT_EQ(firstContainer[9], "RKulagin");
  EXPECT_EQ(firstContainer[15], "SergeyShIU814");
  EXPECT_EQ(firstContainer[2], "Farid057");

  ASSERT_EQ(firstContainer.size(), 6);

  UnorderedMap<size_t, std::string> oth({{2, "Farid057"},
                                         {6, "Hamsterrhino"},
                                         {1, "aaaaaaaalesha"},
                                         {9, "RKulagin"},
                                         {15, "SergeyShIU814"},
                                         {3, "mmmmurad"}});

  EXPECT_EQ(oth[1], "aaaaaaaalesha");
  EXPECT_EQ(oth[6], "Hamsterrhino");
  EXPECT_EQ(oth[3], "mmmmurad");
  EXPECT_EQ(oth[9], "RKulagin");
  EXPECT_EQ(oth[15], "SergeyShIU814");
  EXPECT_EQ(oth[2], "Farid057");
}

TEST(unorderedMap, CopyAssign) {
  UnorderedMap<char, float> uM;
  uM['a'] = 1.1;
  uM['i'] = 2.7;
  uM['o'] = 0.;
  uM['z'] = 45678.2;

  UnorderedMap<char, float> cpyUM(uM);

  ASSERT_EQ(uM.size(), cpyUM.size());
  ASSERT_EQ(uM['a'], cpyUM['a']);
  ASSERT_EQ(uM['i'], cpyUM['i']);
  ASSERT_EQ(uM['o'], cpyUM['o']);
  ASSERT_EQ(uM['z'], cpyUM['z']);

  UnorderedMap<char, float> newUM;
  newUM = cpyUM;

  ASSERT_EQ(uM.bucketCount(), newUM.bucketCount());
  ASSERT_EQ(newUM['a'], cpyUM['a']);
  ASSERT_EQ(newUM['i'], cpyUM['i']);
  ASSERT_EQ(newUM['o'], cpyUM['o']);
  ASSERT_EQ(newUM['z'], cpyUM['z']);
}

TEST(unorderedMap, IteratorsTest) {
  // key - name, value - score
  UnorderedMap<std::string, size_t> students;

  ASSERT_EQ(students.begin(), students.end());

  students["Farid057"] = 98;
  students["aaaaaaaalesha"] = 186;
  students["RKulagin"] = 205;
  students["SergeyShIU814"] = 77;
  students["mmmmurad"] = 120;

  UnorderedMap<std::string, size_t>::iterator it_ = students.begin();

  std::cout << it_->first << " " << it_->second << std::endl;
  ASSERT_EQ(it_, students.begin());
  ++it_;
  std::cout << it_->first << " " << it_->second << std::endl;
  ++it_;
  std::cout << it_->first << " " << it_->second << std::endl;
  ++it_;
  std::cout << it_->first << " " << it_->second << std::endl;
  ++it_;
  std::cout << it_->first << " " << it_->second << std::endl;
  ++it_;
  ASSERT_EQ(it_, students.end());

  // Range cycle
  std::cout << "Some students here: " << std::endl;
  for (const auto &e : students) {
    std::cout << e.first << " " << e.second << std::endl;
  }

  // Postincrement test.
  Iterator<std::string, size_t> it = students.begin();
  Iterator<std::string, size_t> othIt = it;

  it = othIt++;
  ASSERT_FALSE(it == othIt);
  ASSERT_TRUE(it == students.begin());

  ASSERT_EQ(*it, *students.begin());
}

struct Unit {
  bool friendliness;
  bool canAttack;
  std::string info;
};

TEST(unorderedMap, Methods) {
  UnorderedMap<std::string, Unit> unitsBook;

  unitsBook["Hero"] = {true, true, "The main character of our book."};
  unitsBook["Knight"] = {true, true, "Can help in fights against Enemies."};
  unitsBook["Enemy"] = {false, true, "Caution! They can kill you!"};
  unitsBook["Healer"] = {true, false, "Can heal the friendliness units."};

  /// at()
  ASSERT_EQ(unitsBook.at("Hero").canAttack, true);
  ASSERT_EQ(unitsBook.at("Enemy").friendliness, false);
  ASSERT_EQ(unitsBook.at("Healer").info, "Can heal the friendliness units.");

  EXPECT_THROW(unitsBook.at("Builder"), std::out_of_range);

  /// insert()
  Unit builder = {true, false, "Can build a cottage for you."};
  std::pair<std::string, Unit> Builder = std::make_pair("Builder", builder);

  std::pair<Iterator<std::string, Unit>, bool> resultOfInsert =
      unitsBook.insert(Builder);
  ASSERT_TRUE(resultOfInsert.second);

  // Try to insert Builder again - it should not be inserted.
  resultOfInsert = unitsBook.insert(Builder);
  ASSERT_TRUE(!resultOfInsert.second);

  /// find()
  auto it1 = unitsBook.find("Builder");
  auto it2 = unitsBook.find("Hero");

  ASSERT_EQ(it1->first, "Builder");
  ASSERT_EQ(it2->second.info, "The main character of our book.");

  /// erase()
  // And now we only want to talk about good units.
  // We don't want to see Enemies anymore. Remove it!
  EXPECT_EQ(unitsBook.erase("Enemy"), 1);
  // Try to erase Enemy again - it should not be erased.
  EXPECT_EQ(unitsBook.erase("Enemy"), 0);

  /// swap()
  UnorderedMap<std::string, Unit> pageFromAnotherBook;
  pageFromAnotherBook["Rat"] = {false, true, "Can bite"};

  unitsBook.swap(pageFromAnotherBook);

  EXPECT_EQ(unitsBook.size(), 1);
  EXPECT_EQ(pageFromAnotherBook.size(), 4);
  for (const auto &e : pageFromAnotherBook) {
    EXPECT_EQ(e.second.friendliness, true);
  }

  pageFromAnotherBook.swap(unitsBook);

  EXPECT_EQ(unitsBook.size(), 4);
  EXPECT_EQ(pageFromAnotherBook.size(), 1);
  for (const auto &e : unitsBook) {
    EXPECT_EQ(e.second.friendliness, true);
  }

  /// clear()
  // Manuscripts don't burn...
  // Fortunately, we do not have a manuscript at all ;)
  unitsBook.clear();
  ASSERT_TRUE(unitsBook.empty());
}

TEST(unorderedMap, checkRehash) {
  UnorderedMap<size_t, char> alphabet;

  alphabet[1] = 'a';
  alphabet[2] = 'b';
  alphabet[3] = 'c';
  alphabet[4] = 'd';
  alphabet[5] = 'e';
  alphabet[6] = 'f';
  alphabet[7] = 'g';
  alphabet[8] = 'h';
  alphabet[9] = 'i';
  alphabet[10] = 'j';
  alphabet[11] = 'k';
  alphabet[12] = 'l';
  alphabet[13] = 'm';
  alphabet[14] = 'n';
  alphabet[15] = 'o';
  alphabet[16] = 'p';
  alphabet[17] = 'q';
  alphabet[18] = 'r';
  alphabet[19] = 's';
  alphabet[20] = 't';
  alphabet[21] = 'u';
  alphabet[22] = 'v';
  alphabet[23] = 'w';

  // Rehashing here... (loadFactor > maxLoadFactor)
  EXPECT_GT(alphabet.loadFactor(), alphabet.maxLoadFactor());

  alphabet[24] = 'x';
  alphabet[25] = 'y';
  alphabet[26] = 'z';

  EXPECT_EQ(alphabet.bucketCount(), 36);

  EXPECT_EQ(alphabet.at(20), 't');

  EXPECT_EQ(alphabet.erase(24), 1);

  EXPECT_EQ(alphabet.find(24), alphabet.end());

  EXPECT_EQ((alphabet.insert({24, 'X'})).second, true);

  EXPECT_NE(alphabet.find(24), alphabet.end());
}
