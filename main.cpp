#include <iostream>

int main()
{
    int participantsNumber, participantPlace;
    std::cin >> participantsNumber >> participantPlace;
    int array[100];
    for (int i = 0; i < participantsNumber; ++i)
    {
        std::cin >> array[i];
    }
    int startIndex = 0;
    for (int count = 0; count < participantsNumber - 1; ++count)
    {
        if (array[startIndex] >= array[startIndex + 1])
            ++startIndex;
    }
}