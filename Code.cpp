// Added : updated deletePrison() function such that associated inmates are deleted
// Added : input validation
// Added : limit ofr hash table and limit for linked list
// Almost Done: No changes needed --> Imported from final1.cpp
// Should add: -> modify function
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iomanip>

// Structure for prison details
struct Prison
{
    int id;
    std::string name;
    std::string location;
};

// Structure for inmate details
struct Inmate
{
    int id;
    std::string name;
    int prisonId;
};

// Function to calculate the hash value
int hashFunction(int key, int tableSize)
{
    std::hash<int> hasher;
    return hasher(key) % tableSize;
}

// Function to save prison details to file
void savePrisonDetails(const std::unordered_map<int, std::vector<Prison>> &prisonHashTable)
{
    std::ofstream prisonFile("prisons.txt");
    if (prisonFile)
    {
        for (const auto &entry : prisonHashTable)
        {
            for (const Prison &prison : entry.second)
            {
                prisonFile << prison.id << "," << prison.name << "," << prison.location << std::endl;
            }
        }
        prisonFile.close();
    }
    else
    {
        std::cerr << "Error opening prison file for writing." << std::endl;
    }
}

// Function to save inmate details to file
void saveInmateDetails(const std::unordered_map<int, std::vector<Inmate>> &inmateHashTable)
{
    std::ofstream inmateFile("inmates.txt");
    if (inmateFile)
    {
        for (const auto &entry : inmateHashTable)
        {
            for (const Inmate &inmate : entry.second)
            {
                inmateFile << inmate.id << "," << inmate.name << "," << inmate.prisonId << std::endl;
            }
        }
        inmateFile.close();
    }
    else
    {
        std::cerr << "Error opening inmate file for writing." << std::endl;
    }
}

// Function to save prison hash values and keys to file
void savePrisonHashDetails(const std::unordered_map<int, int> &prisonHashKey)
{
    std::ofstream prisonHashFile("prison_hash.txt");
    if (prisonHashFile)
    {
        for (const auto &entry : prisonHashKey)
        {
            prisonHashFile << entry.first << "," << entry.second << std::endl;
        }
        prisonHashFile.close();
    }
    else
    {
        std::cerr << "Error opening prison hash file for writing." << std::endl;
    }
}

// Function to save inmate hash values and keys to file
void saveInmateHashDetails(const std::unordered_map<int, int> &inmateHashKey)
{
    std::ofstream inmateHashFile("inmate_hash.txt");
    if (inmateHashFile)
    {
        for (const auto &entry : inmateHashKey)
        {
            inmateHashFile << entry.first << "," << entry.second << std::endl;
        }
        inmateHashFile.close();
    }
    else
    {
        std::cerr << "Error opening inmate hash file for writing." << std::endl;
    }
}

// Function to add a prison
void addPrison(std::unordered_map<int, std::vector<Prison>> &prisonHashTable,
               std::unordered_map<int, int> &prisonHashKey, int tableSize)
{
    Prison prison;
    std::cout << "Enter Prison ID: ";
    std::cin >> prison.id;

    // Check if the prison ID already exists
    if (prisonHashKey.count(prison.id) > 0)
    {
        std::cout << "Prison ID already exists. Please enter a unique ID." << std::endl;
        return;
    }

    std::cout << "Enter Prison Name: ";
    std::cin.ignore();
    std::getline(std::cin, prison.name);
    std::cout << "Enter Prison Location: ";
    std::getline(std::cin, prison.location);

    int hashValue = hashFunction(prison.id, tableSize);
    // Check if the linked list length has reached the maximum limit
    if (prisonHashTable[hashValue].size() >= 2)
    {
        std::cout << "Cannot add prison. Maximum limit reached for linked lIst." << std::endl;
        return;
    }

    prisonHashTable[hashValue].push_back(prison);
    prisonHashKey[prison.id] = hashValue;

    // Save the details to the files
    savePrisonDetails(prisonHashTable);
    savePrisonHashDetails(prisonHashKey);
}

// Function to display all prisons
void displayPrisons(const std::unordered_map<int, std::vector<Prison>> &prisonHashTable)
{
    // Print table header
    std::cout << std::left << std::setw(12) << "Prison ID"
              << std::setw(20) << "Prison Name"
              << std::setw(20) << "Prison Location" << std::endl;

    // Print table rows
    for (const auto &entry : prisonHashTable)
    {
        for (const Prison &prison : entry.second)
        {
            std::cout << std::left << std::setw(12) << prison.id
                      << std::setw(20) << prison.name
                      << std::setw(20) << prison.location << std::endl;
        }
    }
}

