#include <stdio.h>

int menu();
void Load();
void Save();
void Read();
void Search();
void Add();
void Update();
void Delete();

void check();

char SubscriberName[100][50];
char Email[100][50];
char JournalName[100][20];
char SubscriptionDate[100][12];

int record = 0;

int main()
{   
    // Load();
    while (1)
    {
        int ch = menu();

        switch (ch) {
            case 1:
                // Read();
                check();
                break;
            
            case 2:
                Add();
                break;
            
            case 3:
                // Search();
                break;
            
            case 4:
                // Update();
                break;
            
            case 5:
                // Delete();
                break;

            case 6:
                // Save();
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

void load()
{
    FILE *file = fopen("subscription.csv", "r");
    if (file == NULL) {
        printf("ไม่พบไฟล์\n");
        return;
    }
    
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    
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
    while (Con != 'y' || Con != 'Y' || Con != 'n' || Con != 'N')
    {
        printf("(y/n)?: ");
        scanf(" %c", &Con);
    }
    
    printf("");
    if (Con == 'y' || Con == 'Y'){
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


}

void check()
{
    for (int i = 0; i < record; i++) {
        printf("%s %s %s %s\n", SubscriberName[i], Email[i], JournalName[i], SubscriberName[i]);
    }
}