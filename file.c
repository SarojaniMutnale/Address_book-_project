#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{

    if (addressBook->contactCount == 0)
    {
        printf("No contacts to save");
        return;
    }

    FILE *fptr = fopen("contact.txt", "w");
    if (fptr == NULL)
    {
        printf("Sorry unable to open the file for saving contacts.\n");
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
    printf("The contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "r");
    if (fptr == NULL)
    {
        printf("Sorry: Unable to open contacts.\n");
        return;
    }
    fscanf(fptr, "%d\n", &addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
    // printf("Contacts loaded successfully from contacts.txt.\n");
}
