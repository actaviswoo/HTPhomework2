#include "gtest/gtest.h"
#include "../src/linked_list.h"
#include <forward_list>
#include <algorithm>

TEST(LinkedListTest, ConstructorDefault) {
    LinkedList<int> list;
    std::forward_list<int> flist;
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(flist.empty());
}

TEST(LinkedListTest, ConstructorParametr) {
    LinkedList<int> list(1);
    std::forward_list<int> flist(1);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.front(), 1);
}

TEST(LinkedListTest, ConstructorCopy) {
    LinkedList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    std::forward_list<int> flist;
    flist.push_front(1);
    flist.push_front(2);
    flist.push_front(3);
    int expected[] = {3, 2, 1};
    LinkedList<int> copy(list);
    std::forward_list<int> fcopy(flist);
    int index = 0;
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
    index = 0;
    for (auto it = fcopy.begin(); it != fcopy.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedListTest, ConstructorMove) {
    LinkedList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    std::forward_list<int> flist;
    flist.push_front(1);
    flist.push_front(2);
    flist.push_front(3);
    LinkedList<int> move(std::move(list));
    std::forward_list<int> fmove(std::move(flist));
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(flist.empty());
    int expected[] = {3, 2, 1};
    int index = 0;
    for (auto it = move.begin(); it != move.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
    index = 0;
    for (auto it = fmove.begin(); it != fmove.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedListTest, ConstructorInitializerList) {
    LinkedList<int> list {1, 2, 3};
    std::forward_list<int> flist {1, 2, 3};
    int expected[] = {1, 2, 3};
    int index = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
    index = 0;
    for (auto it = flist.begin(); it != flist.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedListTest, AssignmentOperatorCopy) {
    LinkedList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    std::forward_list<int> flist;
    flist.push_front(1);
    flist.push_front(2);
    flist.push_front(3);
    LinkedList<int> copy;
    copy = list;
    std::forward_list<int> fcopy;
    fcopy = flist;
    int expected[] = {3, 2, 1};
    int index = 0;
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
    index = 0;
    for (auto it = fcopy.begin(); it != fcopy.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedListTest, AssignmentOperatorMove) {
    LinkedList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    std::forward_list<int> flist;
    flist.push_front(1);
    flist.push_front(2);
    flist.push_front(3);
    LinkedList<int> move;
    move = std::move(list);
    std::forward_list<int> fmove;
    fmove = std::move(flist);
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(flist.empty());
    int expected[] = {3, 2, 1};
    int index = 0;
    for (auto it = move.begin(); it != move.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
    index = 0;
    for (auto it = fmove.begin(); it != fmove.end(); ++it) {
        ASSERT_EQ(*it, expected[index++]);
    }
}

TEST(LinkedListTest, Front) {
    LinkedList<int> list {1, 2, 3};
    std::forward_list<int> flist {1, 2, 3};
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(flist.front(), 1);
}

TEST(LinkedListTest, FrontConst) {
    const LinkedList<int> list_const {1, 2, 3};
    const std::forward_list<int> flist_const {1, 2, 3};
    ASSERT_EQ(list_const.front(), 1);
    ASSERT_EQ(flist_const.front(), 1);
}

TEST(LinkedListTest, IteratorBeginEnd) {
    LinkedList<int> list {1, 2, 3};
    std::forward_list<int> flist {1, 2, 3};
    auto it_begin = list.begin();
    auto it_end = list.end();
    auto fit_begin = flist.begin();
    auto fit_end = flist.end();
    ASSERT_NE(it_begin, it_end);
    ASSERT_NE(fit_begin, fit_end);
}

TEST(LinkedListTest, ConstIteratorBeginEnd) {
    const LinkedList<int> list_const {1, 2, 3};
    const std::forward_list<int> flist {1, 2, 3};
    auto it_begin = list_const.cbegin();
    auto it_end = list_const.cend();
    auto fit_begin = flist.cbegin();
    auto fit_end = flist.cend();
    ASSERT_NE(it_begin, it_end);
    ASSERT_NE(fit_begin, fit_end);
}


TEST(LinkedListTest, Empty) {
    LinkedList<int> list;
    std::forward_list<int> flist;
    ASSERT_TRUE(list.empty());
    ASSERT_TRUE(flist.empty());
    list.push_front(1);
    flist.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_FALSE(flist.empty());
}


TEST(LinkedListTest, PushFrontLValue) {
    LinkedList<int> list;
    std::forward_list<int> flist;
    list.push_front(1);
    flist.push_front(1);
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(flist.front(), 1);
}

TEST(LinkedListTest, PushFrontRValue) {
    LinkedList<int> list;
    std::forward_list<int> flist;
    list.push_front(1);
    list.push_front(2);
    flist.push_front(1);
    flist.push_front(2);
    ASSERT_EQ(list.front(), 2);
    ASSERT_EQ(flist.front(), 2);
}

TEST(LinkedListTest, PopFront) {
    LinkedList<int> list;
    std::forward_list<int> flist;
    list.push_front(1);
    list.push_front(2);
    list.pop_front();
    flist.push_front(1);
    flist.push_front(2);
    flist.pop_front();
    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(flist.front(), 1);
}

TEST(LinkedListTest, Find) {
    LinkedList<int> list {1, 2, 3, 4, 5};
    std::forward_list<int> flist{1, 2, 3, 4, 5};
    auto it = list.find(3);
    ASSERT_NE(it, list.end());
    ASSERT_EQ(*it, 3);
    auto fit = std::find(flist.begin(), flist.end(), 3);
    ASSERT_NE(fit, flist.end());
    ASSERT_EQ(*fit, 3);
    ASSERT_EQ(list.find(6), list.end());
    ASSERT_EQ(std::find(flist.begin(), flist.end(), 6), flist.end());
}

TEST(LinkedListTest, FindConst) {
    const LinkedList<int> list {1, 2, 3, 4, 5};
    const std::forward_list<int> flist{1, 2, 3, 4, 5};
    auto it = list.find(3);
    ASSERT_NE(it, list.cend());
    ASSERT_EQ(*it, 3);
    auto fit = std::find(flist.begin(), flist.end(), 3);
    ASSERT_NE(fit, flist.end());
    ASSERT_EQ(*fit, 3);
    ASSERT_EQ(list.find(6), list.cend());
    ASSERT_EQ(std::find(flist.begin(), flist.end(), 6), flist.end());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}