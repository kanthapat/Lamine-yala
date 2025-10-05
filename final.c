#include <stdio.h>
#include <string.h>

int menu();
void Load();
void Save();
void Read();
void Search();
void Add();
void Update(int rec);
void Delete();

void check();

char SubscriberName[100][50];
char Email[100][50];
char JournalName[100][20];
char SubscriptionDate[100][12];

int record = 0;

int main()
{
    char edit[50];
    int choice = 0;
    Load();
    while (1)
    {
        int ch = menu();

        switch (ch)
        {
        case 1:
            // Read();
            check();
            break;

        case 2:
            Add();
            break;

        case 3:
            Search();
            break;

        case 4:
            printf("----- อัพเดทข้อมูล -----\n");
            printf("กรอกชื่อที่ต้องการแก้ไขข้อมูล: ");
            scanf(" %[^\n]", edit);

            int foundFlag = 0;
            
            for (int i = 0; i < record; i++)
            {
                char *found = strstr(SubscriberName[i], edit);
                if (found != NULL)
                {
                    char check;
                    printf("%s %s\n", SubscriberName[i], Email[i]);
                    do
                    {
                        printf("ข้อมูลถูกต้องหรือไม่ (y/n): ");
                        scanf(" %c", &check);
                    } while (check != 'y' && check != 'Y' && check != 'n' && check != 'N');
                    
                    if (check == 'y' || check == 'Y') {
                        Update(i);
                        foundFlag = 1;
                        break;
                    }         
                }
            }

            if (!foundFlag)
            {
                printf("ไม่พบชื่อ '%s'\n", edit);
            }
            break;

        case 5:
            // Delete();
            break;

        case 6:
            Save();
            break;

        default:
            printf("กรอกมั่วลั่วนะ\n");
            break;
        }
        if (ch == 6)
        {
            break;
        }
    }
    return 0;
}

void Load()
{
    FILE *file = fopen("subscription.csv", "r");
    if (file == NULL)
    {
        printf("ไม่พบไฟล์\n");
        return;
    }

    char line[100];
    char *token;
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL && record < 100)
    {

        token = strtok(line, ",");
        if (token != NULL)
        {
            strcpy(SubscriberName[record], token);
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(Email[record], token);
        }

        token = strtok(NULL, ",");
        if (token != NULL)
        {
            strcpy(JournalName[record], token);
        }

        token = strtok(NULL, "\n");
        if (token != NULL)
        {
            strcpy(SubscriptionDate[record], token);
        }

        record++;
    }

    fclose(file);

    printf("โหลดข้อมูลสำเร็จ!!\n");
}

int menu()
{
    int choice = 0;
    printf("-------- ระบบจัดการข้อมูลการสมัครสมาชิก --------\n");
    printf("1.อ่านข้อมูล\n");
    printf("2.เพิ่มข้อมูล\n");
    printf("3.ค้นหาข้อมูล\n");
    printf("4.อัพเดทข้อมูล\n");
    printf("5.ลบข้อมูล\n");
    printf("6.บันทึกและออกจากโปรแกรม");
    printf("กรุณากรอกเลข (1-6): ");
    scanf("%d", &choice);

    return choice;
}

void Add()
{
    char Con;
    printf("----- เพิ่มข้อมูล -----\n");
    printf("Subscirber Name: ");
    scanf(" %[^\n]", &SubscriberName[record]);
    printf("Email: ");
    scanf(" %[^\n]", &Email[record]);
    printf("Journal Name: ");
    scanf(" %[^\n]", &JournalName[record]);
    printf("Subscription Date: ");
    scanf(" %[^\n]", &SubscriptionDate[record]);

    record++;
    printf("เพิ่มข้อมูลสำเร็จ!!\n");
    printf("ต้องการเพิ่มข้อมูลต่อหรือไม่ (y/n): ");

    scanf(" %c", &Con);
    printf("");
    if (Con == 'y' || Con == 'Y')
    {
        Add();
    }
}

