#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NRCHILDREN 10

typedef struct Person 
{
    char name[50];
    struct Person *mother;
    struct Person *father;
    struct Person *children[NRCHILDREN];
    int numChildren;
    int gender; //0 for female, 1 for male
} Person;

//function to insert a person into the tree
void insertPerson(Person *person, const char *name, int gender) 
{
    strcpy(person->name, name);
    person->mother = NULL;
    person->father = NULL;
    person->numChildren = 0;
    person->gender = gender;
}

//function to add a child to somebody
void addChild(Person *parent, Person *child) 
{
    if (parent->numChildren < NRCHILDREN) 
	{
        parent->children[parent->numChildren++] = child;
        if (child->mother == NULL && parent->gender == 0) 
			child->mother = parent; //female
		else if (child->father == NULL && parent->gender == 1) 
			child->father = parent; //male 
    } 
	else 
		printf("Cannot add more children to %s.\n", parent->name);
}

//recursive function for ascendants
void recursiveAscendants(Person *person, int generation) 
{
    int i;
    for (i = 0; i < generation; i++) 
		printf("  ");
    printf("%s\n", person->name);
    if (person->mother != NULL) 
		recursiveAscendants(person->mother, generation + 1);
    if (person->father != NULL) 
		recursiveAscendants(person->father, generation + 1);
}

//function to show ascendants of a person
void showAscendants(Person *person) 
{
    printf("Ascendants of %s:\n", person->name);
    recursiveAscendants(person, 0);
}

//recursive function for descendants
void recursiveDescendants(Person *person, int generation) 
{
    int i;
    for (i = 0; i < generation; i++) 
		printf("  ");
    printf("%s\n", person->name);
    for (i = 0; i < person->numChildren; i++) 
		recursiveDescendants(person->children[i], generation + 1);
}

//function to show descendants of a person
void showDescendants(Person *person) 
{
    printf("Descendants of %s:\n", person->name);
    recursiveDescendants(person, 0);
}

//function to show siblings of somebody
void showSiblings(Person *person) 
{
    if (person->mother == NULL && person->father == NULL) 
    {   //if somebody doesn't have both parents, they won't have siblings
        printf("%s has no siblings.\n", person->name);
        return;
    }
    printf("Siblings of %s:\n", person->name);
	int i;
    if (person->mother != NULL) 
    {
        Person *parent = person->mother;
        for (i = 0; i < parent->numChildren; i++) 
        {
            if (parent->children[i] != person) //exclude the initial person from the list of siblings
                printf("%s\n", parent->children[i]->name);
        }
    }
    else if (person->father != NULL) 
    {
        Person *parent = person->father;
        for (i = 0; i < parent->numChildren; i++) 
        {
            if (parent->children[i] != person) //exclude the initial person from the list of siblings
                printf("%s\n", parent->children[i]->name);
        }
    }
}

