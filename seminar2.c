#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Document {
    int id;
    char name[50];
    int total_lines;
    int remaining_lines;
    struct Document* next;
} Document;

typedef struct Printer {
    int id;
    int time_per_line;
    Document* current_document;
    struct Printer* next;
} Printer;

Document* create_document(int id, const char* name, int total_lines);
void add_document(Document** head, Document* new_document);
void remove_document(Document** head, int id);
void print_documents(Document* head);
void free_documents(Document** head);

Printer* create_printer(int id, int time_per_line);
void add_printer(Printer** head, Printer* new_printer);
void distribute_documents(Printer* printers, Document** document_queue);
void update_printers(Printer* printers);
void print_printers(Printer* head);
void free_printers(Printer** head);

void simulate_time_step(Printer* printers, Document** document_queue);

int main() {
    Printer* printers = NULL;
    add_printer(&printers, create_printer(1, 2));
    add_printer(&printers, create_printer(2, 3));

    Document* document_queue = NULL;
    add_document(&document_queue, create_document(1, "Document1", 10));
    add_document(&document_queue, create_document(2, "Document2", 5));
    add_document(&document_queue, create_document(3, "Document3", 7));

    while (document_queue != NULL || any_printer_busy(printers))
    {
        distribute_documents(printers, &document_queue);
        simulate_time_step(printers, &document_queue);
        print_printers(printers);
        printf("\n");

        if (document_queue != NULL && document_queue->id == 2)
        {
            cancel_document(&document_queue, printers, 2);
            printf("Document 2 has been canceled.\n");
        }

        if (printers->id == 1 && printers->current_document == NULL)
        {
            remove_printer(&printers, &document_queue, 1);
            printf("Printer 1 has been removed.\n");
        }
    }

    free_printers(&printers);
    free_documents(&document_queue);

    return 0;
}

int any_printer_busy(Printer* printers)
{
    Printer* temp = printers;
    while (temp != NULL)
    {
        if (temp->current_document != NULL)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

Document* create_document(int id, const char* name, int total_lines)
{
    Document* new_document = (Document*)malloc(sizeof(Document));
    new_document->id = id;
    strcpy(new_document->name, name);
    new_document->total_lines = total_lines;
    new_document->remaining_lines = total_lines;
    new_document->next = NULL;
    return new_document;
}

void add_document(Document** head, Document* new_document)
{
    if (*head == NULL)
    {
        *head = new_document;
    } else {
        Document* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_document;
    }
}

void remove_document(Document** head, int id)
{
    Document* temp = *head;
    Document* prev = NULL;

    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void print_documents(Document* head)
{
    Document* temp = head;
    while (temp != NULL)
    {
        printf("Document ID: %d, Name: %s, Remaining Lines: %d\n", temp->id, temp->name, temp->remaining_lines);
        temp = temp->next;
    }
}

void free_documents(Document** head)
{
    Document* temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

Printer* create_printer(int id, int time_per_line)
{
    Printer* new_printer = (Printer*)malloc(sizeof(Printer));
    new_printer->id = id;
    new_printer->time_per_line = time_per_line;
    new_printer->current_document = NULL;
    new_printer->next = NULL;
    return new_printer;
}

void add_printer(Printer** head, Printer* new_printer)
{
    if (*head == NULL)
    {
        *head = new_printer;
    } else {
        Printer* temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_printer;
    }
}

void distribute_documents(Printer* printers, Document** document_queue)
{
    Printer* temp_printer = printers;
    while (temp_printer != NULL)
    {
        if (temp_printer->current_document == NULL && *document_queue != NULL)
        {
            temp_printer->current_document = *document_queue;
            *document_queue = (*document_queue)->next;
            temp_printer->current_document->next = NULL;
        }
        temp_printer = temp_printer->next;
    }
}

void update_printers(Printer* printers)
{
    Printer* temp_printer = printers;
    while (temp_printer != NULL)
    {
        if (temp_printer->current_document != NULL)
        {
            temp_printer->current_document->remaining_lines--;
            if (temp_printer->current_document->remaining_lines == 0)
            {
                free(temp_printer->current_document);
                temp_printer->current_document = NULL;
            }
        }
        temp_printer = temp_printer->next;
    }
}

void print_printers(Printer* head)
{
    Printer* temp = head;
    while (temp != NULL)
    {
        if (temp->current_document != NULL)
        {
            printf("Printer ID: %d, Document: %s, Remaining Lines: %d\n", temp->id, temp->current_document->name, temp->current_document->remaining_lines);
        } else {
            printf("Printer ID: %d, No Document\n", temp->id);
        }
        temp = temp->next;
    }
}

void free_printers(Printer** head)
{
    Printer* temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void simulate_time_step(Printer* printers, Document** document_queue)
{
    distribute_documents(printers, document_queue);
    update_printers(printers);
}

void cancel_document(Document** document_queue, Printer* printers, int id)
{
    remove_document(document_queue, id);

    Printer* temp_printer = printers;
    while (temp_printer != NULL)
    {
        if (temp_printer->current_document != NULL && temp_printer->current_document->id == id)
        {
            free(temp_printer->current_document);
            temp_printer->current_document = NULL;
        }
        temp_printer = temp_printer->next;
    }
}

void remove_printer(Printer** head, Document** document_queue, int id)
{
    Printer* temp = *head;
    Printer* prev = NULL;

    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        if (temp->current_document != NULL)
        {
            add_document(document_queue, temp->current_document);
        }
        free(temp);
        return;
    }

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    if (temp->current_document != NULL)
    {
        add_document(document_queue, temp->current_document);
    }
    free(temp);
}
