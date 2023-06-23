/* Zayan Tofeeq - C Coding Challange:  */ 

// max array lenght
#define N 250
// max word Letters to be added into linked list, Can be changed to change the
// insertion size
#define Word_Lenght 4
// self-defined min func
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// initilizing structure of node
typedef struct node {
  int lenght;
  char word[Word_Lenght + 1]; // adding +1 as NULL terminator
  struct node *next;
} node;
node *head = NULL;

// func to create new node
// node stores only first 4 Letters of valid input (Alphabets) and actual lenght
// of the word
node *createnode(char *word, int size) {
  node *newnode = NULL;
  node *temp = NULL;
  // allocating memory for newnode
  newnode = (node *)malloc(sizeof(node));

  for (int i = 0; i < Word_Lenght; i++) {
    // loop to store the word in the new node
    newnode->word[i] = word[i];
  }
  newnode->lenght = size;
  newnode->next = NULL;

  // checking if list is empty
  // else adding onto the existing list
  if (head == NULL) {
    head = newnode;
  } else {
    temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newnode;
  }
  return head;
}

// funtion to print the linked list
void printlist(node *head) {
  node *temp = NULL;
  temp = head;
  printf("\ncurrent list: ");
  while (temp != NULL) {
    printf("[%s|%d]-> ", temp->word, temp->lenght);
    temp = temp->next;
  }
  printf("[null]\n");
}

// funtion to compare strings (return 0 if its a match)
// tolower() is used to avoid wrong sorting due to case sensitivity
int strcompare(const char *str, const char *str1) {
  while (tolower(*str) && (tolower(*str) == tolower(*str1))) {
    str++;
    str1++;
  }
  return tolower(*str) - tolower(*str1);
}

// funtion to sort the list by reassigning the pointers
// implemented insertion sorting algorithm
void sortlist(node **head) {
  if (*head == NULL || (*head)->next == NULL) {
    return;
  }
  node *prev = *head;
  node *curr = prev->next;

  while (curr != NULL) {
    node *insert = *head;
    node *prevInsert = NULL;

    while (insert != curr && strcompare(insert->word, curr->word) < 0) {
      prevInsert = insert;
      insert = insert->next;
    }
    if (insert != curr) {
      prev->next = curr->next;
      curr->next = insert;
      if (prevInsert == NULL) {
        *head = curr;
      } else {
        prevInsert->next = curr;
      }
      curr = prev;
    }
    prev = curr;
    curr = curr->next;
  }
}

// function to delete the whole list
// funtions takes in pointer to the pointer head
void deletlist(node **head) {
  if (*head == NULL) {
    printf("\nSorry! Can't delete an empty list\n");
    return;
  }
  node *curr = *head;
  node *next;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  *head = NULL;
  printf("\nList deleted sucessfully\n");
}

// funtion to add a word into list
// getchar stores stdin in the arr until user press enter
// more words can be inserted if the sentence contains spaces
// only way to re-populate the list after deleting it, without running the
// program again
// same input parsing method used inside **main()**
void addword(node *head) {
  int word_count = 0;
  char arr[N], word[Word_Lenght];
  printf("  Type a word to be added into linked list:\n  ");

  int size = 0, ch;
  while ((ch = getchar()) != '\n') {
    arr[size] = ch;
    size++;
  }
  arr[size] = '\0';

  for (int i = 0; i < size; i++) {
    if (isalpha(arr[i])) {
      word[word_count] = arr[i];
      word_count++;
    }
    if (arr[i] == ' ' || arr[i + 1] == '\0') {
      if (word_count > 0) {
        word[MIN(Word_Lenght, word_count)] = '\0';
        createnode(word, word_count);
        word_count = 0;
      }
    }
  }
}

