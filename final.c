#include <stdio.h>
#include <string.h>
#include <assert.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

int menu();
void Load(const char *filename);
void Save(const char *filename);
void Read();
void Search();
void Add();
void Update(int rec);
void Delete();

void runUnitTests();
void runIntegrationTests();

char SubscriberName[100][50];
char Email[100][50];
char JournalName[100][20];
char SubscriptionDate[100][12];

int record = 0;

int main()
{
    int mode; 
    printf("===== ระบบจัดการข้อมูลการสมัครสมาชิก =====\n"); 
    printf("1. โหมดใช้งานปกติ\n"); 
    printf("2. โหมดทดสอบระบบ (Unit + Integration Test)\n"); 
    printf("เลือกโหมด (1-2): "); 
    scanf("%d", &mode); 
    if (mode == 2) { 
        runUnitTests(); 
        runIntegrationTests(); 
        printf(BLUE"\n✅ การทดสอบทั้งหมดเสร็จสิ้น!\n"RESET); 
        return 0; 
    }

    char edit[50];
    const char *main_file = "subscription.csv";
    int choice = 0;
    Load(main_file);
    int ch;

    do
    {
        ch = menu();

        switch (ch)
        {
        case 1:
            Read();
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
                    printf("----------------------------------------------------------------------------------------------------------\n");
                    printf("----------------------------------------------------------------------------------------------------------\n");
                    printf("| %-20s | %-30s | %-25s | %-18s |\n", "SubscriberName", "Email", "JournalName", "SubscriptionDate");
                    printf("| %-20s | %-30s | %-25s | %-18s |\n", 
                        SubscriberName[i], 
                        Email[i], 
                        JournalName[i], 
                        SubscriptionDate[i]);
                    printf("----------------------------------------------------------------------------------------------------------\n");
                    do
                    {
                        printf("ข้อมูลถูกต้องหรือไม่ (y/n): ");
                        scanf(" %c", &check);
                    } while (check != 'y' && check != 'Y' && check != 'n' && check != 'N');

                    if (check == 'y' || check == 'Y')
                    {
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
            Delete();
            break;

        case 6:
            Save(main_file);
            break;

        default:
            printf("กรอกมั่วลั่วนะ\n");
            break;
        }
    } while (ch != 6);
    
    return 0;
}

void Load(const char *filename)
{
    FILE *file = fopen(filename, "r");
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
    printf("1.แสดงข้อมูล\n");
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
    printf("Subscription Date (yyyy-mm-dd): ");
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

void Save(const char *filename)
{
    FILE *file = fopen(filename, "w");

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

void Read()
{
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-30s | %-25s | %-18s |\n", "SubscriberName", "Email", "JournalName", "SubscriptionDate");
    printf("----------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < record; i++)
    {
        printf("| %-20s | %-30s | %-25s | %-18s |\n", 
               SubscriberName[i], 
               Email[i], 
               JournalName[i], 
               SubscriptionDate[i]);
    }

    printf("----------------------------------------------------------------------------------------------------------\n");
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
                printf("----------------------------------------------------------------------------------------------------------\n");
                printf("| %-20s | %-30s | %-25s | %-18s |\n", "SubscriberName", "Email", "JournalName", "SubscriptionDate");
                printf("----------------------------------------------------------------------------------------------------------\n");
                printf("| %-20s | %-30s | %-25s | %-18s |\n", 
                    SubscriberName[i], 
                    Email[i], 
                    JournalName[i], 
                    SubscriptionDate[i]);
                printf("----------------------------------------------------------------------------------------------------------\n");
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
                printf("----------------------------------------------------------------------------------------------------------\n");
                printf("| %-20s | %-30s | %-25s | %-18s |\n", "SubscriberName", "Email", "JournalName", "SubscriptionDate");
                printf("----------------------------------------------------------------------------------------------------------\n");
                printf("| %-20s | %-30s | %-25s | %-18s |\n", 
                    SubscriberName[j], 
                    Email[j], 
                    JournalName[j], 
                    SubscriptionDate[j]);
                printf("----------------------------------------------------------------------------------------------------------\n");
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
    char Con;
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
        printf("กรอกวันที่ใหม่ (yyyy-mm-dd): ");
        scanf(" %[^\n]", &SubscriptionDate[rec]);
        printf("แก้ไขสำเร็จ!!\n");
        break;
    default:
        printf("มั่ว!!\n");
        break;
    }
    printf("ต้องการแก้ไขข้อมูลต่อหรือไม่ (y/n): ");

    scanf(" %c", &Con);
    printf("");
    if (Con == 'y' || Con == 'Y')
    {
        Update(rec);
    } else if (Con == 'n' || 'N') {
        printf("กำลังกลับสู่หน้าหลัก...\n");
    } else {
        printf("กรอกผิด\n");
        printf("กลับสู่หน้าหลัก...\n");
    }
}

void Delete()
{
    char del[50];
    printf("----- ลบข้อมูล -----\n");
    printf("กรอกชื่อที่ต้องการลบข้อมูล: ");
    scanf(" %[^\n]", del);

    int foundcount = 0;

    for (int i = 0; i < record; i++)
    {
        char *f = strstr(SubscriberName[i], del);
        if (f != NULL)
        {
            char che;
            printf("----------------------------------------------------------------------------------------------------------\n");
            printf("----------------------------------------------------------------------------------------------------------\n");
            printf("| %-20s | %-30s | %-25s | %-18s |\n", "SubscriberName", "Email", "JournalName", "SubscriptionDate");
            printf("| %-20s | %-30s | %-25s | %-18s |\n", 
                SubscriberName[i], 
                Email[i], 
                JournalName[i], 
                SubscriptionDate[i]);
            printf("----------------------------------------------------------------------------------------------------------\n");
            do
            {
                printf("ข้อมูลถูกต้องหรือไม่ (y/n): ");
                scanf(" %c", &che);
            } while (che != 'y' && che != 'Y' && che != 'n' && che != 'N');

            if (che == 'y' || che == 'Y')
            {
                for(int j = i; j < record - 1; j++) {
                    strcpy(SubscriberName[j], SubscriberName[j+1]);
                    strcpy(Email[j], Email[j+1]);
                    strcpy(JournalName[j], JournalName[j+1]);
                    strcpy(SubscriptionDate[j], SubscriptionDate[j+1]);                   
                }
                record--;
                printf("ลบข้อมูลเรียบร้อย!\n");
                foundcount = 1;
                break;
            }
        }
    }

    if (!foundcount)
    {
        printf("ไม่พบชื่อ '%s'\n", del);
    }
}

void DeleteTest(const char *del)
{
    int foundcount = 0;
    for (int i = 0; i < record; i++)
    {
        if (strstr(SubscriberName[i], del))
        {
            for (int j = i; j < record - 1; j++)
            {
                strcpy(SubscriberName[j], SubscriberName[j + 1]);
                strcpy(Email[j], Email[j + 1]);
                strcpy(JournalName[j], JournalName[j + 1]);
                strcpy(SubscriptionDate[j], SubscriptionDate[j + 1]);
            }
            record--;
            foundcount = 1;
            break;
        }
    }
    assert(foundcount == 1);  // ทดสอบว่าเจอและลบได้
}

void runUnitTests()
{
    printf(YELLOW"\n===== 🔍 เริ่มการทดสอบ Unit Test =====\n"RESET);

    // จำลองข้อมูล
    record = 0;
    strcpy(SubscriberName[0], "Alice");
    strcpy(Email[0], "alice@mail.com");
    strcpy(JournalName[0], "Nature");
    strcpy(SubscriptionDate[0], "2024-10-01");
    record++;
    printf("Test Data 1: %s, %s, %s, %s\n", SubscriberName[0], Email[0], JournalName[0], SubscriptionDate[0]);

    // Test 1: เพิ่มข้อมูล
    strcpy(SubscriberName[record], "Bob");
    strcpy(Email[record], "bob@mail.com");
    strcpy(JournalName[record], "Science");
    strcpy(SubscriptionDate[record], "2024-11-01");
    record++;
    printf("Test 1: เพิ่มข้อมูล %s\n", SubscriberName[1]);
    if (strcmp(SubscriberName[1], "Bob") == 0){
        printf(GREEN"✅ Test 1 ผ่าน\n"RESET);
    } else {
        printf(RED"❌ Test 1 ล้มเหลว\n"RESET);
    }
    Read();

    // Test 2: ลบข้อมูล
    printf("Test 2: ลบข้อมูล Alice\n");
    DeleteTest("Alice");  // ฟังก์ชันทดสอบลบข้อมูลเฉพาะ test
    if (record == 1 && strcmp(SubscriberName[0], "Bob") == 0){
        printf(GREEN"✅ Test 2 ผ่าน\n"RESET);
    } else {
        printf(RED"❌ Test 2 ล้มเหลว\n"RESET);
    }

    Read();
    printf(GREEN"✅ Unit Tests เสร็จสิ้น\n"RESET);
}

// -------------------------
void runIntegrationTests()
{
    const char *test_file = "test_subscriptions.csv";

    // แสดง Scenario คร่าว ๆ ก่อนเริ่ม
    printf(YELLOW "\n===== 🧩 Integration Test Scenario =====\n" RESET);
    printf(BLUE "Scenario:\n" RESET);
    printf("1️⃣  เตรียมข้อมูลสมาชิกใหม่ (Charlie)\n");
    printf("2️⃣  บันทึกข้อมูลลงไฟล์ test_subscriptions.csv\n");
    printf("3️⃣  ล้างข้อมูลใน memory และโหลดจากไฟล์\n");
    printf("4️⃣  ตรวจสอบข้อมูลที่โหลดว่าถูกต้องหรือไม่\n");
    printf("5️⃣  แสดงข้อมูลทั้งหมด\n");

    printf(YELLOW "เริ่มการทดสอบ...\n" RESET);

    // --- Step 0: เตรียมข้อมูลจำลอง ---
    record = 0;
    strcpy(SubscriberName[0], "Charlie");
    strcpy(Email[0], "charlie@mail.com");
    strcpy(JournalName[0], "Tech");
    strcpy(SubscriptionDate[0], "2024-09-01");
    record++;
    printf(BLUE "Step 1: เตรียมข้อมูลจำลอง\n" RESET);
    printf("Test Data: %s, %s, %s, %s\n", SubscriberName[0], Email[0], JournalName[0], SubscriptionDate[0]);

    // --- Step 1: Save ---
    printf(BLUE "\nStep 2: Save ข้อมูลลงไฟล์ %s\n" RESET, test_file);
    Save(test_file);
    printf(GREEN "✅ Save สำเร็จ\n" RESET);

    // --- Step 2: Load ---
    record = 0;
    printf(BLUE "\nStep 3: Load ข้อมูลจากไฟล์ %s\n" RESET, test_file);
    Load(test_file);
    printf(GREEN "✅ Load สำเร็จ\n" RESET);

    // --- Step 3: ตรวจสอบข้อมูล ---
    printf(BLUE "\nStep 4: ตรวจสอบข้อมูลที่โหลด\n" RESET);
    printf("Loaded Data: %s, %s, %s, %s\n", SubscriberName[0], Email[0], JournalName[0], SubscriptionDate[0]);
    if (strcmp(SubscriberName[0], "Charlie") == 0 && strcmp(Email[0], "charlie@mail.com") == 0)
        printf(GREEN "✅ Integration Test ผ่าน\n" RESET);
    else
        printf(RED "❌ Integration Test ล้มเหลว\n" RESET);

    // --- Step 4: แสดงข้อมูลทั้งหมด ---
    printf(BLUE "\nStep 4: แสดงข้อมูลทั้งหมด\n" RESET);
    Read();

    printf(GREEN "\n✅ Integration Tests เสร็จสิ้น\n" RESET);
}
