#include "tcyclic_list.h"
#include "tpolynoms.h"

#include <gtest.h>

#include <string>
#include <vector>

// ���� � std::string
TEST(CyclicListTest, StringOperations) {
    CyclicList<std::string> list;
    list.push_back("hello");
    list.push_back("world");
    list.push_front("start");
    EXPECT_EQ(list[0], "start");
    EXPECT_EQ(list[1], "hello");
    EXPECT_EQ(list[2], "world");

    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[1], "world");

    CyclicList<std::string> copy = list;
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(copy.size(), 2); // ���������, ��� ����� �� ����������
    EXPECT_EQ(copy[0], "start");
    EXPECT_EQ(copy[1], "world");

    EXPECT_EQ(copy.find("world"), 1);
    EXPECT_EQ(copy.find("notfound"), -1);
}

// ���� � std::vector<int>
TEST(CyclicListTest, VectorOperations) {
    CyclicList<std::vector<int>> list;
    list.push_back({ 1, 2, 3 });
    list.push_back({ 4, 5 });
    list.insert(1, { 6, 7 });

    EXPECT_EQ(list[0][0], 1);
    EXPECT_EQ(list[1][1], 7);
    EXPECT_EQ(list[2][0], 4);

    list.erase(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0][0], 6);

    // �������� �� �������� �����������
    CyclicList<std::vector<int>> copy = list;
    list[0][0] = 99; // ������ ��������
    EXPECT_EQ(copy[0][0], 6);  // ����� �� ������ ����������
    list.clear();
    EXPECT_EQ(copy.size(), 2);
}

// ���������������� ����� (��� ���������� ���������)
class MyData {
public:
    int id;
    std::string name;

    MyData(int id, const std::string& name) : id(id), name(name) {}
    // ��������� ��������� �� ���������� ���������, ����� ��������� ������� ������
    // (�����������, �������, ��������) ��� ������������� ���������.
};

TEST(CyclicListTest, CustomClassOperations) {
    CyclicList<MyData> list;
    list.push_back(MyData(1, "one"));
    list.push_back(MyData(2, "two"));

    EXPECT_EQ(list[0].id, 1);
    EXPECT_EQ(list[1].name, "two");

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0].id, 2);

    // �������� �� �������� �����������
    CyclicList<MyData> copy;
    copy = list; // ������������

    list[0].id = 10; // ������ ��������.
    EXPECT_EQ(copy[0].id, 2); // ����� �� ������ ����������.

    // �������� �� �������� �����������
    CyclicList<MyData> copy2(list); // ������������

    list[0].id = 10; // ������ ��������.
    EXPECT_EQ(copy2[0].id, 10); // ����� �� ������ ����������.
}

// ���� � ������� ����������� ��������� (std::string)
TEST(CyclicListTest, LargeStringList) {
    CyclicList<std::string> list;
    const int largeSize = 1000;
    for (int i = 0; i < largeSize; ++i) {
        list.push_back(std::to_string(i));
    }
    EXPECT_EQ(list.size(), largeSize);
    EXPECT_EQ(list[500], "500");
    list.clear();
    EXPECT_EQ(list.size(), 0);
}

// ���� ��������� �������� � ������� ������
TEST(CyclicListTest, MixedTypeOperations) {
    CyclicList<int> intList;
    intList.push_back(10);
    intList.push_front(5);
    CyclicList<int> intCopy = intList;
    intCopy.pop_front();
    EXPECT_EQ(intCopy.size(), 1);
    EXPECT_EQ(intCopy[0], 10);

    CyclicList<std::string> stringList;
    stringList.push_back("hello");
    stringList.insert(0, "world");
    EXPECT_EQ(stringList[0], "world");
    EXPECT_EQ(stringList[1], "hello");

    CyclicList<std::vector<int>> vectorList;
    vectorList.push_back({ 1, 2 });
    vectorList.push_back({ 3, 4 });
    vectorList.erase(0);
    EXPECT_EQ(vectorList.size(), 1);
    EXPECT_EQ(vectorList[0][1], 4);
}