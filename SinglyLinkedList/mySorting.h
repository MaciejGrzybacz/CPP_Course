//
// Created by 006ma on 21.04.2024.
//

#ifndef MYSORTING_H
#define MYSORTING_H
#include <vector>
#include <algorithm>
#include "myList.h"

template<typename T=int, typename S>
void mySort(S &list) {
    for (int i = 0; i < (int)std::size(list); i++) {
        for (int j = 0; j < (int)std::size(list) - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                std::swap(list[j], list[j + 1]);
            }
        }
    }
}

template<typename T>
void mySort(MyList<T> &list) {
    if (list.size() <= 1)
        return;
    for (auto i = list.begin(); i != list.end(); i++) {
        auto val = i;
        for (auto j = i; j != list.end(); j++) {
            if (*j < *val) {
                val = j;
            }
        }
        std::swap(*i, *val);
    }
}

template<int size1, int size2>
void mySort(char (&list)[size1][size2]) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1 - 1; j++) {
            char str1[size2], str2[size2];
            strncpy(str1, list[j], size2 - 1);
            str1[size2 - 1] = '\0';
            strncpy(str2, list[j + 1], size2 - 1);
            str2[size2 - 1] = '\0';
            for (int k = 0; k < size2; k++) {
                str1[k] = toupper(str1[k]);
                str2[k] = toupper(str2[k]);
            }
            if (strcmp(str1, str2) > 0) {
                std::swap(list[j], list[j + 1]);
            }
        }
    }

}

#endif //MYSORTING_H
