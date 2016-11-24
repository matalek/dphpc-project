#ifndef MERGE_HULL
#define MERGE_HULL

#include <vector>
#include "geometric_helpers.hh"
#include <stdio.h>
#include <algorithm>
#include "data_structures/convex_hull_representation.hh"


using namespace std;

int turnRight(POINT * a, POINT * b, POINT * c) {
    return DetPointer(a,b,c) < 0;
}

int turnLeft(POINT * a, POINT * b, POINT * c) {
    return DetPointer(a,b,c) > 0;
}

int lowerTangentA(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    POINT * a = hullA.get_point(aIndex);
    POINT * u = hullA.get_point(hullA.go_counter_clockwise(aIndex));
    POINT * w = hullA.get_point(hullA.go_clockwise(aIndex));
    POINT * b = hullB.get_point(bIndex);
    return !(turnLeft(b, a, u) || turnLeft(b, a, w));
}

// A is always the left hull, B is the right one
int upperTangentA(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    POINT * a = hullA.get_point(aIndex);
    POINT * u = hullA.get_point(hullA.go_counter_clockwise(aIndex));
    POINT * w = hullA.get_point(hullA.go_clockwise(aIndex));
    POINT * b = hullB.get_point(bIndex);
    return !(turnRight(b, a, u) || turnRight(b, a, w));
}

int lowerTangentB(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    POINT * a = hullA.get_point(aIndex);
    POINT * u = hullB.get_point(hullB.go_counter_clockwise(bIndex));
    POINT * w = hullB.get_point(hullB.go_clockwise(bIndex));
    POINT * b = hullB.get_point(bIndex);
    return !(turnRight(a, b, u) || turnRight(a, b, w));
    //return upperTangentA(hullB, hullA, bIndex, aIndex);
}

int upperTangentB(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    POINT * a = hullA.get_point(aIndex);
    POINT * u = hullB.get_point(hullB.go_counter_clockwise(bIndex));
    POINT * w = hullB.get_point(hullB.go_clockwise(bIndex));
    POINT * b = hullB.get_point(bIndex);
    return !(turnLeft(a, b, u) || turnLeft(a, b, w));
}

int findLowerTangentA(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    while (!lowerTangentA(hullA, hullB, aIndex, bIndex)) {
        aIndex = hullA.go_clockwise(aIndex);
    }
    return aIndex;
}

int findLowerTangentB(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    while (!lowerTangentB(hullA, hullB, aIndex, bIndex)) {
        bIndex = hullB.go_counter_clockwise(bIndex);
    }
    return bIndex;
}

int findUpperTangentA(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    while (!upperTangentA(hullA, hullB, aIndex, bIndex)) {
        aIndex = hullA.go_counter_clockwise(aIndex);
    }
    return aIndex;
}

int findUpperTangentB(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, int aIndex, int bIndex) {
    while (!upperTangentB(hullA, hullB, aIndex, bIndex)) {
        bIndex=hullB.go_clockwise(bIndex);
    }
    return bIndex;
}

//TODO: make it more general
pair<int,int> findLowerT(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB) {
    pair<char, double> returnValues;
    int aIndex = hullA.find_rightmost_point();
    int bIndex = hullB.find_leftmost_point();
    while (!(lowerTangentA(hullA, hullB, aIndex, bIndex) && lowerTangentB(hullA, hullB, aIndex, bIndex))) {
        aIndex = findLowerTangentA(hullA, hullB, aIndex, bIndex);
        bIndex = findLowerTangentB(hullA, hullB, aIndex, bIndex);
    }
    returnValues.first = aIndex;
    returnValues.second = bIndex;
    return returnValues;
}

pair<int,int> findUpperT(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB) {
    pair<char, double> returnValues;
    int aIndex = hullA.find_rightmost_point();
    int bIndex = hullB.find_leftmost_point();

    while (!(upperTangentA(hullA, hullB, aIndex, bIndex) && upperTangentB(hullA, hullB, aIndex, bIndex))) {
        aIndex = findUpperTangentA(hullA, hullB, aIndex, bIndex);
        bIndex = findUpperTangentB(hullA, hullB, aIndex, bIndex);
    }
    returnValues.first = aIndex;
    returnValues.second = bIndex;
    return returnValues;
}

vector<POINT*>  mergeVectors(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB, pair <int, int> lowT, pair <int, int> upperT){
    vector<POINT*> mergedVector;
    int hullIndex = upperT.first;
    while (1) {
        mergedVector.push_back(hullA.get_point(hullIndex));
        if(hullIndex == lowT.first) break;
        hullIndex = hullA.go_counter_clockwise(hullIndex);
    };
    hullIndex = lowT.second;
    while (1) {
        mergedVector.push_back(hullB.get_point(hullIndex));
        if(hullIndex == upperT.second) break;
        hullIndex = hullB.go_counter_clockwise(hullIndex);
    };
    return mergedVector;
}

vector<POINT*> mergeHulls(ConvexHullRepresentation &hullA, ConvexHullRepresentation &hullB) {
    pair <int, int> lowT = findLowerT(hullA, hullB);
    pair <int,int> upperT = findUpperT(hullA, hullB);
    return mergeVectors(hullA, hullB, lowT, upperT);
}

#endif // MERGE_HULL