void Save()
{
    FILE *file = fopen("subscription.csv", "w");

    if (file == NULL)
    {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    fprintf(file, "SubscriberName, Email, JournalName, SubscriptionDate\n");

    for (int i = 0; i < record; i++)
    {
        fprintf(file, "%s,%s,%s,%s\n", SubscriberName[i], Email[i], JournalName[i], SubscriptionDate[i]);
    }

    fclose(file);

    printf("บันทึกสำเร็จ!!\n");
}

void check()
{
    for (int i = 0; i < record; i++)
    {
        printf("%s %s %s %s\n", SubscriberName[i], Email[i], JournalName[i], SubscriptionDate[i]);
    }
}

void Search()
{
    int choose = 0;
    int foundCount = 0;
    printf("----- ค้นหาข้อมูล -----\n");
    printf("ต้องการค้นหาแบบไหน\n 1.ชื่อสมาชิก\n 2.ชื่อวารสาร\n");
    while (choose != 1 && choose != 2)
    {
        printf("กรอกตัวเลือก (1,2): ");
        scanf("%d", &choose);
    }

    if (choose == 1)
    {
        char name[50];
        printf("กรอกชื่อที่ต้องการหา ");
        scanf(" %[^\n]", &name);

        for (int i = 0; i < record; i++)
        {
            char *foundName = strstr(name, SubscriberName[i]);
            if (foundName != NULL)
            {
                printf("%s %s %s %s\n", SubscriberName[i], Email[i], JournalName[i], SubscriptionDate[i]);
                foundCount++;
            }
        }
    }
    else
    {
        char Journal[50];
        printf("กรอกชื่อวารสารที่ต้องการค้นหา: ");
        scanf(" %[^\n]", &Journal);

        for (int j = 0; j < record; j++)
        {
            char *foundJournal = strstr(Journal, JournalName[j]);

            if (foundJournal != NULL)
            {
                printf("%s %s %s %s\n", SubscriberName[j], Email[j], JournalName[j], SubscriptionDate[j]);
                foundCount++;
            }
        }
    }

    if (foundCount == 0)
    {
        printf("ไม่พบข้อมูล\n");
    }
}

void Update(int rec)
{
    int choice = 0;

    printf("ต้องการแก้ไขข้อมูลอะไร?\n1.ชื่อ\n2.อีเมล์\n3.ชื่อวารสาร\n4.วันที่สมัครสมาชิก\n");
    printf("กรอกตัวเลข (1-4): ");
    scanf("%d", &choice);

    while (choice < 1 && choice > 4)
    {
        printf("กรอกมั่ว!!\n");
        printf("ต้องการแก้ไขข้อมูลอะไร?\n1.ชื่อ\n2.อีเมล์\n3.ชื่อวารสาร\n4.วันที่สมัครสมาชิก\n");
        printf("กรอกตัวเลข (1-4): ");
        scanf("%d", &choice);
    }

    switch (choice)
    {
    case 1:
        printf("กรอกชื่อใหม่: ");
        scanf(" %[^\n]", &SubscriberName[rec]);
        printf("แก้ไขสำเร็จ!!\n");
        break;
    case 2:
        printf("กรอกอีเมล์ใหม่: ");
        scanf(" %[^\n]", &Email[rec]);
        printf("แก้ไขสำเร็จ!!\n");
        break;
    case 3:
        printf("กรอกชื่อวารสารใหม่: ");
        scanf(" %[^\n]", &JournalName[rec]);
        printf("แก้ไขสำเร็จ!!\n");
        break;
    case 4:
        printf("กรอกวันที่ใหม่: ");
        scanf(" %[^\n]", &SubscriptionDate[rec]);
        printf("แก้ไขสำเร็จ!!\n");
        break;
    default:
        printf("มั่ว!!");
        break;
    }
}
