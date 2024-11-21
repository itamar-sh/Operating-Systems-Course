#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} Person;


void serialize(Person *p, const char *filename) {
    FILE *file = fopen(filename, "wb");  // Open for binary write
    if (file != NULL) {
        fwrite(p, sizeof(Person), 1, file);  // Write the struct as raw bytes
        fclose(file);
    } else {
        printf("Error opening file for serialization.\n");
    }
}


void deserialize(Person *p, const char *filename) {
    FILE *file = fopen(filename, "rb");  // Open for binary read
    if (file != NULL) {
        fread(p, sizeof(Person), 1, file);  // Read the bytes into the struct
        fclose(file);
    } else {
        printf("Error opening file for deserialization.\n");
    }
}


int main() {
    Person person = {1, "John Doe"};

    // Serialize to file
    serialize(&person, "person.dat");

    // Create a new person struct to load data into
    Person loadedPerson;

    // Deserialize from file
    deserialize(&loadedPerson, "person.dat");

    // Print out deserialized data
    printf("ID: %d, Name: %s\n", loadedPerson.id, loadedPerson.name);

    return 0;
}