//function to show cousins of somebody
void showCousins(Person *person) 
{
    if (person->mother == NULL && person->father == NULL) 
    {   //if somebody doesn't have both parents, they won't have cousins
        printf("%s has no cousins.\n", person->name);
        return;
    }
    printf("Cousins of %s:\n", person->name);
    int i, j;
    
    
    if (person->mother != NULL && person->father != NULL)//first for both having a mother and a father
    {
        Person *maternalGrandmother = person->mother->mother;
        Person *maternalGrandfather = person->mother->father;
        
        
        if (maternalGrandfather != NULL && maternalGrandmother != NULL) 
        {
            for (i = 0; i < maternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandfather->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (maternalGrandmother != NULL) 
        {
            for (i = 0; i < maternalGrandmother->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandmother->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (maternalGrandfather != NULL) 
        {
            for (i = 0; i < maternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandfather->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
    }
    
    
	else if (person->mother != NULL) //for only having a mother
    {
        Person *maternalGrandmother = person->mother->mother;
        Person *maternalGrandfather = person->mother->father;
        
        
        if (maternalGrandfather != NULL && maternalGrandmother != NULL) 
        {
            for (i = 0; i < maternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandfather->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (maternalGrandmother != NULL) 
        {
            for (i = 0; i < maternalGrandmother->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandmother->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (maternalGrandfather != NULL) 
        {
            for (i = 0; i < maternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = maternalGrandfather->children[i];
                if (auntUncle != person->mother)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
    }
    
    
    else if (person->father != NULL)//for only having a father
    {
        Person *paternalGrandmother = person->father->mother;
        Person *paternalGrandfather = person->father->father;
        
        
        if (paternalGrandfather != NULL && paternalGrandmother != NULL) 
        {
            for (i = 0; i < paternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = paternalGrandfather->children[i];
                if (auntUncle != person->father)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (paternalGrandmother != NULL) 
        {
            for (i = 0; i < paternalGrandmother->numChildren; i++) 
            {
                Person *auntUncle = paternalGrandmother->children[i];
                if (auntUncle != person->father)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
        
        
        else if (paternalGrandfather != NULL) 
        {
            for (i = 0; i < paternalGrandfather->numChildren; i++) 
            {
                Person *auntUncle = paternalGrandfather->children[i];
                if (auntUncle != person->father)//exclude the initial parent from the list of aunts or uncles
                {
                    for (j = 0; j < auntUncle->numChildren; j++) 
                    {
                        Person *cousin = auntUncle->children[j];
                        if (cousin != person)//exclude the initial person from the list of cousins
                            printf("%s\n", cousin->name);
                    }
                }
            }
        }
    }
    
    
}

//function to number and show grandchildren
void grandchildren(Person *person) 
{
    printf("Grandchildren of %s:\n", person->name);
    int grandchildNumber = 1;
	int i, j;
    for (i = 0; i < person->numChildren; i++) 
	{
        Person *child = person->children[i];
        for (j = 0; j < child->numChildren; j++) 
		{
            Person *grandchild = child->children[j];
            printf("Grandchild %d: %s\n", grandchildNumber++, grandchild->name);
        }
    }
}

//function to find the spouse of a person for uncles and aunts
Person *findSpouse(Person *person) 
{
	int i;
    for (i = 0; i < person->numChildren; i++) 
	{
        if ((person->children[i]->mother == person) && (person->children[i]->father != NULL)) 
            return person->children[i]->father;
		else if ((person->children[i]->father == person) && (person->children[i]->mother != NULL)) 
            return person->children[i]->mother;
    }
    return NULL;
}

//function to show uncles and aunts of somebody
void showUnclesAunts(Person *person) 
{
    if (person->mother == NULL && person->father == NULL) 
    {   //if somebody doesn't have parents, clearly they won't have uncles or aunts
        printf("%s has no uncles or aunts.\n", person->name);
        return;
    }
    int i, aux = 0; //declare variable aux to check if somebody has or not uncles and aunts an if not show this
    printf("Uncles and Aunts of %s:\n", person->name);
    if (person->mother != NULL) 
    {
        Person *maternalGrandmother = person->mother->mother;
        if (maternalGrandmother != NULL && maternalGrandmother->numChildren > 1) 
        {
            for (i = 0; i < maternalGrandmother->numChildren; i++) 
            {
                Person *uncleAunt = maternalGrandmother->children[i];
                if (uncleAunt != person->mother) 
                {
                    printf("%s", uncleAunt->name);
                    Person *spouse = findSpouse(uncleAunt);//check if the uncle or aunt has a spouse
                    if (spouse != NULL)
                        printf(" and %s", spouse->name);
                    printf("\n");
                    aux = 1;
                }
            }
        } 
    }
    if (person->father != NULL) 
    {
        Person *paternalGrandmother = person->father->mother;

        if (paternalGrandmother != NULL && paternalGrandmother->numChildren > 1) 
        {
            for (i = 0; i < paternalGrandmother->numChildren; i++) 
            {
                Person *uncleAunt = paternalGrandmother->children[i];
                if (uncleAunt != person->father) 
                {
                    printf("%s", uncleAunt->name);
                    Person *spouse = findSpouse(uncleAunt);//check if the uncle or aunt has a spouse
                    if (spouse != NULL)
                        printf(" and %s", spouse->name);
                    printf("\n");
                    aux = 1;
                }
            }
        } 
    }
    if (!aux) 
        printf("%s has no uncles or aunts.\n", person->name);
}


int main() 
{
    //insert all the names and genders of the family members
    Person balasa, nae, costel, veronia, cecilia, catalin, nicoleta, dana, gabi, ionut, bogdan, claudia, laurentiu, carmen, alexandra, ionut2, vlad, adina, lali, livia, manuela, 
	georgiana, dan, mihai2, alexandru, ilie, madalin, loredana, ema, carla, ryan, zara, viorel, madi, madalina, mihai, mariana, mishu, cristina, corina, ciprian, stefan, alex;
    insertPerson(&balasa, "Balasa", 0);
    insertPerson(&nae, "Nae", 1);
    insertPerson(&costel, "Costel", 1);
    insertPerson(&veronia, "Veronia", 0);
    insertPerson(&cecilia, "Cecilia", 0);
    insertPerson(&catalin, "Catalin", 1);
    insertPerson(&nicoleta, "Nicoleta", 0);
    insertPerson(&dana, "Dana", 0);
    insertPerson(&gabi, "Gabi", 0);
    insertPerson(&ionut, "Ionut", 1);
    insertPerson(&bogdan, "Bogdan", 1);
    insertPerson(&claudia, "Claudia", 0);
	insertPerson(&laurentiu, "Laurentiu", 1);
	insertPerson(&carmen, "Carmen", 0);
    insertPerson(&alexandra, "Alexandra", 0);
    insertPerson(&ionut2, "Ionut2", 1);
    insertPerson(&vlad, "Vlad", 1);
    insertPerson(&adina, "Adina", 0);
    insertPerson(&lali, "Lali", 0);
    insertPerson(&livia, "Livia", 0);
    insertPerson(&manuela, "Manuela", 0);
    insertPerson(&georgiana, "Georgiana", 0);
    insertPerson(&dan, "Dan", 1);
    insertPerson(&mihai2, "Mihai2", 1);
	insertPerson(&alexandru, "Alexandru", 1);		
	insertPerson(&ilie, "Ilie", 1);
	insertPerson(&madalin, "Madalin", 1);
	insertPerson(&loredana, "Loredana", 0);
	insertPerson(&ema, "Ema", 0);
	insertPerson(&carla, "Carla", 0);
	insertPerson(&ryan, "Ryan", 1);
	insertPerson(&zara, "Zara", 0);
    insertPerson(&viorel, "Viorel", 1);
    insertPerson(&madi, "Madi", 0);
	insertPerson(&madalina, "Madalina", 0);	
	insertPerson(&mihai, "Mihai", 1);	
	insertPerson(&mariana, "Mariana", 0);
	insertPerson(&mishu, "Mishu", 1);
	insertPerson(&cristina, "Cristina", 0);
	insertPerson(&corina, "Corina", 0);
	insertPerson(&ciprian, "Ciprian", 1);
	insertPerson(&stefan, "Stefan", 1);
	insertPerson(&alex, "Alex", 0);
	
    //define each parent-child relationship
    addChild(&nae, &veronia);
    addChild(&balasa, &veronia);
    addChild(&nae, &cecilia);
    addChild(&balasa, &cecilia);
    addChild(&nae, &claudia);
    addChild(&balasa, &claudia);
    addChild(&nae, &lali);
    addChild(&balasa, &lali);
    addChild(&nae, &ilie);
    addChild(&balasa, &ilie);
    
    addChild(&cecilia, &catalin);
    addChild(&cecilia, &nicoleta);
    addChild(&catalin, &dana);
    addChild(&catalin, &gabi);
    addChild(&nicoleta, &ionut);
    addChild(&nicoleta, &bogdan);
    
    addChild(&claudia, &laurentiu);
    addChild(&claudia, &carmen);
    addChild(&laurentiu, &alexandra);
    addChild(&laurentiu, &ionut2);
    addChild(&carmen, &vlad);
    addChild(&carmen, &adina);
    
    addChild(&lali, &livia);
    addChild(&lali, &manuela);
    addChild(&livia, &georgiana);
    addChild(&livia, &dan);
    addChild(&manuela, &mihai2);
    addChild(&manuela, &alexandru);
    
    addChild(&ilie, &madalin);
    addChild(&ilie, &loredana);
    addChild(&madalin, &ema);
    addChild(&madalin, &carla);
    addChild(&loredana, &ryan);
    addChild(&loredana, &zara);
    
    addChild(&viorel, &madalina);
    addChild(&madi, &madalina);
    
    addChild(&costel, &mihai);
    addChild(&veronia, &mihai);
    addChild(&costel, &mariana);
    addChild(&veronia, &mariana);
    
    addChild(&mihai, &stefan);
	addChild(&madalina, &stefan);
    
    addChild(&mishu, &cristina);
    addChild(&mishu, &corina);
    addChild(&mariana, &cristina);
    addChild(&mishu, &cristina);
    addChild(&mariana, &corina);
    addChild(&mishu, &corina);
    
    addChild(&ciprian, &alex);
    addChild(&cristina, &alex);
	
    /*showAscendants(&zara);
    printf("\n");
    showAscendants(&vlad);
    printf("\n");
    showAscendants(&ema);
    printf("\n");
    showAscendants(&bogdan);
    printf("\n");
    showAscendants(&stefan);
    printf("\n");*/
    showAscendants(&nae);
    printf("\n");
    /*showDescendants(&balasa);
	printf("\n");
	
    showSiblings(&loredana);
	printf("\n");
	showSiblings(&dan);
	printf("\n");
	showSiblings(&laurentiu);
	printf("\n");
	showSiblings(&dana);
	printf("\n");
	showSiblings(&corina);
	printf("\n");*/
	showDescendants(&stefan);
	printf("\n");
    showCousins(&mihai);
    printf("\n");
    showCousins(&ryan);
    printf("\n");
    showCousins(&gabi);
    printf("\n");
    showCousins(&carla);
    printf("\n");
    showCousins(&ionut);
    printf("\n");
    showCousins(&stefan);
    printf("\n");
    showCousins(&alex);
    printf("\n");
    /*grandchildren(&nae);
    printf("\n");
    grandchildren(&veronia);
    printf("\n");
    grandchildren(&cecilia);
    printf("\n");
    grandchildren(&claudia);
    printf("\n");
    grandchildren(&lali);
    printf("\n");
    grandchildren(&ilie);
    printf("\n");*/
    
    grandchildren(&stefan);
    printf("\n");
    /*showUnclesAunts(&vlad);
    printf("\n");
    showUnclesAunts(&madalin);
    printf("\n");
    showUnclesAunts(&lali);
    printf("\n");
    showUnclesAunts(&alex);
    printf("\n");
    showUnclesAunts(&dana);
    printf("\n");*/
    return 0;
}

