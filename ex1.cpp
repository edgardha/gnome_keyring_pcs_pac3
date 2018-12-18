#include <gnome-keyring-1/gnome-keyring.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void createPassword() {
    GnomeKeyringResult res;
    gchar display_name[128];
    gchar password[128];
    gchar attr_name[128],attr_value[128];
    const gchar *c_display_name,*c_password,*c_attr_name,*c_attr_value;
    printf("Enter description text: ");
    scanf("%s",display_name);
    c_display_name = display_name;
    printf("Enter password: ");
    scanf("%s", password);
    c_password = password;
    printf("Enter attribute name: ");
    scanf("%s", attr_name);
    c_attr_name = attr_name;
    printf("Enter attribute value: ");
    scanf("%s", attr_value);
    c_attr_value = attr_value;
    
    const GnomeKeyringPasswordSchema schema = {GNOME_KEYRING_ITEM_GENERIC_SECRET,
    {{c_attr_name, GNOME_KEYRING_ATTRIBUTE_TYPE_STRING}, {NULL, GnomeKeyringAttributeType::GNOME_KEYRING_ATTRIBUTE_TYPE_STRING}}};

    res = gnome_keyring_store_password_sync(&schema, NULL, c_display_name, c_password, c_attr_name, c_attr_value,NULL,(char *)NULL);
}

void getPassword() {
    gchar *pass;
    GnomeKeyringResult res;
    gchar attr_name[128];
    gchar attr_value[128];
    const gchar *c_attr_name,*c_attr_value;

    printf("Enter attribute name: ");
    scanf("%s", attr_name);
    c_attr_name = attr_name;
    printf("Enter attribute value: ");
    scanf("%s", attr_value);
    c_attr_value = attr_value;

    const GnomeKeyringPasswordSchema schema = {GNOME_KEYRING_ITEM_GENERIC_SECRET,
    {{c_attr_name, GNOME_KEYRING_ATTRIBUTE_TYPE_STRING}, {NULL, GnomeKeyringAttributeType::GNOME_KEYRING_ATTRIBUTE_TYPE_STRING}}};

    res = gnome_keyring_find_password_sync(&schema, &pass, c_attr_name, c_attr_value, NULL, (char *)NULL);

    if (pass == NULL)
    {
        printf("There are no password with this attributes.\n");
        return;
    }
    printf("Password is %s\n", pass);
    gnome_keyring_free_password(pass);

    return;
}

void printMenu() {
    printf("Choose an option:\n");
    printf("1. Create entry on gnome-keyring\n");
    printf("2. Get an entry from gnome-keyring\n");
    printf("3. Exit\n");
    printf("Option (1/2/3): ");
}

void selectOption() {
    int option = 0;

    printMenu();
    while (true) {
        while (option != 1 && option != 2 && option != 3) {
            scanf("%d", &option);
        }
        if (option == 1) {
            createPassword();
        } else if (option == 2) {
            getPassword();
        } else {
            return;
        }
        printMenu();
        option = 0;
    }
}

int main() {
    selectOption();
    return 0;
}