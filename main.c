#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 100
#define SHORT_LEN 7
typedef struct URLNode 
{
char longURL[1000];
char shortCode[SHORT_LEN];
struct URLNode* next;
} URLNode;
URLNode* hashTable[TABLE_SIZE];
int hashFunction(char* shortCode) 
{
int sum = 0;
for (int i = 0; shortCode[i] != '\0'; i++)
sum += shortCode[i];
return sum % TABLE_SIZE;
}
void generateShortCode(char* longURL, char* shortCode) {
int sum = 0;
for (int i = 0; longURL[i] != '\0'; i++)
sum += longURL[i];
sprintf(shortCode, "H%05d", sum % 100000); // Example: H12345
}
void insertURL(char* longURL) {
char shortCode[SHORT_LEN];
generateShortCode(longURL, shortCode);
int index = hashFunction(shortCode);
URLNode* newNode = (URLNode*)malloc(sizeof(URLNode));
strcpy(newNode->longURL, longURL);
strcpy(newNode->shortCode, shortCode);
newNode->next = hashTable[index];
hashTable[index] = newNode;
printf("\nShortened URL: %s --> %s\n", shortCode, longURL);
}
void getLongURL(char* shortCode) {
int index = hashFunction(shortCode);
URLNode* temp = hashTable[index];
while (temp != NULL) {
if (strcmp(temp->shortCode, shortCode) == 0) {
printf("Original URL: %s\n", temp->longURL);
return;
}
temp = temp->next;
}
printf("No URL found for short code %s\n", shortCode);
}
void displayURLs() {
printf("\nStored URL Mappings:\n");
for (int i = 0; i < TABLE_SIZE; i++) {
URLNode* temp = hashTable[i];
while (temp != NULL) {
printf("%s --> %s\n", temp->shortCode, temp->longURL);
temp = temp->next;
}
}
}
int main() {
int choice;
char longURL[1000], shortCode[SHORT_LEN];
while (1) {
printf("\n--- URL Shortening Service ---\n");
printf("1. Shorten new URL\n");
printf("2. Retrieve original URL\n");
printf("3. Display all URLs\n");
printf("4. Exit\n");
printf("Enter choice: ");
scanf("%d", &choice);
getchar();
switch (choice) {
case 1:
printf("Enter long URL: ");
fgets(longURL, sizeof(longURL), stdin);
longURL[strcspn(longURL, "\n")] = '\0';
insertURL(longURL);
break;
case 2:
printf("Enter short code: ");
scanf("%s", shortCode);
getLongURL(shortCode);
break;
case 3:
displayURLs();
break;
case 4:
printf("Exiting...\n");
exit(0);
default:
printf("Invalid choice!\n");
}
}
}