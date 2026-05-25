#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{
    printf("##-------------------------------------------------------##\n");
    printf("\t\t📃📃LIST OF CONTACTS📃📃\t\n");
    printf("##-------------------------------------------------------##\n");
    printf("|name\t\t|phonenumber\t\t|Email\n");
    printf("##--------------------------------------------------------##\n");

    for (int i = 0; i < addressBook->contactCount; i++) // this loop will list the all contacts
    {
        printf("%s \t%s \t%s \t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("##---------------------------------------------------------##\n");
}
void initialize(AddressBook *addressBook)

{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    char ch;

    char name[50], phone_no[50], emailid[50]; // declration of variables
    printf("Enter the name: ");               // read input from user
    getchar();
    scanf(" %[^\n]", name);
    while (1)
    {

        int valid = 1;

        for (int i = 0; name[i] != '\0'; i++)
        {
            if (name[i] == '\n')
            {
                continue;
            }

            if (!((name[i] >= 'A' && name[i] <= 'Z') ||
                  (name[i] >= 'a' && name[i] <= 'z') ||
                  name[i] == ' '))
            {

                valid = 0;
                break;
            }
        }
        if (valid)
            break;
        printf("only alphabets and spaces area llowed. \n");
        printf("Re - Enter the name: "); // read input from user
        getchar();
        scanf(" %[^\n]", name);
    }

    while (1)
    {

        printf("Enter the phone no: "); // read phone no.and validate
        getchar();
        scanf("%s", phone_no);
        if (strlen(phone_no) != 10 || strspn(phone_no, "0123456789") != strlen(phone_no))
        {
            printf("Invalid phone number.\n Re -");
            continue;
        }
        break;
    }

    while (1)
    {

        printf("Enter Email ID: "); // read email
        getchar();
        scanf("%s", emailid);
        // check first character is lowercase letter
        if (!(emailid[0] >= 'a' && emailid[0] <= 'z'))
        {
            printf("Invalid email ID. Must start with a lowercase letter.\nRe-enter the email ID:\n");
            continue;
        }
        // check for @ .com and nospace
        if (strchr(emailid, '@') == NULL || strstr(emailid, ".com") == NULL || strchr(emailid, ' ') != NULL)
        {
            printf("Invalid email ID.spaces are not allowed.\n Re -");
            continue;
        }
        break;
    }

    // store the contact details
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone_no);
    strcpy(addressBook->contacts[addressBook->contactCount].email, emailid);
    // increament contact count
    addressBook->contactCount++;
    printf("Contact added successfully!!!!!!!.\n");
}

void searchContact(AddressBook *addressBook)

