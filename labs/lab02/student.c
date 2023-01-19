#include <stdio.h>
#include <assert.h>

struct student{
    char *name;
    int ID;
    int age;
};

typedef struct student student;

void print_age(student st)
{
    printf("Age: %d\n", st.age);
}

void print_name(student st)
{
    printf("Name: %s\n", st.name);
}

void print_id(student st)
{
    printf("ID: %d\n", st.ID);
}

int main(void)
{
    struct student Junior;
    Junior.name = "José Junior";
    Junior.ID = 4063142;
    Junior.age = 23;


    print_age(Junior);
    assert(Junior.name == "Jose Junior");
    print_name(Junior);
    print_id(Junior);
}