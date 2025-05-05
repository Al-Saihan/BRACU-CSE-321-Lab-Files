#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_RESOURCES 3
#define MAX_NAME_LEN 20
#define MAX_ACL_ENTRIES 20
#define MAX_CAPABILITIES 20

typedef enum
{
    // TODO
    NO_PERM = 0,
    READ = 1,
    WRITE = 2,
    EXECUTE = 4,
    ALL_PERM = READ | WRITE | EXECUTE
} Permission;

// User and Resource Definitions
typedef struct
{
    // TODO
    char name[MAX_NAME_LEN];
} User;

typedef struct
{
    // TODO
    char name[MAX_NAME_LEN];
} Resource;

// ACL Entry
typedef struct
{
    // TODO
    char username[MAX_NAME_LEN];
    int permissions;
} ACLEntry;

typedef struct
{
    // TODO
    char resource_name[MAX_NAME_LEN];
    ACLEntry entries[MAX_ACL_ENTRIES];
    int count;
} ACLControlledResource;

// Capability Entry
typedef struct
{
    // TODO
    char name[MAX_NAME_LEN];
    int permissions;
} Capability;

typedef struct
{
    // TODO
    User person;
    Capability capabilities[MAX_CAPABILITIES];
    int count;
} CapabilityUser;

// Utility Functions
void printPermissions(int perm)
{
    // TODO
    printf("(");
    if (perm == NO_PERM)
    {
        printf("\"NONE\"");
    }
    int comma = 0;
    if ((perm & READ) == READ)
    {
        printf("\"Read\"");
        comma = 1;
    }
    if ((perm & WRITE) == WRITE)
    {
        if (comma)
        {
            printf(", ");
        };
        printf("\"Write\"");
        comma = 1;
    }
    if ((perm & EXECUTE) == EXECUTE)
    {
        if (comma)
        {
            printf(", ");
        }
        printf("\"Execute\"");
    }
    printf(")\n");
}

int hasPermission(int userPerm, int requiredPerm)
{
    // TODO
    if (userPerm & requiredPerm == requiredPerm)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ACL System
void checkACLAccess(ACLControlledResource *res, const char *userName, int perm)
{
    // TODO
    printf("ACL Check: User {%s} requests {%s} on {%s}: Access {%s}", *userName);
}

// Capability System
void checkCapabilityAccess(CapabilityUser *user, const char *resourceName, int perm)
{
    // TODO
}

int main()
{
    // Sample users and resources
    User users[MAX_USERS] = {{"Alice"}, {"Bob"}, {"Charlie"}};
    Resource resources[MAX_RESOURCES] = {{"File1"}, {"File2"}, {"File3"}};

    // ACL Setup
    // TODO
    ACLControlledResource aclResources[MAX_RESOURCES] =
        {{"File1", {{"Alice", READ | WRITE}, {"Bob", READ}}, 2},

         {"File2", {{"Bob", ALL_PERM}, {"Charlie", READ | EXECUTE}}, 2},

         {"File3", {{"Alice", WRITE}, {"Charlie", READ}}, 2}};

    // Capability Setup
    // TODO
    CapabilityUser capabilityUsers[MAX_USERS] =
        {{{"Alice"}, {{"File1", READ | WRITE}, {"File3", WRITE}}, 2},

         {{"Bob"}, {{"File1", READ}, {"File2", ALL_PERM}}, 2},

         {{"Charlie"}, {{"File2", READ | EXECUTE}, {"File3", READ}}, 2}};

    // Test ACL
    // TODO

    // Test Capability
    // TODO

    return 0;
}