// Function to add an inmate
void addInmate(std::unordered_map<int, std::vector<Inmate>> &inmateHashTable,
               std::unordered_map<int, int> &inmateHashKey, int tableSize,
               const std::unordered_map<int, std::vector<Prison>> &prisonHashTable, std::unordered_map<int, int> &prisonHashKey)
{
    Inmate inmate;
    std::cout << "Enter Inmate ID: ";
    std::cin >> inmate.id;

    // Check if the inmate ID already exists
    if (inmateHashKey.count(inmate.id) > 0)
    {
        std::cout << "Inmate ID already exists. Please enter a unique ID." << std::endl;
        return;
    }

    std::cout << "Enter Inmate Name: ";
    std::cin.ignore();
    std::getline(std::cin, inmate.name);

    // Check if the entered prison ID exists
    int prisonId;
    std::cout << "Enter Prison ID: ";
    std::cin >> prisonId;
    if (prisonHashKey.count(prisonId) == 0)
    {
        std::cout << "Prison with ID " << prisonId << " does not exist." << std::endl;

        char choice;
        std::cout << "Do you want to display available prisons? (Y/N): ";
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            displayPrisons(prisonHashTable);
        }

        return;
    }
    inmate.prisonId = prisonId;

    int hashValue = hashFunction(inmate.id, tableSize);

    // Check if the linked list length has reached the maximum limit
    if (inmateHashTable[hashValue].size() >= 2)
    {
        std::cout << "Cannot add inmate. Maximum limit reached for the hash value." << std::endl;
        return;
    }

    inmateHashTable[hashValue].push_back(inmate);
    inmateHashKey[inmate.id] = hashValue;

    // Save the details to the files
    saveInmateDetails(inmateHashTable);
    saveInmateHashDetails(inmateHashKey);
}

// Function to search for a prison
void searchPrison(const std::unordered_map<int, std::vector<Prison>> &prisonHashTable,
                  const std::unordered_map<int, int> &prisonHashKey, int tableSize)
{
    int prisonId;
    std::cout << "Enter Prison ID to search: ";
    std::cin >> prisonId;

    auto it = prisonHashKey.find(prisonId);
    if (it != prisonHashKey.end())
    {
        int hashValue = it->second;
        const std::vector<Prison> &prisons = prisonHashTable.at(hashValue);
        for (const Prison &prison : prisons)
        {
            if (prison.id == prisonId)
            {
                std::cout << "Prison ID: " << prison.id << std::endl;
                std::cout << "Prison Name: " << prison.name << std::endl;
                std::cout << "Prison Location: " << prison.location << std::endl;
                return;
            }
        }
    }

    std::cout << "Prison not found." << std::endl;
}

// Function to search for an inmate
void searchInmate(const std::unordered_map<int, std::vector<Inmate>> &inmateHashTable,
                  const std::unordered_map<int, int> &inmateHashKey, int tableSize)
{
    int inmateId;
    std::cout << "Enter Inmate ID to search: ";
    std::cin >> inmateId;

    auto it = inmateHashKey.find(inmateId);
    if (it != inmateHashKey.end())
    {
        int hashValue = it->second;
        const std::vector<Inmate> &inmates = inmateHashTable.at(hashValue);
        for (const Inmate &inmate : inmates)
        {
            if (inmate.id == inmateId)
            {
                std::cout << "Inmate ID: " << inmate.id << std::endl;
                std::cout << "Inmate Name: " << inmate.name << std::endl;
                std::cout << "Prison ID: " << inmate.prisonId << std::endl;
                return;
            }
        }
    }

    std::cout << "Inmate not found." << std::endl;
}

// Function to delete associated inmates with prison (called automatically)
void deleteAssociatedInmates(std::unordered_map<int, std::vector<Inmate>> &inmateHashTable,
                             std::unordered_map<int, int> &inmateHashKey,
                             int prisonId)
{
    for (auto &inmatePair : inmateHashTable)
    {
        std::vector<Inmate> &inmates = inmatePair.second;
        auto iter = inmates.begin();
        while (iter != inmates.end())
        {
            if (iter->prisonId == prisonId)
            {
                int inmateId = iter->id;
                iter = inmates.erase(iter);
                inmateHashKey.erase(inmateId);
            }
            else
            {
                ++iter;
            }
        }
    }
}

// Function to delete a prison
void deletePrison(std::unordered_map<int, std::vector<Prison>> &prisonHashTable,
                  std::unordered_map<int, int> &prisonHashKey,
                  std::unordered_map<int, std::vector<Inmate>> &inmateHashTable,
                  std::unordered_map<int, int> &inmateHashKey)
{
    int prisonId;
    std::cout << "Enter Prison ID to delete: ";
    std::cin >> prisonId;

    auto it = prisonHashKey.find(prisonId);
    if (it != prisonHashKey.end())
    {
        int hashValue = it->second;
        std::vector<Prison> &prisons = prisonHashTable[hashValue];
        for (auto iter = prisons.begin(); iter != prisons.end(); ++iter)
        {
            if (iter->id == prisonId)
            {
                prisons.erase(iter);
                prisonHashKey.erase(it);
                std::cout << "Prison deleted successfully." << std::endl;

                // Delete associated inmates
                deleteAssociatedInmates(inmateHashTable, inmateHashKey, prisonId);

                // Save the updated details to the files
                savePrisonDetails(prisonHashTable);
                savePrisonHashDetails(prisonHashKey);
                saveInmateDetails(inmateHashTable);
                saveInmateHashDetails(inmateHashKey);
                return;
            }
        }
    }

    std::cout << "Prison not found." << std::endl;
}