// funtion to search the given word or string of words
// getchar stores stdin in the arr to be parsed and compared with the words in
// the list whenever a valid word is parsed/found it is compared to the words in
// the list Only first 4 letters of the word is compared supports case sensitive
// and insensitive search type
void searchwords(node **head) {
  int word_count = 0, casesense;
  char arr[N], word[Word_Lenght];

  while (scanf("%d", &casesense) != 1 || (casesense != 0 && casesense != 1)) {
    printf("  Invalid input!\n  :: ");
    while (getchar() != '\n')
      ;
  }
  getchar();
  printf(
      "  Type a word to search in the list (note: compares first %d letters of "
      "the word in the list)\n  ",
      Word_Lenght);

  int size = 0, ch;
  while ((ch = getchar()) != '\n') {
    arr[size] = ch;
    size++;
  }
  arr[size] = '\0';

  for (int i = 0; i < size; i++) {
    if (isalpha(arr[i])) {
      word[word_count] = arr[i];
      word_count++;
    }
    if (arr[i] == ' ' || arr[i + 1] == '\0') {
      printf("\n");
      if (word_count > 0) {
        word[MIN(Word_Lenght, word_count)] = '\0';
        node *temp = NULL;
        temp = *head;
        while (temp != NULL) {
          int match = 1;
          for (int i = 0; i < (MIN(Word_Lenght, word_count)); i++) {
            if (casesense == 1) {
              if (temp->word[i] != word[i]) {
                match = 0;
                break;
              }
            } else {
              if (tolower(temp->word[i]) != tolower(word[i])) {
                match = 0;
                break;
              }
            }
          }
          if (match == 1) {
            printf("[%s|%d], ", temp->word, temp->lenght);
          }
          temp = temp->next;
        }
        word_count = 0;
      }
    }
  }
  printf("\n");
}

int main() {
  char arr[N], word[Word_Lenght];
  int word_count = 0, choice, scannum;

  printf("Type a sentence to be added into linked list:\n");

  // stdin stored in the arr until user press enter
  int size = 0, ch;
  while ((ch = getchar()) != '\n') {
    arr[size] = ch;
    size++;
  }
  arr[size] = '\0';

  // looping through the input to discard any other charectors that are not
  // alphabets also using spaces to slipt the words into pairs of word and thier
  // size. max lenght of the word stored in the list is defined in (Word_Lenght)
  // function MIN function is used to compare and store the words if they are <
  // Word_Lenght

  for (int i = 0; i < size; i++) {
    if (isalpha(arr[i])) {
      word[word_count] = arr[i];
      word_count++;
    }
    if (arr[i] == ' ' || arr[i + 1] == '\0') {
      if (word_count > 0) {
        word[MIN(Word_Lenght, word_count)] = '\0';
        node *head = createnode(word, word_count);
        word_count = 0;
      }
    }
  }
  printlist(head);
  printf("\nafter sorting ");
  sortlist(&head);
  printlist(head);

  // Do while loop to run the menu with list modifying functions until user wish
  // to exit nested do while loop to check the invalid input until the right
  // input is received

  do {
    printf(
        "\nEnter your choice:\n1: Print current list\n2: Add new words to the "
        "list\n3: Search for a word in the list\n4: Delete the list\n0: "
        "Quit\n:: ");

    do {
      scannum = scanf("%d", &choice);
      while (getchar() != '\n')
        ;
      if (scannum != 1) {
        printf("\nInvalid Choice !!");
        printf("\nEnter your choice:\n1: Print current list\n2: Add new words "
               "to the "
               "list\n3: Search for a word in the list\n4: Delete the list\n0: "
               "Quit\n:: ");
      }
    } while (scannum != 1);

    switch (choice) {
    case 1:
      printlist(head);
      break;
    case 2:
      addword(head);
      sortlist(&head);
      printlist(head);
      break;
    case 3:
      printf("  0:case insensitive\n  1:case sensitive\n  "
             "::");
      searchwords(&head);
      break;
    case 4:
      deletlist(&head);
      break;
    case 0:
      break;
    default:
      printf("\nInvalid Choice !!");
      break;
    }
  } while (choice != 0);
  return 0;
}