{

    /*Define the logic for search*/
    int searchOption;
    char str[50];
    int flag = 0;
    printf("##---------------------------------------------------##\n");
    printf("\t\t\t*****SEARCH THE CONTACT*****\t\n");
    printf("##---------------------------------------------------##\n");
    printf("Search By: \n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar();
    switch (searchOption)
    {
    case 1:
        printf("Enter the name you want to search: ");
        scanf(" %[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, str) != NULL)
            {
                printf("##--------------------------------------------------------------##\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("##--------------------------------------------------------------##\n");
                flag = 1;
            }
        }
        break;
    case 2:
        printf("Enter the 📞📞phone number you want to search:");
        scanf("%10[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("--------------------------------------------------------------\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("--------------------------------------------------------------\n");
                flag = 1;
            }
        }
        break;
    case 3:
        printf("Enter the email ✉️✉️ you want to search: ");
        scanf("%[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("------------------------------------------------------------\n");
                printf("%s\t %s\t %s\tn", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("-------------------------------------------------------------\n");
                flag = 1;
            }
        }
        break;
    default:
        printf("Invalid Option❌❌.\n");
        return;
    }
    if (flag == 0)
    {
        printf("Contact not found.\n");
    }
}
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to edit.\n");
        return;
    }
    printf("--------------------------------------------------------\n");
    printf("\t\t\tEDIT THE CONATACT\t\n");
    printf("----------------------------------------------------------\n");

    int searchOption, pos, i;
    char str[50];
    int foundindexes[MAX_CONTACTS];
    int matchCount = 0;
    printf("Search By:\n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar(); // clear newline

    switch (searchOption)
    {
    case 1:
        printf("Enter the name you want to search: ");
        scanf(" %[^\n]", str);
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, str) != NULL)
            {
                printf("%d.%s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundindexes[matchCount++] = i;
            }
        }
        break;
    case 2:
        printf("Enter the phone number you want to search: ");
        scanf(" %[^\n]", str);
        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("%d.%s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundindexes[matchCount++] = i;
            }
        }
        break;
    case 3:
        printf("Enter the email you wnat to search: ");
        scanf(" %[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("%d. %s\t %s\t %s\t\n", matchCount + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                foundindexes[matchCount++] = i;
            }
        }
        break;
    default:
        printf("Invalid option.❌❌\n");
        return;
    }
    if (matchCount == 0)
    {
        printf("Contact not found.\n");
        return;
    }
    int found;
    if (matchCount == 1)
    {
        found = foundindexes[0];
    }
    else
    {
        printf("Multiple contacts found...!!\n");
        printf("Enter the position you want to edit: ");
        scanf("%d", &pos);

        if (pos < 1 || pos > matchCount)
        {
            printf("Invalid position selected.\n");
            return;
        }
        found = foundindexes[pos - 1];
    }
    int editoption;

    printf("What do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &editoption);
    getchar(); // Clear newline after scanf

    switch (editoption)
    {
    case 1:
    {
        char newName[50];
        printf("Enter the name: "); // read input from user

        scanf(" %[^\n]", newName);

        while (1)
        {
            int valid = 1;

            // sara123
            for (int i = 0; newName[i] != '\0'; i++)
            {
                if (newName[i] == '\n')
                {
                    continue;
                }

                // f || f || f
                if (!((newName[i] >= 'A' && newName[i] <= 'Z') ||
                      (newName[i] >= 'a' && newName[i] <= 'z') ||
                      newName[i] == ' '))
                {

                    valid = 0;
                    break;
                }
            }
            if (valid)
                break;
            printf("only alphabets are allowed. \n");
            printf("Re - Enter the name: "); // read input from user
            getchar();
            scanf(" %[^\n]", newName);
        }

        strcpy(addressBook->contacts[found].name, newName);
        printf("Name updated successfully👍👍.\n");
        break;
    }
    case 2:
    {
        char newPhone[20];
        while (1)
        {

            printf("Enter the phone no: "); // read phone no.and validates

            scanf("%s", newPhone);
            if (strlen(newPhone) != 10 || strspn(newPhone, "0123456789") != strlen(newPhone))
            {
                printf("Invalid phone number.\n Re -");
                continue;
            }
            break;
        }

        // Validate phone
        if (strlen(newPhone) != 10 || strspn(newPhone, "0123456789") != strlen(newPhone))
        {
            printf("Invalid phone number.\n");
            return;
        }

        strcpy(addressBook->contacts[found].phone, newPhone);
        printf("Phone updated successfully.👍👍\n");
        break;
    }
    case 3:
    {
        char newEmail[50];
        while (1)
        {

            printf("Enter Email ID: "); // read email

            scanf("%s", newEmail);
            if (strchr(newEmail, '@') == NULL || strstr(newEmail, ".com") == NULL)
            {
                printf("Invalid email ID.\n Re -");
                continue;
            }
            break;
        }

        strcpy(addressBook->contacts[found].email, newEmail);
        printf("Email updated successfully.👍👍\n");
        break;
    }
    default:

        printf("Invalid Choice.\n");
        return;
    }
}

void deleteContact(AddressBook *addressBook)
{
    /*   Define the logic for deletecontact  */
    printf("-------------------------------------------------\n");
    printf("\t\tDELETE THE CONTACT\t\n");
    printf("--------------------------------------------------\n");
    int searchOption;
    char str[50];
    int flag = 0;
    char ch;
    int index;
    printf("Search to delete contact by: \n"); // Give menu for searching the contact
    printf("1.Name\n");
    printf("2.phone\n");
    printf("3.Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchOption);
    getchar();
    switch (searchOption) // read the value to search
    {
    case 1:
        printf("Enter the name : ");

        scanf(" %[^\n]", str);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].name) == 0)
            {
                printf("Name is present in the List\n");
                printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull👍\n");
                    break;
                }
                else if (ch == 'n')
                {
                    printf("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!\n");
                    break;
                }
            }
        }
        break;

    case 2:
        printf("Enter the Phonenumber : ");
        scanf(" %10[^\n]", str);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].phone) == 0)
            {
                printf("phone number is prsent in the List\n");
                printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull\n");
                    break;
                }
                else if (ch == 'n')
                {
                    ("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!\n");
                    break;
                }
            }
        }
        break;

    case 3:
        printf("Enter the Email id : ");
        scanf(" %[^\n]", str);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            index = i;
            if (strcmp(str, addressBook->contacts[i].email) == 0)
            {
                printf("Email id is prsent in the List\n");
                printf("%s \t %s \t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                flag = 1;
                printf("Do you want this delete contact ?(y/n): ");
                scanf(" %c", &ch);
                if (ch == 'y')
                {
                    for (int i = index; i < addressBook->contactCount; i++) // Shift contacts to delete the selected one
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Delete Successfull✅\n");
                    break;
                }
                else if (ch == 'n')
                {
                    printf("Contact not deleted\n");
                    break;
                }
                else
                {
                    printf("Invalid input!!\n");
                    break;
                }
            }
        }
        break;

    default:
        printf("Invalid option.❌❌n");
        return;
    }
    if (flag == 0) // If contact is not found
    {
        printf("Contact not found.\n");
        return;
    }
}
