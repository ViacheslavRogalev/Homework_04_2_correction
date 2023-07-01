#include <iostream>
#include <fstream>
#include <sstream> 
#include <windows.h>


class Address {
protected:
    std::string city;
    std::string street;
    int buildingNumber;
    int flatNumber;

public:
    Address()
    {
        std::string city = "Anonymous";
        std::string street = "Anonymous";
        int buildingNumber = 0;
        int flatNumber = 0;
    }

    Address(std::string city, std::string street, int buildingNumber, int flatNumber)
    {
        this->city = city;
        this->street = street;
        this->buildingNumber = buildingNumber;
        this->flatNumber = flatNumber;
    }

    std::string getCity() 
    {
        return city;
    }

    std::string getStreet() 
    {
        return street;
    }

    int getBuildingNumber() 
    {
        return buildingNumber;
    }

    int getFlatNumber() 
    {
        return flatNumber;
    }

    std::string getOutAddress() 
    {
        return this->city + ", " + this->street + ", " + std::to_string(this->buildingNumber) + ", " + std::to_string(this->flatNumber);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::string fileName = "in.txt";
    std::ifstream myFile(fileName);

    if (myFile) 
    {
        std::cout << "Файл открыт" << std::endl;

        int numberOfAddress;
        myFile >> numberOfAddress;

        std::string* arr_city = new std::string[numberOfAddress];
        std::string* arr_street = new std::string[numberOfAddress];
        int* arr_buildingNumber = new int[numberOfAddress];
        int* arr_flatNumber = new int[numberOfAddress];
        Address* arr_address = new Address[numberOfAddress];

        for (int i = 0; i < numberOfAddress; i++) 
        {
            myFile >> arr_city[i];
            myFile >> arr_street[i];
            myFile >> arr_buildingNumber[i];
            myFile >> arr_flatNumber[i];
            arr_address[i] = Address(arr_city[i], arr_street[i], arr_buildingNumber[i], arr_flatNumber[i]);
        }

        Address temp;
        for (int i = 1, j; i < 5; ++i)
        {
            temp = arr_address[i];
            for (j = i - 1; j >= 0 && arr_address[j].getCity() > temp.getCity(); --j) 
            {
                arr_address[j + 1] = arr_address[j];
            }
            arr_address[j + 1] = temp;
        }

        std::string fileOutName = "out.txt";
        std::ofstream myOutFile(fileOutName);

        if (myOutFile) 
        {
            std::cout << "Файл открыт успешно" << std::endl;
            myOutFile << numberOfAddress << std::endl;

            for (int i = 0; i < numberOfAddress; i++) 
            {
                myOutFile << arr_address[i].getOutAddress() << std::endl;
            }
            myOutFile.close();
        }
        myFile.close();

        delete[]arr_city;
        delete[]arr_street;
        delete[]arr_buildingNumber;
        delete[]arr_flatNumber;
        delete[]arr_address;
    }

    else 
    {
        std::cout << "Не получилось открыть файл" << std::endl;
        return 0;
    }
    return 0;
}