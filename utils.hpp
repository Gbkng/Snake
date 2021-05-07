///////////////////////////////////////
// Project : GuySnake
// Author : Guillaume Brooking
// Date : May 2021
// Email : guillaume.brooking@gmail.com
///////////////////////////////////////

#ifndef GUYBRO_UTILS_HPP_
#define GUYBRO_UTILS_HPP_

#include <cstdlib>
#include "SFML/Graphics.hpp"

sf::Color generateRandomColor();

// return a random integer in interval [0, N], bounds included
int generateRandomInteger(int N);

// // useless for now
// template <class T>
// void insertInSortedList(std::vector<T> &sortedList, T element)
// {
//   const int size = sortedList.size();

//   if (element > sortedList.back()) // easy case !
//   {
//     sortedList.push_back(element);
//   }
//   else
//   {
//     int precedentIdx = 0;
//     while (sortedList.at(precedentIdx) < element) // no overflow thanks to the precedent test (cf. esay cas)
//     {
//       precedentIdx++;
//     } // k is now equal to the index of the element just before the index of the element to add

//     // time to make some place for the new budy...
//     sortedList.resize(size + 1);
//     for (int k = size - 1; k > precedentIdx; k--)
//     { // reverse order for aliasing issue
//       sortedList.at(k + 1) = sortedList.at(k);
//     }
//     // insert the budy. Welcome.
//     sortedList.at(precedentIdx + 1) = element;
//   }
// }

#endif