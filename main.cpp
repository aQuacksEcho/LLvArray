/*
 *******************************************************************************
 * Compares a Double Linked List (a C++ "list" container) to an Array (a C++
 * "vector" container) by timing certain removal operations (at front, 1/4, 1/2,
 * 3/4, and back).
 *
 * Timing is done using a "high_precision_clock" from the C++11 standard.
 *
 * Timing information is output to terminal on completion.
 *
 * Do whatever you want with this, I guess. No real license.
 *
 * Authored by Isaac Steele
 * Started:        5/1/2014
 * Last Edited:    5/1/2014
 *******************************************************************************
 */

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <chrono>

int main()
{
    std::vector<int> testVector;        //Vector to use in testing
    std::vector<int>::iterator vit;     //Vector Iterator to use in testing

    std::list<int> testList;            //Linked List to use in testing
    std::list<int>::iterator lit;       //Linked List Iterator to use in testing

    std::chrono::high_resolution_clock::time_point vt1; //Time points for
    std::chrono::high_resolution_clock::time_point vt2; //use in Vector tests

    std::chrono::high_resolution_clock::time_point lt1; //Time points for
    std::chrono::high_resolution_clock::time_point lt2; //use in List tests

    std::chrono::duration<double> vFrontPopT;
    std::chrono::duration<double> vBackPopT;
    std::chrono::duration<double> vQuarterEraseT;
    std::chrono::duration<double> vHalfEraseT;
    std::chrono::duration<double> vThreeQuarterEraseT;

    std::chrono::duration<double> lFrontPopT;
    std::chrono::duration<double> lBackPopT;
    std::chrono::duration<double> lQuarterEraseT;
    std::chrono::duration<double> lHalfEraseT;
    std::chrono::duration<double> lThreeQuarterEraseT;

    std::chrono::duration<double> differenceT;

    int vHalfPoint;
    int vQuarterPoint;
    int vThreeQuarterPoint;

    int lHalfPoint;
    int lQuarterPoint;
    int lThreeQuarterPoint;
    int lThreeQuarterTestPoint;

    int containerSize = 1000;

    int value;

    //Initialize the iterators to the start of their containers
    vit = testVector.begin();
    lit = testList.begin();

    //Initialize the Vector
    for(int i=0; i < containerSize; i++)
    {
        value = rand() % 10000;
        testVector.push_back(value);
    }

    //Copy the Vector into the List
    testList.insert(lit, testVector.begin(), testVector.end());

    //Test removal of data elements from Front and Back of the Vector and List
    //Start with the front of the Vector:
    vt1 = std::chrono::high_resolution_clock::now();
    vit = testVector.begin(); //set the Vector Iterator to the start of the Vector
    testVector.erase(vit);
    vt2 = std::chrono::high_resolution_clock::now();

    vFrontPopT = std::chrono::duration_cast<std::chrono::duration<double>>(vt2 - vt1);

    //Then the front of the List:
    lt1 = std::chrono::high_resolution_clock::now();
    testList.pop_front();
    lt2 = std::chrono::high_resolution_clock::now();

    lFrontPopT = std::chrono::duration_cast<std::chrono::duration<double>>(lt2 - lt1);

    //Now the back of the Vector:
    vt1 = std::chrono::high_resolution_clock::now();
    testVector.pop_back();
    vt2 = std::chrono::high_resolution_clock::now();

    vBackPopT = std::chrono::duration_cast<std::chrono::duration<double>>(vt2 - vt1);

    //And the back of the List:
    lt1 = std::chrono::high_resolution_clock::now();
    testList.pop_back();
    lt2 = std::chrono::high_resolution_clock::now();

    lBackPopT = std::chrono::duration_cast<std::chrono::duration<double>>(lt2 - lt1);

    //Moving on, test the removal of data at the 1/4, 1/2, and 3/4 positions:
    //Start by finding the 1/2 point of the current Vector and List:
    vHalfPoint = testVector.size() / 2;
    lHalfPoint = testList.size() / 2;

    //Then erase the element at that point from the Vector:
    vt1 = std::chrono::high_resolution_clock::now();
    vit = testVector.begin() + vHalfPoint; //set the Vector Iterator
    testVector.erase(vit);
    vt2 = std::chrono::high_resolution_clock::now();

    vHalfEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(vt2 - vt1);

    //And the element at that point from the List:
    lt1 = std::chrono::high_resolution_clock::now();
    lit = testList.begin(); //set the List Iterator to the List start
    for(int i = 0; i <= lHalfPoint; i++)
    {
        ++lit;              //Move the List Iterator to the Half Point
    }
    testList.erase(lit);
    lt2 = std::chrono::high_resolution_clock::now();

    lHalfEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(lt2 - lt1);

    //Now repeat for 1/4 point:
    vQuarterPoint = testVector.size() / 4;
    lQuarterPoint = testList.size() / 4;

    //Erase the element at that point from the Vector:
    vt1 = std::chrono::high_resolution_clock::now();
    vit = testVector.begin() + vQuarterPoint; //set the Vector Iterator
    testVector.erase(vit);
    vt2 = std::chrono::high_resolution_clock::now();

    vQuarterEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(vt2 - vt1);

    //And the element at that point from the List:
    lt1 = std::chrono::high_resolution_clock::now();
    lit = testList.begin(); //set the List Iterator to the List start
    for(int i = 0; i <= lQuarterPoint; i++)
    {
        ++lit;              //Move the List Iterator to the Half Point
    }
    testList.erase(lit);
    lt2 = std::chrono::high_resolution_clock::now();

    lQuarterEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(lt2 - lt1);

    //Finally, repeat for 3/4 point:
    vThreeQuarterPoint = 3 * testVector.size() / 4;
    lThreeQuarterPoint = 3 * testList.size() / 4;
    lThreeQuarterTestPoint = testList.size() - lThreeQuarterPoint;

    //Erase the element at that point from the Vector:
    vt1 = std::chrono::high_resolution_clock::now();
    vit = testVector.begin() + vThreeQuarterPoint; //set the Vector Iterator
    testVector.erase(vit);
    vt2 = std::chrono::high_resolution_clock::now();

    vThreeQuarterEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(vt2 - vt1);

    //And the element at that point from the List:
    lt1 = std::chrono::high_resolution_clock::now();
    lit = testList.end(); //set the List Iterator to the List end
    for(int i = 0; i <= lThreeQuarterTestPoint; i++)
    {
        --lit;              //Move the List Iterator to the Half Point
    }
    testList.erase(lit);
    lt2 = std::chrono::high_resolution_clock::now();

    lThreeQuarterEraseT = std::chrono::duration_cast<std::chrono::duration<double>>(lt2 - lt1);

    //Print the results:
    std::cout << "Using containers with " << containerSize << " elements.\n";
    std::cout << "All times include time needed to point the iterator to the correct element.\n";

    //Removal from Front:
    std::cout << "\nTime to remove an element from the front of the container:\n";
    //Vector:
    std::cout << "Vector: " << vFrontPopT.count() << " seconds\n";
    //List:
    std::cout << "List: " << lFrontPopT.count() << " seconds\n";

    if(vFrontPopT.count() < lFrontPopT.count())
    {
        std::cout << "Vector is faster, by ";
        differenceT = lFrontPopT - vFrontPopT;
        std::cout << differenceT.count() << " seconds.\n";
    }
    else
    {
        std::cout << "List is faster, by ";
        differenceT = vFrontPopT - lFrontPopT;
        std::cout << differenceT.count() << " seconds.\n";
    }

    //Removal from Back:
    std::cout << "\nTime to remove an element from the back of the container:\n";
    //Vector:
    std::cout << "Vector: " << vBackPopT.count() << " seconds\n";
    //List:
    std::cout << "List: " << lBackPopT.count() << " seconds\n";

    if(vBackPopT.count() < lBackPopT.count())
    {
        std::cout << "Vector is faster, by ";
        differenceT = lBackPopT - vBackPopT;
        std::cout << differenceT.count() << " seconds.\n";
    }
    else
    {
        std::cout << "List is faster, by ";
        differenceT = vBackPopT - lBackPopT;
        std::cout << differenceT.count() << " seconds.\n";
    }

    //Removal from Center:
    std::cout << "\nTime to remove an element from the center of the container:\n";
    //Vector:
    std::cout << "Vector: " << vHalfEraseT.count() << " seconds\n";
    //List:
    std::cout << "List: " << lHalfEraseT.count() << " seconds\n";

    if(vHalfEraseT.count() < lHalfEraseT.count())
    {
        std::cout << "Vector is faster, by ";
        differenceT = lHalfEraseT - vHalfEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }
    else
    {
        std::cout << "List is faster, by ";
        differenceT = vHalfEraseT - lHalfEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }

    //Removal from One Quarter into the container:
    std::cout << "\nTime to remove an element from the front quarter of the container:\n";
    //Vector:
    std::cout << "Vector: " << vQuarterEraseT.count() << " seconds\n";
    //List:
    std::cout << "List: " << lQuarterEraseT.count() << " seconds\n";

    if(vQuarterEraseT.count() < lQuarterEraseT.count())
    {
        std::cout << "Vector is faster, by ";
        differenceT = lQuarterEraseT - vQuarterEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }
    else
    {
        std::cout << "List is faster, by ";
        differenceT = vQuarterEraseT - lQuarterEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }

    //Removal from Three Quarters into the container:
    std::cout << "\nTime to remove an element from the back quarter of the container:\n";
    //Vector:
    std::cout << "Vector: " << vThreeQuarterEraseT.count() << " seconds\n";
    //List:
    std::cout << "List: " << lThreeQuarterEraseT.count() << " seconds\n";

    if(vThreeQuarterEraseT.count() < lThreeQuarterEraseT.count())
    {
        std::cout << "Vector is faster, by ";
        differenceT = lThreeQuarterEraseT - vThreeQuarterEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }
    else
    {
        std::cout << "List is faster, by ";
        differenceT = vThreeQuarterEraseT - lThreeQuarterEraseT;
        std::cout << differenceT.count() << " seconds.\n";
    }

    return 0;
}