// Function to delete an inmate
void deleteInmate(std::unordered_map<int, std::vector<Inmate>> &inmateHashTable,
                  std::unordered_map<int, int> &inmateHashKey)
{
    int inmateId;
    std::cout << "Enter Inmate ID to delete: ";
    std::cin >> inmateId;

    auto it = inmateHashKey.find(inmateId);
    if (it != inmateHashKey.end())
    {
        int hashValue = it->second;
        std::vector<Inmate> &inmates = inmateHashTable[hashValue];
        for (auto iter = inmates.begin(); iter != inmates.end(); ++iter)
        {
            if (iter->id == inmateId)
            {
                inmates.erase(iter);
                inmateHashKey.erase(it);
                std::cout << "Inmate deleted successfully." << std::endl;

                // Save the updated details to the files
                saveInmateDetails(inmateHashTable);
                saveInmateHashDetails(inmateHashKey);
                return;
            }
        }
    }

    std::cout << "Inmate not found." << std::endl;
}

// Function to display all inmates
void displayInmates(const std::unordered_map<int, std::vector<Inmate>> &inmateHashTable)
{
    // Print table header
    std::cout << std::left << std::setw(12) << "Inmate ID"
              << std::setw(20) << "Inmate Name"
              << std::setw(20) << "Prison ID" << std::endl;

    for (const auto &entry : inmateHashTable)
    {
        for (const Inmate &inmate : entry.second)
        {
            std::cout << std::left << std::setw(12) << inmate.id
                      << std::setw(20) << inmate.name
                      << std::setw(20) << inmate.prisonId << std::endl;
        }
    }
}

int countEntriesInFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line))
    {
        count++;
    }

    file.close();
    return count;
}

void printCentered(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    std::cout << std::setw(padding + text.length()) << std::setfill(' ') << text << std::endl;
}

void printChoice(int number, const std::string& choiceText) {
    std::cout << std::left << std::setw(2) << number << ". " << choiceText << std::endl;
}

int main()
{
    int tableSize, Pcnt, Icnt;
    std::cout << "Enter the hash table size: ";
    std::cin >> tableSize;

    std::unordered_map<int, std::vector<Prison>> prisonHashTable;
    std::unordered_map<int, std::vector<Inmate>> inmateHashTable;
    std::unordered_map<int, int> prisonHashKey;
    std::unordered_map<int, int> inmateHashKey;

    int choice;
    do
    {
        std::cout << "******************************************" << std::endl;
        printCentered("    WELCOME TO PRISON MANAGEMENT", 42);
        std::cout << "******************************************" << std::endl;
        printCentered("     MAIN MENU", 42);
        std::cout << "******************************************" << std::endl;
        printChoice(1, "Add Prison");
        printChoice(2, "Add Inmate");
        printChoice(3, "Search Prison");
        printChoice(4, "Search Inmate");
        printChoice(5, "Delete Prison");
        printChoice(6, "Delete Inmate");
        printChoice(7, "Display Prisons");
        printChoice(8, "Display Inmates");
        printChoice(0, "Exit");
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            addPrison(prisonHashTable, prisonHashKey, tableSize);
            Pcnt = countEntriesInFile("prison_hash.txt");
            if (Pcnt == tableSize)
            {
                std::cout << "Hash file size for Prison exceeded" << std::endl;
                return 1;
            }
            break;
        case 2:
            Icnt = countEntriesInFile("inmate_hash.txt");
            if (Icnt == tableSize)
            {
                std::cout << "Hash file size for Inmate exceeded" << std::endl;
                return 1;
            }
            addInmate(inmateHashTable, inmateHashKey, tableSize, prisonHashTable, prisonHashKey);
            break;
        case 3:
            searchPrison(prisonHashTable, prisonHashKey, tableSize);
            break;
        case 4:
            searchInmate(inmateHashTable, inmateHashKey, tableSize);
            break;
        case 5:
            deletePrison(prisonHashTable, prisonHashKey, inmateHashTable, inmateHashKey);
            break;
        case 6:
            deleteInmate(inmateHashTable, inmateHashKey);
            break;
        case 7:
            displayPrisons(prisonHashTable);
            break;
        case 8:
            displayInmates(inmateHashTable);
            break;
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}
