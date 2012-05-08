#ifndef __SORTER_HPP__
#define __SORTER_HPP__

#include <vector>

class Sorter {
public:
    void set_values(std::vector<int> values); // 非破壊的
    std::vector<int> get_values();
    virtual void sort() = 0;
    Sorter() = default;         //これがないとコンパイル通らない
    virtual ~Sorter() = default; //仮想デストラクタ

protected:
    std::vector<int> values;

    // コピー・ムーブ禁止
    Sorter(Sorter const&) = delete;
    Sorter(Sorter&&) = delete;
    Sorter& operator = (Sorter const&) = delete;
    Sorter& operator = (Sorter&&) = delete;

};

void Sorter::set_values(std::vector<int> values) {
    this->values = values;
}

std::vector<int> Sorter::get_values() {
    return this->values;
}

#endif
