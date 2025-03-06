#include "tcyclic_list.h"
#include "tpolynoms.h"

#include <gtest.h>

#include <string>
#include <vector>

// Тест с std::string
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
    EXPECT_EQ(copy.size(), 2); // Проверяем, что копия не изменилась
    EXPECT_EQ(copy[0], "start");
    EXPECT_EQ(copy[1], "world");

    EXPECT_EQ(copy.find("world"), 1);
    EXPECT_EQ(copy.find("notfound"), -1);
}

// Тест с std::vector<int>
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

    // Проверка на глубокое копирование
    CyclicList<std::vector<int>> copy = list;
    list[0][0] = 99; // Меняем оригинал
    EXPECT_EQ(copy[0][0], 6);  // Копия не должна измениться
    list.clear();
    EXPECT_EQ(copy.size(), 2);
}

// Пользовательский класс (без операторов сравнения)
class MyData {
public:
    int id;
    std::string name;

    MyData(int id, const std::string& name) : id(id), name(name) {}
    // Операторы сравнения не определены намеренно, чтобы проверить базовую работу
    // (копирование, вставку, удаление) без использования сравнения.
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

    // Проверка на глубокое копирование
    CyclicList<MyData> copy;
    copy = list; // Присваивание

    list[0].id = 10; // Меняем оригинал.
    EXPECT_EQ(copy[0].id, 2); // Копия не должна измениться.

    // Проверка на глубокое копирование
    CyclicList<MyData> copy2(list); // Присваивание

    list[0].id = 10; // Меняем оригинал.
    EXPECT_EQ(copy2[0].id, 10); // Копия не должна измениться.
}

// Тест с большим количеством элементов (std::string)
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

// Тест смешанных операций с разными типами
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